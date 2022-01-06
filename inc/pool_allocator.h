#ifndef ALLOCATOR_POOL_ALLOCATOR_H
#define ALLOCATOR_POOL_ALLOCATOR_H

#include <vector>

#include "block_allocator.h"
#include "chunk_list.h"

template <typename T>
class pool_allocator {
public:
    explicit pool_allocator(const std::size_t& chunk_per_blocks);
    ~pool_allocator();

    [[maybe_unused]] chunk<T>* allocate() noexcept;
    [[maybe_unused]] void deallocate(chunk<T>* release_chunk) noexcept;

private:
    [[maybe_unused]] void used_memory(T* pointer_to_memory, const std::size_t& number_of_bytes, bool is_allocating = true); // Used for showing messages.

    std::vector<chunk_list<T>, block_allocator<chunk_list<T>>> m_block_list;
    chunk_list<T>* m_current_block;
    std::size_t m_current_chunk;
    std::size_t m_chunks_per_block;
};

template<typename T>
pool_allocator<T>::pool_allocator(const std::size_t &chunk_per_blocks) :
    m_block_list{},
    m_current_block{},
    m_current_chunk{chunk_per_blocks},
    m_chunks_per_block{chunk_per_blocks}
{}

template<typename T>
pool_allocator<T>::~pool_allocator() {
    for ([[maybe_unused]] auto& single_block : m_block_list)
        single_block.remove_chunk_list();
}

template<typename T>
[[maybe_unused]] chunk<T> *pool_allocator<T>::allocate() noexcept {
    if (m_current_chunk == m_chunks_per_block) {
        m_block_list.push_back(chunk_list<T>{m_chunks_per_block});
        m_current_block = &m_block_list.back();
        m_current_chunk = 0;
    }

    m_current_chunk++;
    return m_current_block->get_free_chunk();
}

template<typename T>
[[maybe_unused]] void pool_allocator<T>::deallocate(chunk<T>* release_chunk) noexcept {
    m_current_block->remove_chunk(release_chunk);
}

template<typename T>
[[maybe_unused]] void pool_allocator<T>::used_memory(T *pointer_to_memory, const size_t &number_of_bytes, bool is_allocating) {
    std::cout << "---- ALLOCATOR MESSAGE ---- \t" << (is_allocating ? "Allocated memory: " : "Deallocated memory: ")
        << sizeof(T) * number_of_bytes << " bytes at address: " << std::hex << std::showbase << reinterpret_cast<T*>(pointer_to_memory) << std::dec << std::endl;
}

#endif