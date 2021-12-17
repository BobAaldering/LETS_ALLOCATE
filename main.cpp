#include <iostream>
#include <sys/mman.h>

// Link: https://github.com/alecbz/mmap-allocator/blob/master/mmap_allocator.h

int main() {
    auto* ptr = static_cast<int*>(mmap(nullptr, 5 * sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 ));

    for (int i = 0; i < 5; i++) {
        *(ptr + i) = i;
        std::cout << "Memory address: " << (ptr + i) << ", value: " << *(ptr + i) << std::endl;
    }

    if (munmap(ptr, 5 * sizeof(int))) // Release the memory.
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS;
}
