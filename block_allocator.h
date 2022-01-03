#ifndef ALLOCATOR_BLOCK_ALLOCATOR_H
#define ALLOCATOR_BLOCK_ALLOCATOR_H

#include <iostream>
#include <sys/mman.h>

template <typename T>
class block_allocator {
public:
    typedef T value_type;

    T* allocate (std::size_t number_of_elements);
    void deallocate(T* memory, std::size_t number_of_elements) noexcept;

private:
    void used_memory(T* pointer_to_memory, const std::size_t& number_of_bytes, bool is_allocating = true);
};

template<typename T>
T *block_allocator<T>::allocate(std::size_t number_of_elements) {
    if (auto* allocated_memory = reinterpret_cast<T*>(mmap(nullptr, number_of_elements, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0))) {
        used_memory(allocated_memory, number_of_elements);
        return allocated_memory;
    }

    return nullptr;
}

template<typename T>
void block_allocator<T>::deallocate(T *memory, std::size_t number_of_elements) noexcept {
    used_memory(memory, number_of_elements, false);
    if (munmap(memory, number_of_elements))
        std::cerr << "Deallocating memory failed!" << std::endl;
}

template<typename T>
void block_allocator<T>::used_memory(T *pointer_to_memory, const size_t &number_of_bytes, bool is_allocating) {
    std::cout << (is_allocating ? "Allocated memory: " : "Deallocated memory: ")
        << sizeof(T) * number_of_bytes << " bytes at address: " << std::hex << std::showbase << reinterpret_cast<T*>(pointer_to_memory) << std::dec << std::endl;
}

#endif