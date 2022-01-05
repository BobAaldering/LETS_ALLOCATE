#ifndef ALLOCATOR_ALLOCATOR_H
#define ALLOCATOR_ALLOCATOR_H

#include <iostream>
#include <limits>
#include <sys/mman.h>

namespace memory_map {
    template <typename T>
    class allocator {
    public:
        [[maybe_unused]] typedef T value_type;
        [[maybe_unused]] typedef T* pointer;
        [[maybe_unused]] typedef const T* const_pointer;
        [[maybe_unused]] typedef T& reference;
        [[maybe_unused]] typedef const T& const_reference;
        [[maybe_unused]] typedef std::size_t size_type;
        [[maybe_unused]] typedef std::ptrdiff_t difference_type;

        // This is for rebinding to the type 'U'.
        template<class U>
        struct [[maybe_unused]] rebind {
            [[maybe_unused]] typedef allocator<U> other_allocator;
        };

        // Return the address of your 'value', you can modify its content.
        [[maybe_unused]] pointer address(reference value) const {
            return &value;
        }

        // Return the address of your 'value', you cannot modify its content, because its constant.
        [[maybe_unused]] const_pointer address(const_reference value) const {
            return &value;
        }

        // Use default constructors, because 'allocator' will have no state.
        allocator() noexcept = default;
        allocator(const allocator&) noexcept = default;
        ~allocator() noexcept = default;

        [[nodiscard]] size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(T);
        }

        template<class U> constexpr explicit allocator (const allocator<U>&) noexcept {}

        [[maybe_unused]] [[nodiscard]] T* allocate(std::size_t number_of_elements) {
            if (number_of_elements > max_size())
                throw std::bad_array_new_length();

            if (auto* ptr = reinterpret_cast<T*>(mmap(nullptr, number_of_elements * sizeof(T), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0))) {
                used_memory_message(ptr, number_of_elements);
                return ptr;
            }

            throw std::bad_alloc();
        }

        // Constructs an object of the type in you previously-allocated storage at the address pointed to 'ptr', using 'value' as the constructor arguments.
        [[maybe_unused]] void construct(pointer ptr, const_reference value) {
            new ((void*)ptr) T(value);
        }

        [[maybe_unused]] void destroy(pointer ptr) {
            ptr->~T();
        }

        [[maybe_unused]] void deallocate(T* ptr, std::size_t number_of_elements) noexcept {
            used_memory_message(ptr, number_of_elements, false);
            if (munmap(ptr, number_of_elements))
                std::cerr << "Deallocating memory failed!" << std::endl;
        }

    private:
        void used_memory_message(T* ptr, std::size_t number_of_elements, bool allocate = true) {
            std::cout
                << (allocate ? "Allocated memory: " : "Deallocated memory: ")
                << sizeof(T) * number_of_elements
                << " bytes at: "
                << std::hex
                << std::showbase
                << reinterpret_cast<void*>(ptr)
                << std::dec
                << std::endl;
        }
    };

    template <typename T, typename U>
    bool operator==(const allocator<T>&, const allocator<U>&) noexcept {
        return true;
    }

    template <typename T, typename U>
    bool operator!=(const allocator<T>&, const allocator<U>&) noexcept {
        return false;
    }
}

#endif