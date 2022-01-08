#ifndef ALLOCATOR_CHUNK_LIST_H
#define ALLOCATOR_CHUNK_LIST_H

#include <cstddef> // Include here all the 'cstddef' facilities.
#include <sys/mman.h> // Include here all the 'sys/mman' facilities.

/// This structure is used within a memory pool allocator. It contains a data element, together with the address to the next chunk.
/// \tparam T The type of this specific structure.
template <typename T>
struct chunk {
    T m_data; // This is your data field.
    chunk* m_next_node; // This is the value to the next node field. It is a memory address.
};

/// This is the class 'chunk_list'. It is used to allocate/deallocate memory for the list of chunks for a block in your memory pool allocator.
/// \tparam T The type of this specific class.
template <typename T>
class chunk_list {
public:
    /// This is the constructor of the 'chunk_list' class.
    /// \param number_of_chunks This is the number of chunks that you want to allocate. It is NOT in bytes!
    explicit chunk_list(const std::size_t& number_of_chunks);

    /// This method gets a free chunk from your current block of chunks.
    /// \return Return the address to a free chunk.
    chunk<T>* get_free_chunk();

    /// This method removes a just allocated chunk. Due to that you are using a linked list under the hood, you are only chancing the 'm_next_node' field from this struct.
    /// \param free_chunk The address to an allocated chunk.
    void remove_chunk(chunk<T>* free_chunk) noexcept;

    /// This method removes the whole list of chunks. It deallocates the whole block of memory.
    void remove_chunk_list() noexcept;

private:
    /// This method is just used for debugging purposes, it shows how much memory you just allocated, or you are going to deallocate.
    /// \param pointer_to_memory Memory address of the memory that you are allocating/deallocating.
    /// \param number_of_bytes The number of bytes you are allocating/deallocating.
    /// \param is_allocating Indication whether you want to allocate/deallocate.
    [[maybe_unused]] void used_memory(chunk<T>* pointer_to_memory, const std::size_t& number_of_bytes, bool is_allocating = true); // Used for showing messages.

    chunk<T>* m_current_chunk; // This field will hold the address to the current chunk.
    chunk<T>* m_begin_chunk; // This field will hold the address to the first chunk.

    bool m_is_allocated; // This field indicates whether you allocated a chunk.

    std::size_t m_number_of_chunks; // This field indicates the number of chunks per block.
    std::size_t m_size_block; // This field indicates the size of your block with various chunks.
};

// This is the constructor of the 'chunk_list' class.
template<typename T>
chunk_list<T>::chunk_list(const size_t &number_of_chunks) :
    m_current_chunk{nullptr},
    m_begin_chunk{nullptr},
    m_is_allocated{false},
    m_number_of_chunks{number_of_chunks},
    m_size_block{number_of_chunks * sizeof(chunk<T>)}
{}

// This method gets a free chunk from your current block of chunks.
template<typename T>
chunk<T> *chunk_list<T>::get_free_chunk() {
    // Check if you never allocated new memory for you current block.
    if (m_current_chunk == nullptr) {
        auto* allocated_memory = reinterpret_cast<chunk<T>*>(mmap(nullptr, m_size_block, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0)); // Allocate a new memory block with 'mmap'. You can read/write to this memory. Also, the mapping is not mapped to a file.

        // Check if allocating succeeded.
        if (allocated_memory != MAP_FAILED) {
            auto* current_memory_element = allocated_memory; // Indication for your current memory address.

            // Check if you already allocated memory for you block (later block with chunks).
            if (!m_is_allocated) {
                m_begin_chunk = allocated_memory; // Your first memory block.
                m_is_allocated = true; // After this call, you will always have an initial memory block.
            }

            // Go through the allocated block of memory, and divide smaller parts for single chunks. This allows for less fragmentation within you memory.
            for (std::size_t i = 0; i < m_number_of_chunks - 1; i++) {
                current_memory_element->m_next_node = reinterpret_cast<chunk<T>*>(reinterpret_cast<char*>(current_memory_element) + sizeof(chunk<T>)); // Allocate memory for a single chunk out of the bigger block of memory.
                current_memory_element = current_memory_element->m_next_node; // Go to the next chunk, you also want to allocate memory for the next chunk, unless you reached the maximum number of chunks.
            }

            current_memory_element->m_next_node = nullptr; // Last in the block of memory, it must be a 'nullptr'.
            m_current_chunk = allocated_memory; // First element in the allocated block of memory.
        }
        else
            throw std::bad_alloc(); // Allocating failed, throw this exception.
    }

    auto* free_memory_chunk = m_current_chunk; // Get free memory.
    m_current_chunk = m_current_chunk->m_next_node; // Go to the next chunk, your old chunk will be returned (first available place in memory). Allocating here goes in O(1) time.

    return free_memory_chunk; // Return the free chunk.
}

// This method removes a just allocated chunk. Due to that you are using a linked list under the hood, you are only chancing the 'm_next_node' field from this struct.
template<typename T>
void chunk_list<T>::remove_chunk(chunk<T> *free_chunk) noexcept {
    reinterpret_cast<chunk<T>*>(free_chunk)->m_next_node = m_current_chunk; // This chunk is now at the end of your list.
    m_current_chunk = reinterpret_cast<chunk<T>*>(free_chunk); // Your current chunk, if you ask new memory, it will return the address of 'free_chunk'. This is allowed within a memory pool allocator.
}

// This method removes the whole list of chunks. It deallocates the whole block of memory.
template<typename T>
void chunk_list<T>::remove_chunk_list() noexcept {
    // Here, you unmap the just allocated memory. You are passing the first address of the allocated block, together with the number of bytes.
    if (munmap(m_begin_chunk, m_size_block))
        std::cerr << "Deallocating memory failed!" << std::endl; // If this function failed deallocating the memory, print this as standard error.
}

template<typename T>
[[maybe_unused]] void chunk_list<T>::used_memory(chunk<T> *pointer_to_memory, const size_t &number_of_bytes, bool is_allocating) {
    // Show a message of allocating/deallocating.
    std::cout << "---- ALLOCATOR MESSAGE ---- \t" << (is_allocating ? "Allocated memory: " : "Deallocated memory: ")
        << sizeof(T) * number_of_bytes << " bytes at address: " << std::hex << std::showbase << reinterpret_cast<T*>(pointer_to_memory) << std::dec << std::endl;
}

#endif