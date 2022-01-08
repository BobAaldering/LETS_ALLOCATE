#ifndef ALLOCATOR_BLOCK_ALLOCATOR_H
#define ALLOCATOR_BLOCK_ALLOCATOR_H

#include <iostream> // Include here all the 'iostream' facilities.
#include <sys/mman.h> // Include here all the 'sys/mman' facilities.

// ---- EXTRA INFORMATION ---- //
// This class can be used as an allocator for, for instance a vector. This can also operate on different STL-containers.
// But, in this case it is used for allocating new blocks for a memory pool allocator.
// If you want to make an allocator yourself, you should mainly provide it with two methods, in this case an 'allocate' and a 'deallocate' method.
// To allocate and deallocate memory, use is made of the various facilities that Linux offers for this purpose, namely 'mmap' and 'munmap'.
// ---- END EXTRA INFORMATION ---- //

/// This is the template class 'block_allocator', used for allocating memory for a new block for the memory pool allocator.
/// \tparam T The type of this specific class.
template <typename T>
class block_allocator {
public:
    /// You must specify this type definition within an allocator. It is an value type.
    [[maybe_unused]] typedef T value_type;

    /// This method allocates new memory. In this case 'number_of_elements' is always the number of elements that you want to allocate. It is NOT in bytes!
    /// \param number_of_elements The number of elements that you want to allocate memory for. This is NOT in bytes!
    /// \return The first memory address of the allocated block.
    [[maybe_unused]] T* allocate (std::size_t number_of_elements);

    /// This method deallocates the allocated memory, allocated with the 'allocated' method. In this case must 'number_of_elements' be the same value as passed to the earlier called 'allocate' method.
    /// \param memory A pointer to the memory address allocated with the 'allocate' method.
    /// \param number_of_elements The number of elements. It must be the same as just passed to the 'allocate' method.
    [[maybe_unused]] void deallocate(T* memory, std::size_t number_of_elements) noexcept;

private:
    /// This method is just used for debugging purposes, it shows how much memory you just allocated, or you are going to deallocate.
    /// \param pointer_to_memory Memory address of the memory that you are allocating/deallocating.
    /// \param number_of_bytes The number of bytes you are allocating/deallocating.
    /// \param is_allocating Indication whether you want to allocate/deallocate.
    [[maybe_unused]] void used_memory(T* pointer_to_memory, const std::size_t& number_of_bytes, bool is_allocating = true); // Used for showing messages.
};

// This method allocates new memory. In this case 'number_of_elements' is always the number of elements that you want to allocate. It is NOT in bytes!
template<typename T>
[[maybe_unused]] T *block_allocator<T>::allocate(std::size_t number_of_elements) {
    auto* allocated_memory = mmap(nullptr, number_of_elements * sizeof(T), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0); // Allocate a new memory block with 'mmap'. You can read/write to this memory. Also, the mapping is not mapped to a file.

    // Check if allocating new memory succeeded.
    if (allocated_memory == MAP_FAILED)
        throw std::bad_alloc(); // Allocating not succeeded. Throw this exception. Allowed within C++ -> allocating method.

    return reinterpret_cast<T*>(allocated_memory); // Cast the allocated block to your type 'T'.
}

// This method deallocates the allocated memory, allocated with the 'allocated' method. In this case must 'number_of_elements' be the same value as passed to the earlier called 'allocate' method.
template<typename T>
[[maybe_unused]] void block_allocator<T>::deallocate(T *memory, std::size_t number_of_elements) noexcept {
    // Here, you unmap the just allocated memory. You are passing the first address of the allocated block, together with the number of bytes.
    if (munmap(memory, number_of_elements * sizeof(T)))
        std::cerr << "Deallocating memory failed!" << std::endl; // If this function failed deallocating the memory, print this as standard error.
}

// This method is just used for debugging purposes, it shows how much memory you just allocated, or you are going to deallocate.
template<typename T>
[[maybe_unused]] void block_allocator<T>::used_memory(T *pointer_to_memory, const size_t &number_of_bytes, bool is_allocating) {
    // Show a message of allocating/deallocating.
    std::cout << "---- ALLOCATOR MESSAGE ---- \t" << (is_allocating ? "Allocated memory: " : "Deallocated memory: ")
        << sizeof(T) * number_of_bytes << " bytes at address: " << std::hex << std::showbase << reinterpret_cast<T*>(pointer_to_memory) << std::dec << std::endl;
}

#endif