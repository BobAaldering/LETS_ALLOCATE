# Let's allocate!
#### By: Bob Aaldering (492152) and Nian Luisman (496439)

Everything revolves around memory, even in a computer program. In order to allocate memory in a lower-level programming language, you have to do it all yourself. In C++ you can use `::operator new` to dynamically allocate memory. To release this memory, use `::operator delete`. In C, on the other hand, you use the functions `malloc()` and `free()`. However, allocating memory with the functions mentioned above is a complex problem.

This repository explains the problems of dynamic memory allocation. In addition, research is given on how memory is allocated dynamically, what the algorithms are on this type of memory. Also given are pros and cons of using the functions that allocate memory in both C++ and C. Finally, several implementations of allocators are also given, for example a proprietary implementation of `std::allocator` and a `memory_pool_allocator` .

## Prose

To clarify allocators, a [prose](PROSE.md) has been generated. It is written in a formal format, with extensive explanations on various topics.
An explanation of the topic follows, in which the complex problem surrounding allocators is clarified. It also mentions why allocators are important in acquiring programming experience. Following is the actual content, which gives everything about allocators needed to know all about it!
To give various applications, code snippets are also given, where explanation is also given. 
In addition to theoretical aspects related to this subject, you will also see applications, to which all data can of course be better processed by yourself.

## Additional information

This repository has been developed for a specific subject for [Saxion University of Applied Sciences](https://www.saxion.edu), department [Applied Computer Science](https://www.saxion.edu/programmes/bachelor/applied-computer-science). This course is 'Advanced Programming Concepts', which required further investigation of a particular topic. Obviously, this topic is allocators.
This course requires a short presentation covering the main topics of this subject. In addition, a [prose](PROSE.md) had to be generated as well. This file provides a full explanation of how to allocate memory, along with, for example, various advantages and disadvantages of allocators in C++ and C. In addition, a number of experiences/learning processes will also be given. This has obviously taken place while generating all the necessary information to learn more about the advanced concept called 'allocators'.