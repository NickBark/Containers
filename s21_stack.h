#ifndef S21_STACK_H
#define S21_STACK_H

#include <cstddef>   // size_t
#include <iostream>  // cout
#include <limits>    // initializer_listq

namespace s21 {
template <typename T>
class stack {
   public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    stack() : head_(nullptr), size_(0) {}
    stack(std::initializer_list<value_type> const& items);
    stack(const stack& s);
    stack(stack&& s);
    ~stack();
    stack& operator=(stack&& s);
    stack& operator=(const stack& s);

    const_reference top() const { return head_->data_; }
    bool empty() const { return !size_; }
    size_type size() const { return size_; }

    void push(const_reference value);
    void pop();
    void swap(stack& other);

    template <typename... Args>
    void insert_many_front(Args&&... args);

   private:
    class Node {
       public:
        Node(const_reference value) : data_(value), pNext_(nullptr) {}
        value_type data_;
        Node* pNext_;
    };
    Node* head_;
    size_type size_;
};

template <typename value_type>
template <typename... Args>
void stack<value_type>::insert_many_front(Args&&... args) {
    (push(std::forward(args)), ...);
}

template <typename value_type>
stack<value_type>::stack(std::initializer_list<value_type> const& items)
    : head_(nullptr), size_(0) {
    for (const_reference item : items) {
        push(item);
    }
}

template <typename value_type>
stack<value_type>::stack(const stack& s) : head_(nullptr), size_(0) {
    Node* tmp = s.head_;
    stack<value_type> reverse;
    while (tmp) {
        reverse.push(tmp->data_);
        tmp = tmp->pNext_;
    }
    while (!reverse.empty()) {
        push(reverse.top());
        reverse.pop();
    }
}

template <typename value_type>
stack<value_type>::stack(stack&& s) : head_(s.head_), size_(s.size_) {
    s.head_ = nullptr;
    s.size_ = 0;
}

template <typename value_type>
stack<value_type>::~stack() {
    while (!empty()) {
        pop();
    }
}

template <typename value_type>
stack<value_type>& stack<value_type>::operator=(stack&& s) {
    if (this != &s) swap(std::move(s));
    return *this;
}

template <typename value_type>
stack<value_type>& stack<value_type>::operator=(const stack& s) {
    if (this != &s) swap(s);
    return *this;
}

template <typename value_type>
void stack<value_type>::push(const_reference value) {
    Node* newNode = new Node(value);
    if (!head_) {
        head_ = newNode;
    } else {
        Node* tmp = head_;
        head_ = newNode;
        head_->pNext_ = tmp;
    }
    size_++;
}

template <typename value_type>
void stack<value_type>::pop() {
    if (!head_) return;
    Node* tmp = head_;
    head_ = head_->pNext_;
    delete tmp;
    size_--;
}

template <typename value_type>
void stack<value_type>::swap(stack& other) {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
}

}  // namespace s21

#endif  // S21_STACK_H
