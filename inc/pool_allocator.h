#ifndef ALLOCATOR_POOL_ALLOCATOR_H
#define ALLOCATOR_POOL_ALLOCATOR_H

#include <vector>

#include "block_allocator.h"
#include "chunk_list.h"

template <typename T>
class pool_allocator {
public:
    explicit pool_allocator(const std::size_t& chunk_per_blocks);

    chunk<T>* get_memory() noexcept;
    void back_memory(chunk<T>* release_chunk) noexcept;

    void release_blocks() noexcept;

private:
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
chunk<T> *pool_allocator<T>::get_memory() noexcept {
    if (m_current_chunk == m_chunks_per_block) {
        m_block_list.push_back(chunk_list<T>{m_chunks_per_block});
        m_current_block = &m_block_list.back();
        m_current_chunk = 0;
    }

    m_current_chunk++;
    return m_current_block->get_free_chunk();
}

template<typename T>
void pool_allocator<T>::back_memory(chunk<T>* release_chunk) noexcept {
    m_current_block->remove_chunk(release_chunk);
}

template<typename T>
void pool_allocator<T>::release_blocks() noexcept {
    for ([[maybe_unused]] auto& single_block : m_block_list)
        single_block.remove_chunk_list();
}

#endif