#ifndef ALLOCATOR_ALLOCATOR_H
#define ALLOCATOR_ALLOCATOR_H

#include <iostream>
#include <limits>
#include <sys/mman.h>

namespace memory_map {
    template <typename T>
    class allocator {
    public:
        typedef T value_type;

        allocator() = default;

        template<class U> constexpr explicit allocator (const allocator<U>&) noexcept {}

        [[nodiscard]] T* allocate(std::size_t number_of_elements) {
            if (number_of_elements > (std::numeric_limits<std::size_t>::max() / sizeof(T)))
                throw std::bad_array_new_length();

            if (auto ptr = static_cast<T*>(mmap(nullptr, number_of_elements, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0))) {
                used_memory_message(ptr, number_of_elements);
                return ptr;
            }

            throw std::bad_alloc();
        }

        void deallocate(T* ptr, std::size_t number_of_elements) noexcept {
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