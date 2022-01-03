#include "pool_allocator.h"

int main() {
    pool_allocator<int> allocator{3};

    auto first_value = allocator.get_memory();
    auto second_value = allocator.get_memory();
    auto third_value = allocator.get_memory();
    auto fourth_value = allocator.get_memory();

    first_value->m_data = 5;
    second_value->m_data = 6;
    third_value->m_data = 7;
    fourth_value->m_data = 8;

    std::cout << "First value: " << first_value->m_data << std::endl;
    std::cout << "Second value: " << second_value->m_data << std::endl;
    std::cout << "Third value: " << third_value->m_data << std::endl;
    std::cout << "Fourth value: " << fourth_value->m_data << std::endl;

    allocator.release_blocks();

    return 0;
}