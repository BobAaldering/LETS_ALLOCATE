#ifndef ALLOCATOR_POOL_ALLOCATOR_H
#define ALLOCATOR_POOL_ALLOCATOR_H

#include "chunk_list.h"

template <typename T>
class pool_allocator {
public:
    explicit pool_allocator(const std::size_t& chunk_per_blocks);

    chunk<T>* get_memory() noexcept;
    void back_memory(chunk<T>* release_chunk) noexcept;

    void set_chunks_number(const std::size_t& number_of_chunks) noexcept;

private:
    chunk_list<T> m_memory_list;
};

template<typename T>
pool_allocator<T>::pool_allocator(const std::size_t &chunk_per_blocks) :
    m_memory_list{chunk_per_blocks}
{}

template<typename T>
chunk<T> *pool_allocator<T>::get_memory() noexcept {
    return m_memory_list.get_free_chunk();
}

template<typename T>
void pool_allocator<T>::back_memory(chunk<T>* release_chunk) noexcept {
    m_memory_list.remove_chunk(release_chunk);
}

template<typename T>
void pool_allocator<T>::set_chunks_number(const size_t &number_of_chunks) noexcept {
    m_memory_list.set_chunks_size(number_of_chunks);
}

#endif