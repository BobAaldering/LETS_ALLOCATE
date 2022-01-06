#include "allocator_tester.h"

void allocator_tester::pool_validate_int() {
    std::cout << "---- MEMORY POOL VALIDATOR INTEGERS ----" << std::endl;
    std::cout << "Initializing... Creating a 'memory pool' with 3 chunks (integers)..." << std::endl;

    pool_allocator<int> allocator{3};
    std::vector<chunk<int>*> integer_vec_allocated{};

    for (const auto& single_number : {1, 2, 3, 4, 5}) {
        auto chunk_of_data = allocator.allocate();
        chunk_of_data->m_data = single_number;
        integer_vec_allocated.push_back(chunk_of_data);
    }

    ASSERT_EQ(1, integer_vec_allocated[0]->m_data, "The expected value is 1!")
    ASSERT_EQ(2, integer_vec_allocated[1]->m_data, "The expected value is 2!")
    ASSERT_EQ(3, integer_vec_allocated[2]->m_data, "The expected value is 3!")
    ASSERT_EQ(4, integer_vec_allocated[3]->m_data, "The expected value is 4!")
    ASSERT_EQ(5, integer_vec_allocated[4]->m_data, "The expected value is 5!")

    allocator.deallocate(integer_vec_allocated.back());
    integer_vec_allocated.pop_back();

    allocator.deallocate(integer_vec_allocated.back());
    integer_vec_allocated.pop_back();

    ASSERT_EQ(1, integer_vec_allocated[0]->m_data, "The expected value is 1!")
    ASSERT_EQ(2, integer_vec_allocated[1]->m_data, "The expected value is 2!")
    ASSERT_EQ(3, integer_vec_allocated[2]->m_data, "The expected value is 3!")

    for (const auto& single_number : {8, 9, 10}) {
        auto chunk_of_data = allocator.allocate();
        chunk_of_data->m_data = single_number;
        integer_vec_allocated.push_back(chunk_of_data);
    }

    ASSERT_EQ(8, integer_vec_allocated[3]->m_data, "The expected value is 8!")
    ASSERT_EQ(9, integer_vec_allocated[4]->m_data, "The expected value is 9!")
    ASSERT_EQ(10, integer_vec_allocated[5]->m_data, "The expected value is 10!")

    std::cout << "---- END MEMORY POOL VALIDATOR INTEGERS ----" << std::endl;
}

void allocator_tester::pool_validate_double() {
    std::cout << "---- MEMORY POOL VALIDATOR DOUBLES ----" << std::endl;
    std::cout << "Initializing... Creating a 'memory pool' with 3 chunks (doubles)..." << std::endl;

    pool_allocator<double> allocator{3};
    std::vector<chunk<double>*> double_vec_allocated{};

    for (const auto& single_number : {1.1, 2.1, 3.1, 4.1, 5.1}) {
        auto chunk_of_data = allocator.allocate();
        chunk_of_data->m_data = single_number;
        double_vec_allocated.push_back(chunk_of_data);
    }

    ASSERT_EQ(1.1, double_vec_allocated[0]->m_data, "The expected value is 1.1!")
    ASSERT_EQ(2.1, double_vec_allocated[1]->m_data, "The expected value is 2.1!")
    ASSERT_EQ(3.1, double_vec_allocated[2]->m_data, "The expected value is 3.1!")
    ASSERT_EQ(4.1, double_vec_allocated[3]->m_data, "The expected value is 4.1!")
    ASSERT_EQ(5.1, double_vec_allocated[4]->m_data, "The expected value is 5.1!")

    allocator.deallocate(double_vec_allocated.back());
    double_vec_allocated.pop_back();

    allocator.deallocate(double_vec_allocated.back());
    double_vec_allocated.pop_back();

    ASSERT_EQ(1.1, double_vec_allocated[0]->m_data, "The expected value is 1.1!")
    ASSERT_EQ(2.1, double_vec_allocated[1]->m_data, "The expected value is 2.1!")
    ASSERT_EQ(3.1, double_vec_allocated[2]->m_data, "The expected value is 3.1!")

    for (const auto& single_number : {8.8, 9.8, 10.1}) {
        auto chunk_of_data = allocator.allocate();
        chunk_of_data->m_data = single_number;
        double_vec_allocated.push_back(chunk_of_data);
    }

    ASSERT_EQ(8.8, double_vec_allocated[3]->m_data, "The expected value is 8.8!")
    ASSERT_EQ(9.8, double_vec_allocated[4]->m_data, "The expected value is 9.8!")
    ASSERT_EQ(10.1, double_vec_allocated[5]->m_data, "The expected value is 10.1!")

    std::cout << "---- END MEMORY POOL VALIDATOR DOUBLES ----" << std::endl;
}

