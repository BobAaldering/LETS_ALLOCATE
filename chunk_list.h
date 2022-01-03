#ifndef ALLOCATOR_CHUNK_LIST_H
#define ALLOCATOR_CHUNK_LIST_H

#include <cstddef>
#include <sys/mman.h>

template <typename T>
struct chunk {
    T m_data; // This is your data.
    chunk* m_next_node; // This is the value to the next node.
};

template <typename T>
class chunk_list {
public:
    explicit chunk_list(const std::size_t& number_of_chunks);

    chunk<T>* get_free_chunk() noexcept;
    void remove_chunk(chunk<T>* free_chunk) noexcept;

    void set_chunks_size(const std::size_t& number_of_chunks) noexcept;

    ~chunk_list();

private:
    chunk<T>* m_current_chunk;
    chunk<T>* m_begin_chunk;

    bool m_is_allocated;

    std::size_t m_number_of_chunks;
    std::size_t m_size_block;
};

template<typename T>
chunk_list<T>::chunk_list(const size_t &number_of_chunks) :
    m_current_chunk{nullptr},
    m_begin_chunk{nullptr},
    m_is_allocated{false},
    m_number_of_chunks{number_of_chunks},
    m_size_block{number_of_chunks * sizeof(chunk<T>)}
{}

template<typename T>
chunk<T> *chunk_list<T>::get_free_chunk() noexcept {
    if (m_current_chunk == nullptr) {
        if (auto allocated_memory = reinterpret_cast<chunk<T>*>(mmap(nullptr, m_size_block, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0))) {
            auto* current_memory_element = allocated_memory;

            if (!m_is_allocated) {
                m_begin_chunk = allocated_memory; // Your first memory block.
                m_is_allocated = true; // After this call, you will always have an initial memory block.
            }

            for (std::size_t i = 0; i < m_number_of_chunks; i++) {
                current_memory_element->m_next_node = reinterpret_cast<chunk<T>*>(reinterpret_cast<char*>(current_memory_element) + sizeof(chunk<T>));
                current_memory_element = current_memory_element->m_next_node;
            }

            current_memory_element->m_next_node = nullptr; // Last in the block of memory, it must be a 'nullptr'.
            m_current_chunk = allocated_memory; // First element in the allocated block of memory.
        }
    }

    auto* free_memory_chunk = m_current_chunk;
    m_current_chunk = m_current_chunk->m_next_node; // Go to the next chunk, your old chunk will be returned (first available place in memory).

    return free_memory_chunk;
}

template<typename T>
void chunk_list<T>::remove_chunk(chunk<T> *free_chunk) noexcept {
    reinterpret_cast<chunk<T>*>(free_chunk)->m_next_node = m_current_chunk;
    m_current_chunk = reinterpret_cast<chunk<T>*>(free_chunk);
}

template<typename T>
chunk_list<T>::~chunk_list() {
    auto* current_chunk = m_begin_chunk;
    while (current_chunk != nullptr) {
        auto* temp_chunk = current_chunk->m_next_node;
        munmap(temp_chunk, sizeof(chunk<T>)); // Delete your 'current_chunk'.
        current_chunk = temp_chunk;
    }
}

template<typename T>
void chunk_list<T>::set_chunks_size(const std::size_t &number_of_chunks) noexcept {
    m_number_of_chunks = number_of_chunks;
    m_size_block = m_number_of_chunks * sizeof(chunk<T>);
}

#endif