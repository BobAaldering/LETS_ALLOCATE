#ifndef ALLOCATOR_MALLOC_ALLOCATOR_H
#define ALLOCATOR_MALLOC_ALLOCATOR_H

#include <iostream>
#include <cstdlib>

template <typename T>
class malloc_allocator {
public:
    [[maybe_unused]] T value_type;

    malloc_allocator() = default; // You are always using the default constructor for this class.
    ~malloc_allocator() = default; // You are always using the default destructor for this class.

    template <typename U>
    [[maybe_unused]] constexpr explicit malloc_allocator (const malloc_allocator<U>& ) noexcept {}

    [[maybe_unused]] [[nodiscard]] T* allocate(std::size_t number_of_elements);
    [[maybe_unused]] void deallocate(T* allocated_memory, std::size_t number_of_elements) noexcept;

    [[maybe_unused]] [[nodiscard]] std::size_t max_size() const;

    [[maybe_unused]] void construct(T* allocated_memory, const T& value);
    [[maybe_unused]] void destroy(T* object_to_destroy);

private:
    [[maybe_unused]] void used_memory_message(T* pointer_to_memory, std::size_t number_of_bytes, bool is_allocating = true);
};

template<typename T>
[[maybe_unused]] T *malloc_allocator<T>::allocate(std::size_t number_of_elements) {
    if (auto* allocated_memory = std::malloc(number_of_elements * sizeof(T)))
        return reinterpret_cast<T*>(allocated_memory);

    throw std::bad_alloc();
}

template<typename T>
[[maybe_unused]] void malloc_allocator<T>::deallocate(T *allocated_memory, std::size_t) noexcept {
    std::free(allocated_memory);
}

template<typename T>
[[maybe_unused]] std::size_t malloc_allocator<T>::max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template<typename T>
[[maybe_unused]] void malloc_allocator<T>::construct(T *allocated_memory, const T &value) {
    new ((void*) allocated_memory) T(value);
}

template<typename T>
[[maybe_unused]] void malloc_allocator<T>::destroy(T *object_to_destroy) {
    object_to_destroy->~T();
}

template<typename T>
[[maybe_unused]] void malloc_allocator<T>::used_memory_message(T *pointer_to_memory, std::size_t number_of_bytes, bool is_allocating) {
    std::cout << "---- ALLOCATOR MESSAGE ---- \t" << (is_allocating ? "Allocated memory: " : "Deallocated memory: ")
              << sizeof(T) * number_of_bytes << " bytes at address: " << std::hex << std::showbase << reinterpret_cast<T*>(pointer_to_memory) << std::dec << std::endl;
}

template <typename T, typename U>
bool operator==(const malloc_allocator<T>&, const malloc_allocator<U>&) { return true; }

template <typename T, typename U>
bool operator!=(const malloc_allocator<T>&, const malloc_allocator<U>&) { return false; }

#endif
