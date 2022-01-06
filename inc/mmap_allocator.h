#ifndef ALLOCATOR_MMAP_ALLOCATOR_H
#define ALLOCATOR_MMAP_ALLOCATOR_H

#include <iostream>
#include <limits>
#include <sys/mman.h>

template <typename T>
class mmap_allocator {
public:
    [[maybe_unused]] T value_type;

    mmap_allocator() = default; // You are always using the default constructor for this class.
    ~mmap_allocator() = default; // You are always using the default destructor for this class.

    template <typename U>
    [[maybe_unused]] constexpr explicit mmap_allocator (const mmap_allocator<U>& ) noexcept {}

    [[nodiscard]] T* allocate(std::size_t number_of_elements);
    void deallocate(T* allocated_memory, std::size_t number_of_elements) noexcept;

    [[maybe_unused]] [[nodiscard]] std::size_t max_size() const;

    [[maybe_unused]] void construct(T* allocated_memory, const T& value);
    [[maybe_unused]] void destroy(T* object_to_destroy);

private:
    [[maybe_unused]] void used_memory_message(T* pointer_to_memory, std::size_t number_of_bytes, bool is_allocating = true);
};

template<typename T>
[[maybe_unused]] T *mmap_allocator<T>::allocate(std::size_t number_of_elements) {
    auto* allocated_memory = mmap(nullptr, number_of_elements * sizeof(T), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    if (allocated_memory == MAP_FAILED)
        throw std::bad_alloc();

    return reinterpret_cast<T*>(allocated_memory);
}

template<typename T>
[[maybe_unused]] void mmap_allocator<T>::deallocate(T *allocated_memory, std::size_t number_of_elements) noexcept {
    if (munmap(allocated_memory, number_of_elements * sizeof(T)))
        std::cerr << "Deallocating memory failed!" << std::endl;
}

template<typename T>
[[maybe_unused]] std::size_t mmap_allocator<T>::max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template<typename T>
[[maybe_unused]] void mmap_allocator<T>::construct(T *allocated_memory, const T &value) {
    new ((void*) allocated_memory) T(value);
}

template<typename T>
[[maybe_unused]] void mmap_allocator<T>::destroy(T *object_to_destroy) {
    object_to_destroy->~T();
}

template<typename T>
[[maybe_unused]] void mmap_allocator<T>::used_memory_message(T *pointer_to_memory, std::size_t number_of_bytes, bool is_allocating) {
    std::cout << "---- ALLOCATOR MESSAGE ---- \t" << (is_allocating ? "Allocated memory: " : "Deallocated memory: ")
        << sizeof(T) * number_of_bytes << " bytes at address: " << std::hex << std::showbase << reinterpret_cast<T*>(pointer_to_memory) << std::dec << std::endl;
}

template <typename T, typename U>
bool operator==(const mmap_allocator<T>&, const mmap_allocator<U>&) { return true; }

template <typename T, typename U>
bool operator!=(const mmap_allocator<T>&, const mmap_allocator<U>&) { return false; }

#endif