void allocator_tester::pool_validate_compound() {
    struct task_compound {
        int m_priority;
        std::string m_person_to_task;
    };

    std::cout << "---- MEMORY POOL VALIDATOR COMPOUND TYPE ----" << std::endl;
    std::cout << "Initializing... Creating a 'memory pool' with 3 chunks (compound types - 'task_compound')..." << std::endl;

    pool_allocator<task_compound> allocator{3};
    std::vector<chunk<task_compound>*> task_vec_allocated{};

    for (const auto& single_task : {task_compound{1, "Alice"}, task_compound{4, "Bob"}, task_compound{1, "Eve"}, task_compound{7, "Sam"}, task_compound{9, "Robert"}}) {
        auto chunk_of_data = allocator.allocate();
        chunk_of_data->m_data = single_task;
        task_vec_allocated.push_back(chunk_of_data);
    }

    ASSERT_EQ("Alice", task_vec_allocated[0]->m_data.m_person_to_task, "The expected value is 'Alice'!")
    ASSERT_EQ("Bob", task_vec_allocated[1]->m_data.m_person_to_task, "The expected value is 'Bob'!")
    ASSERT_EQ("Eve", task_vec_allocated[2]->m_data.m_person_to_task, "The expected value is 'Eve'!")
    ASSERT_EQ("Sam", task_vec_allocated[3]->m_data.m_person_to_task, "The expected value is 'Sam'!")
    ASSERT_EQ("Robert", task_vec_allocated[4]->m_data.m_person_to_task, "The expected value is 'Robert'!")

    ASSERT_EQ(1, task_vec_allocated[0]->m_data.m_priority, "The expected value is 1!")
    ASSERT_EQ(4, task_vec_allocated[1]->m_data.m_priority, "The expected value is 4!")
    ASSERT_EQ(1, task_vec_allocated[2]->m_data.m_priority, "The expected value is 1!")
    ASSERT_EQ(7, task_vec_allocated[3]->m_data.m_priority, "The expected value is 7!")
    ASSERT_EQ(9, task_vec_allocated[4]->m_data.m_priority, "The expected value is 9!")

    allocator.deallocate(task_vec_allocated.back());
    task_vec_allocated.pop_back();

    allocator.deallocate(task_vec_allocated.back());
    task_vec_allocated.pop_back();

    ASSERT_EQ("Alice", task_vec_allocated[0]->m_data.m_person_to_task, "The expected value is 'Alice'!")
    ASSERT_EQ("Bob", task_vec_allocated[1]->m_data.m_person_to_task, "The expected value is 'Bob'!")
    ASSERT_EQ("Eve", task_vec_allocated[2]->m_data.m_person_to_task, "The expected value is 'Eve'!")

    ASSERT_EQ(1, task_vec_allocated[0]->m_data.m_priority, "The expected value is 1!")
    ASSERT_EQ(4, task_vec_allocated[1]->m_data.m_priority, "The expected value is 4!")
    ASSERT_EQ(1, task_vec_allocated[2]->m_data.m_priority, "The expected value is 1!")

    for (const auto& single_task : {task_compound{11, "John"}, task_compound{44, "Gina"}, task_compound{11, "Jade"}}) {
        auto chunk_of_data = allocator.allocate();
        chunk_of_data->m_data = single_task;
        task_vec_allocated.push_back(chunk_of_data);
    }

    ASSERT_EQ("John", task_vec_allocated[3]->m_data.m_person_to_task, "The expected value is 'John'!")
    ASSERT_EQ("Gina", task_vec_allocated[4]->m_data.m_person_to_task, "The expected value is 'Gina'!")
    ASSERT_EQ("Jade", task_vec_allocated[5]->m_data.m_person_to_task, "The expected value is 'Jade'!")

    ASSERT_EQ(11, task_vec_allocated[3]->m_data.m_priority, "The expected value is 11!")
    ASSERT_EQ(44, task_vec_allocated[4]->m_data.m_priority, "The expected value is 44!")
    ASSERT_EQ(11, task_vec_allocated[5]->m_data.m_priority, "The expected value is 11!")

    std::cout << "---- END MEMORY POOL VALIDATOR COMPOUND TYPE ----" << std::endl;
}