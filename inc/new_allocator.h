#ifndef ALLOCATOR_NEW_ALLOCATOR_H
#define ALLOCATOR_NEW_ALLOCATOR_H

#include <iostream>
#include <limits>
#include <sys/mman.h>

template <typename T>
class new_allocator {
public:
    [[maybe_unused]] T value_type;

    new_allocator() = default; // You are always using the default constructor for this class.
    ~new_allocator() = default; // You are always using the default destructor for this class.

    template <typename U>
    [[maybe_unused]] constexpr explicit new_allocator (const new_allocator<U>& ) noexcept {}

    [[maybe_unused]] [[nodiscard]] T* allocate(std::size_t number_of_elements);
    [[maybe_unused]] void deallocate(T* allocated_memory, std::size_t number_of_elements) noexcept;

    [[maybe_unused]] [[nodiscard]] std::size_t max_size() const;

    [[maybe_unused]] void construct(T* allocated_memory, const T& value);
    [[maybe_unused]] void destroy(T* object_to_destroy);

private:
    [[maybe_unused]] void used_memory_message(T* pointer_to_memory, std::size_t number_of_bytes, bool is_allocating = true);
};

template<typename T>
[[maybe_unused]] T *new_allocator<T>::allocate(std::size_t number_of_elements) {
    return new T[number_of_elements];
}

template<typename T>
[[maybe_unused]] void new_allocator<T>::deallocate(T *allocated_memory, std::size_t) noexcept {
    delete[] allocated_memory;
}

template<typename T>
[[maybe_unused]] std::size_t new_allocator<T>::max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template<typename T>
[[maybe_unused]] void new_allocator<T>::construct(T *allocated_memory, const T &value) {
    new ((void*) allocated_memory) T(value);
}

template<typename T>
[[maybe_unused]] void new_allocator<T>::destroy(T *object_to_destroy) {
    object_to_destroy->~T();
}

template<typename T>
[[maybe_unused]] void new_allocator<T>::used_memory_message(T *pointer_to_memory, std::size_t number_of_bytes, bool is_allocating) {
    std::cout << "---- ALLOCATOR MESSAGE ---- \t" << (is_allocating ? "Allocated memory: " : "Deallocated memory: ")
        << sizeof(T) * number_of_bytes << " bytes at address: " << std::hex << std::showbase << reinterpret_cast<T*>(pointer_to_memory) << std::dec << std::endl;
}

template <typename T, typename U>
bool operator==(const new_allocator<T>&, const new_allocator<U>&) { return true; }

template <typename T, typename U>
bool operator!=(const new_allocator<T>&, const new_allocator<U>&) { return false; }

#endif