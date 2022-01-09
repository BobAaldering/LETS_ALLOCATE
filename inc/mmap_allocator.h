#ifndef ALLOCATOR_MMAP_ALLOCATOR_H
#define ALLOCATOR_MMAP_ALLOCATOR_H

#include <iostream> // Include here all the 'iostream' facilities.
#include <limits> // Include here all the 'limits' facilities.
#include <sys/mman.h> // Include here all the 'sys/mman' facilities.

// ---- EXTRA INFORMATION ---- //
// This class can be used as an allocator for, for instance a vector. This can also operate on different STL-containers.
// But, in this case it is used for allocating new memory with 'mmap'.
// If you want to make an allocator yourself, you should mainly provide it with two methods, in this case an 'allocate' and a 'deallocate' method.
// PAY ATTENTION! This class was developed by also testing the speed of 'malloc' within the benchmarker. In addition, they practice by making their own allocator. But the purpose of this class is to only test 'mmap' within the benchmarker.
// ---- END EXTRA INFORMATION ---- //

/// This is the class 'mmap_allocator', used for allocating memory with 'mmap'.
/// \tparam T The type of this specific class.
template <typename T>
class mmap_allocator {
public:
    /// You must specify this type definition within an allocator. It is an value type.
    [[maybe_unused]] typedef T value_type;

    /// This is the constructor of the 'mmap_allocator' class. It is a default constructor.
    mmap_allocator() = default;
    /// This is the destructor of the 'mmap_allocator' class. It is a default destructor.
    ~mmap_allocator() = default;

    /// The constexpr constructor for this allocator.
    /// \tparam U The type of 'mmap_allocator' U.
    template <typename U>
    [[maybe_unused]] constexpr explicit mmap_allocator (const mmap_allocator<U>& ) noexcept {}

    /// This method allocates new memory. In this case 'number_of_elements' is always the number of elements that you want to allocate. It is NOT in bytes!
    /// \param number_of_elements The number of elements that you want to allocate memory for. This is NOT in bytes!
    /// \return The first memory address of the allocated block of memory.
    [[maybe_unused]] [[nodiscard]] T* allocate(std::size_t number_of_elements);

    /// This method deallocates the allocated memory, allocated with the 'allocated' method. In this case must 'number_of_elements' be the same value as passed to the earlier called 'allocate' method.
    /// \param memory A pointer to the memory address allocated with the 'allocate' method.
    /// \param number_of_elements The number of elements. It must be the same as just passed to the 'allocate' method.
    [[maybe_unused]] void deallocate(T* allocated_memory, std::size_t number_of_elements) noexcept;

    /// This method returns the maximum size that you can allocate.
    /// \return The number of the maximum amount that you can allocate.
    [[maybe_unused]] [[nodiscard]] std::size_t max_size() const;

    /// This method constructs your type 'T'. Is has nothing to do with allocating memory with 'mmap'.
    /// \param allocated_memory The address of the allocated memory with 'mmap'.
    /// \param value The value that you want to construct.
    [[maybe_unused]] void construct(T* allocated_memory, const T& value);

    /// This method destroys your type 'T'. It has nothing to do with deallocating memory with 'munmap'.
    /// \param object_to_destroy The address to the allocated memory, whereby you want to destroy its object.
    [[maybe_unused]] void destroy(T* object_to_destroy);

private:
    /// This method is just used for debugging purposes, it shows how much memory you just allocated, or you are going to deallocate.
    /// \param pointer_to_memory Memory address of the memory that you are allocating/deallocating.
    /// \param number_of_bytes The number of bytes you are allocating/deallocating.
    /// \param is_allocating Indication whether you want to allocate/deallocate.
    [[maybe_unused]] void used_memory_message(T* pointer_to_memory, std::size_t number_of_bytes, bool is_allocating = true);
};

// This method allocates new memory. In this case 'number_of_elements' is always the number of elements that you want to allocate. It is NOT in bytes!
template<typename T>
[[maybe_unused]] T *mmap_allocator<T>::allocate(std::size_t number_of_elements) {
    auto* allocated_memory = mmap(nullptr, number_of_elements * sizeof(T), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0); // Allocate a new memory block with 'mmap'. You can read/write to this memory. Also, the mapping is not mapped to a file.

    // Check if allocating new memory succeeded.
    if (allocated_memory == MAP_FAILED)
        throw std::bad_alloc(); // Allocating not succeeded. Throw this exception. Allowed within C++ -> allocating method.

    return reinterpret_cast<T*>(allocated_memory); // Cast the allocated block to your type 'T'.
}

// This method deallocates the allocated memory, allocated with the 'allocated' method. In this case must 'number_of_elements' be the same value as passed to the earlier called 'allocate' method.
template<typename T>
[[maybe_unused]] void mmap_allocator<T>::deallocate(T *allocated_memory, std::size_t number_of_elements) noexcept {
    // Here, you unmap the just allocated memory. You are passing the first address of the allocated block, together with the number of bytes.
    if (munmap(allocated_memory, number_of_elements * sizeof(T)))
        std::cerr << "Deallocating memory failed!" << std::endl; // If this function failed deallocating the memory, print this as standard error.
}

// This method returns the maximum size that you can allocate.
template<typename T>
[[maybe_unused]] std::size_t mmap_allocator<T>::max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T); // Calculate the amount of allocating memory.
}

// This method constructs your type 'T'. Is has nothing to do with allocating memory with 'mmap'.
template<typename T>
[[maybe_unused]] void mmap_allocator<T>::construct(T *allocated_memory, const T &value) {
    new ((void*) allocated_memory) T(value); // Construct object 'T'. You are using 'placement new', that is different from allocating.
}

// This method destroys your type 'T'. It has nothing to do with deallocating memory with 'munmap'.
template<typename T>
[[maybe_unused]] void mmap_allocator<T>::destroy(T *object_to_destroy) {
    object_to_destroy->~T(); // Destruct the object of 'T'.
}

// This method is just used for debugging purposes, it shows how much memory you just allocated, or you are going to deallocate.
template<typename T>
[[maybe_unused]] void mmap_allocator<T>::used_memory_message(T *pointer_to_memory, std::size_t number_of_bytes, bool is_allocating) {
    // Show a message of allocating/deallocating.
    std::cout << "---- ALLOCATOR MESSAGE ---- \t" << (is_allocating ? "Allocated memory: " : "Deallocated memory: ")
        << sizeof(T) * number_of_bytes << " bytes at address: " << std::hex << std::showbase << reinterpret_cast<T*>(pointer_to_memory) << std::dec << std::endl;
}

/// This operator compares two 'mmap' allocators.
/// \tparam T The type of this specific class.
/// \tparam U The type of this specific class.
/// \return This operator normally returns always true.
template <typename T, typename U>
bool operator==(const mmap_allocator<T>&, const mmap_allocator<U>&) { return true; }

/// This operator compares two 'mmap' allocators.
/// \tparam T The type of this specific class.
/// \tparam U The type of this specific class.
/// \return This operator normally returns always false.
template <typename T, typename U>
bool operator!=(const mmap_allocator<T>&, const mmap_allocator<U>&) { return false; }

#endif