#include <vector>
#include "allocator.h"

// Link: https://github.com/alecbz/mmap-allocator/blob/master/mmap_allocator.h
// Link: https://www.codetd.com/en/article/12255921
// Link: https://en.cppreference.com/w/cpp/named_req/Allocator

int main() {
    std::vector<int, memory_map::allocator<int>> vector{};
    vector.push_back(8);
    vector.push_back(9);
    vector.push_back(10);
    vector.push_back(11);
    vector.push_back(12);

    memory_map::allocator<double> alloc{};

    auto* mem = alloc.allocate(45);

    for (int i = 0; i < 45; i++)
        mem[i] = i;

    for (int i = 0; i < 45; i++)
        std::cout << "Value: " << mem[i] << std::endl;

    alloc.deallocate(mem, 45);

    return 0;
}
