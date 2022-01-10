# Let's allocate!
#### By: Bob Aaldering (492152) and Nian Luisman (496439)

Everything revolves around memory, even in a computer program. In order to allocate memory in a lower-level programming language, you have to do it all yourself. In C++ you can use `::operator new` to dynamically allocate memory. To release this memory, use `::operator delete`. In C, on the other hand, you use the functions `malloc()` and `free()`. However, allocating memory with the functions mentioned above is a complex problem.

This repository explains the problems of dynamic memory allocation. In addition, research is given on how memory is allocated dynamically, what the algorithms are on this type of memory. Also given are pros and cons of using the functions that allocate memory in both C++ and C. Finally, several implementations of allocators are also given, for example a proprietary implementation of `std::allocator` and a `memory_pool_allocator` .

## Prose

To clarify allocators, a [prose](PROSE.md) has been generated. It is written in a formal format, with extensive explanations on various topics.
An explanation of the topic follows, in which the complex problem surrounding allocators is clarified. It also mentions why allocators are important in acquiring programming experience. Following is the actual content, which gives everything about allocators needed to know all about it!
To give various applications, code snippets are also given, where explanation is also given. 
In addition to theoretical aspects related to this subject, you will also see applications, to which all data can of course be better processed by yourself.

## Presentation

In addition to the prose, a presentation was also given. This can be found [here](doc/ppt/APC_TOPIC_2_ALLOCATORS.pptx). For more clarification: it is given in the folder `doc/ppt`. This presentation provides an introduction to this topic and identifies applications. In addition, the most relevant points of the subject are discussed.

## How the program works

Various allocators have been written for this program. For example, you have several allocators that use `malloc` and `::operator new`. There is also an allocator that uses `mmap`. By implementing these allocators, a comparison can eventually be made, together with the written memory pool allocator. A benchmark is used to determine which allocator can allocate the fastest memory.
Finally, over various amounts of memory allocation, the average execution time is taken at which a certain amount of memory is allocated.
This information is processed to be able to plot this information. MATLAB is used for this. In the end, this generated MATLAB script will look like this:

```Matlab
%% ADVANCED_PROGRAMMING_CONCEPTS_ALLOCATOR

memory_sizes = [10,100,1000];
pool_time = [14.2,34.8,147.6];
malloc_time = [2915.2,109303,445926];
mmap_time = [85.8,962,11440];
new_time = [3.8,30.6,694.8];

plot(memory_sizes, pool_time)
hold on
plot(memory_sizes, malloc_time)
plot(memory_sizes, mmap_time)
plot(memory_sizes, new_time)

title("Execution time allocating memory")
xlabel("Number of runs")
ylabel("Execution time allocating (microseconds)")
legend("MEMORY POOL", "MALLOC", "MMAP", "NEW")
```

In addition to this test/benchmark, various tests are also performed, in our case mainly on the pool allocator. This checks whether memory is allocated correctly. To do this, custom assertions were used. These assertions are given below:

```c++
#define ASSERT_TRUE(expression, message) { if (!(expression)) std::cerr << message; } // Custom-made assert, that checks if the given expression is true.
#define ASSERT_EQ(expected, actual, message) ASSERT_TRUE((expected) == (actual), message) // Custom-made assert, that checks if the expected value is equal to the actual value.
```

This allows us to ensure whether the values given from the relevant allocator actually correspond to what is expected. If an error occurs, it will be reported. This also shows that an assertions is not correct, and the implementation of the allocator is also incorrect. Our allocators have been extensively tested with these assertions, with no errors. Various data types have also been taken into account, such as `int`, `double` and a compound type, `task_compound`.

## Additional information

This repository has been developed for a specific subject for [Saxion University of Applied Sciences](https://www.saxion.edu), department [Applied Computer Science](https://www.saxion.edu/programmes/bachelor/applied-computer-science). This course is 'Advanced Programming Concepts', which required further investigation of a particular topic. Obviously, this topic is allocators.
This course requires a short presentation covering the main topics of this subject. In addition, a [prose](PROSE.md) had to be generated as well. This file provides a full explanation of how to allocate memory, along with, for example, various advantages and disadvantages of allocators in C++ and C. In addition, a number of experiences/learning processes will also be given. This has obviously taken place while generating all the necessary information to learn more about the advanced concept called 'allocators'.