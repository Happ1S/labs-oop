#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "include/linkinList.h"

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head_) {
        Node* temp = head_;
        head_ = head_->next;
        allocator_.deallocate(temp, 1);
    }
}

template<typename T>
void LinkedList<T>::push_front(const T& value) {
    Node* new_node = allocator_.allocate(1);
    allocator_.construct(new_node, value);
    new_node->next = head_;
    head_ = new_node;
    ++size_;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (head_) {
        Node* temp = head_;
        head_ = head_->next;
        allocator_.deallocate(temp, 1);
        --size_;
    }
}

#endif