#ifndef ALLOCATOR_POOL_ALLOCATOR_H
#define ALLOCATOR_POOL_ALLOCATOR_H

#include <vector> // Include here all the 'vector' facilities.

#include "block_allocator.h" // Include here all the 'block_allocator' facilities.
#include "chunk_list.h" // Include here all the 'chunk_list' facilities.

/// This is the 'pool_allocator' class, that represents a memory pool allocator.
/// \tparam T The type of this specific class.
template <typename T>
class pool_allocator {
public:
    /// This is the constructor of the 'memory_pool' allocator class.
    /// \param chunk_per_blocks This is the number of chunks that a block of memory will contain. This is NOT in bytes!
    explicit pool_allocator(const std::size_t& chunk_per_blocks);

    /// This is the destructor of the 'memory_pool' allocator class.
    ~pool_allocator();

    /// This method allocates memory for a new chunk.
    /// \return The address of an allocated chunk.
    [[maybe_unused]] chunk<T>* allocate();

    /// This method releases memory for an allocated chunk.
    /// \param release_chunk The address of the chunk that you want to deallocate.
    [[maybe_unused]] void deallocate(chunk<T>* release_chunk) noexcept;

private:
    /// This method is just used for debugging purposes, it shows how much memory you just allocated, or you are going to deallocate.
    /// \param pointer_to_memory Memory address of the memory that you are allocating/deallocating.
    /// \param number_of_bytes The number of bytes you are allocating/deallocating.
    /// \param is_allocating Indication whether you want to allocate/deallocate.
    [[maybe_unused]] void used_memory(T* pointer_to_memory, const std::size_t& number_of_bytes, bool is_allocating = true); // Used for showing messages.

    std::vector<chunk_list<T>, block_allocator<chunk_list<T>>> m_block_list; // This field is a vector of blocks, that uses a custom allocator. This is a design decision, so that you can allocate multiple blocks, with chunks. This is allowed within a memory pool allocator.
    chunk_list<T>* m_current_block; // This list of chunks to your current block with not yet allocated chunks.
    std::size_t m_current_chunk; // The number of chunks per block.
    std::size_t m_chunks_per_block; // The number of chunks per block.
};

// This is the constructor of the 'memory_pool' allocator class.
template<typename T>
pool_allocator<T>::pool_allocator(const std::size_t &chunk_per_blocks) :
    m_block_list{},
    m_current_block{nullptr},
    m_current_chunk{chunk_per_blocks},
    m_chunks_per_block{chunk_per_blocks}
{}

// This is the destructor of the 'memory_pool' allocator class.
template<typename T>
pool_allocator<T>::~pool_allocator() {
    // Go through all the blocks, deallocate the memory for the list of chunks.
    for ([[maybe_unused]] auto& single_block : m_block_list)
        single_block.remove_chunk_list();
}

// This method allocates memory for a new chunk.
template<typename T>
[[maybe_unused]] chunk<T> *pool_allocator<T>::allocate() {
    // Check if you have not reached the end of a block.
    if (m_current_chunk == m_chunks_per_block) {
        m_block_list.push_back(chunk_list<T>{m_chunks_per_block}); // Create a new block with chunks.
        m_current_block = &m_block_list.back(); // Change your current block.
        m_current_chunk = 0; // Your number of chunk is zero, you can allocate new memory.
    }

    m_current_chunk++; // Increment the number of chunks that indicates the amount of allocated memory.
    return m_current_block->get_free_chunk(); // Get a free chunk.
}

// This method releases memory for an allocated chunk.
template<typename T>
[[maybe_unused]] void pool_allocator<T>::deallocate(chunk<T>* release_chunk) noexcept {
    m_current_block->remove_chunk(release_chunk); // Remove a specific chunk.
    m_current_chunk--; // You freed a chunk, decrement the number of allocated chunks for your current block.
}

// This method is just used for debugging purposes, it shows how much memory you just allocated, or you are going to deallocate.
template<typename T>
[[maybe_unused]] void pool_allocator<T>::used_memory(T *pointer_to_memory, const size_t &number_of_bytes, bool is_allocating) {
    // Show a message of allocating/deallocating.
    std::cout << "---- ALLOCATOR MESSAGE ---- \t" << (is_allocating ? "Allocated memory: " : "Deallocated memory: ")
        << sizeof(T) * number_of_bytes << " bytes at address: " << std::hex << std::showbase << reinterpret_cast<T*>(pointer_to_memory) << std::dec << std::endl;
}

#endif