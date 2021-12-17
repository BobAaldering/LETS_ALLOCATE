#include <vector>
#include "allocator.h"

// Link: https://github.com/alecbz/mmap-allocator/blob/master/mmap_allocator.h
// Link: https://www.codetd.com/en/article/12255921
// Link: https://en.cppreference.com/w/cpp/named_req/Allocator

int main() {
    std::vector<int, memory_map::allocator<int>> vector(8);
    vector.push_back(8);

    return 0;
}
