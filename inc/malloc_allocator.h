#ifndef ALLOCATOR_MALLOC_ALLOCATOR_H
#define ALLOCATOR_MALLOC_ALLOCATOR_H

#include <cstdlib>
#include <iostream>

template <typename T>
struct chunk;

template <typename T>
class malloc_allocator {
public:
    explicit malloc_allocator(const std::size_t& number_of_elements);

    T* allocate();
    void deallocate(T* ptr);

private:
    std::size_t m_size_memory;
};

template<typename T>
malloc_allocator<T>::malloc_allocator(const size_t &number_of_elements) :
    m_size_memory{number_of_elements * sizeof(int)}
{}

template<typename T>
T *malloc_allocator<T>::allocate() {
    return reinterpret_cast<T*>(malloc(m_size_memory));
}

template<typename T>
void malloc_allocator<T>::deallocate(T *ptr) {
    free(ptr);
}

#endif