#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <cstddef>   // size_t
#include <iostream>  // cout
#include <limits>    // initializer_listq

namespace s21 {
template <typename T>
class queue {
   public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

   private:
    class Node {
       public:
        value_type data_;
        Node* pNext_;
        Node(const_reference data) : data_(data), pNext_(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    size_type size_;

   public:
    queue() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~queue();

    const_reference front() const { return head_->data_; }
    const_reference back() const { return tail_->data_; }
    bool empty() const { return !size_; }
    size_type size() const { return size_; }
    void push(const_reference value);
    void pop();
};

template <typename value_type>
queue<value_type>::~queue() {
    while (!empty()) {
        pop();
    }
}

template <typename value_type>
void queue<value_type>::pop() {
    if (!head_) return;
    Node* tmp = head_;
    head_ = head_->pNext_;
    delete tmp;
    size_--;
}

template <typename value_type>
void queue<value_type>::push(const_reference value) {
    Node* newNode = new Node(value);
    if (!head_) {
        head_ = newNode;
        tail_ = newNode;
        size_++;
    } else {
        tail_->pNext_ = newNode;
        tail_ = newNode;
        size_++;
    }
}

}  // namespace s21

#endif  // S21_QUEUE_H