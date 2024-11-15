#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory_resource>
#include <iterator>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };

    std::pmr::polymorphic_allocator<Node> allocator_;
    Node* head_;
    size_t size_;

public:
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

    private:
        Node* current_;

    public:
        explicit iterator(Node* node) : current_(node) {}

        reference operator*() { return current_->data; }
        pointer operator->() { return &current_->data; }

        iterator& operator++() {
            current_ = current_->next;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            current_ = current_->next;
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    explicit LinkedList(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
        : allocator_(resource), head_(nullptr), size_(0) {}

    ~LinkedList();

    void push_front(const T& value);
    void pop_front();
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(nullptr); }
};

#include "../linkinList.tpp"

#endif // LINKED_LIST_H