#ifndef ALLOCATOR_STACK_LINKED_LIST_H
#define ALLOCATOR_STACK_LINKED_LIST_H

template <typename T>
struct node_list {
    T m_data;
    node_list* m_next_node;
};

template <typename T>
class stack_linked_list {
public:
    void push_node(node_list<T>* next_node) noexcept;
    node_list<T>* pop_node() noexcept;

private:
    node_list<T>* m_head;
};

template<typename T>
void stack_linked_list<T>::push_node(node_list<T> *next_node) noexcept {
    next_node->m_next_node = m_head;
    m_head = next_node;
}

template<typename T>
node_list<T> *stack_linked_list<T>::pop_node() noexcept {
    auto* top_node = m_head;
    m_head = m_head->m_next_node;
    return top_node;
}

#endif