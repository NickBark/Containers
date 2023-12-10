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

    queue() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~queue();
    queue(std::initializer_list<value_type> const& items);
    queue(queue&& q);
    queue(const queue& q);

    queue<value_type>& operator=(queue&& q);
    queue<value_type>& operator=(const queue& q);

    const_reference front() const { return head_->data_; }
    const_reference back() const { return tail_->data_; }
    bool empty() const { return !size_; }
    size_type size() const { return size_; }

    void push(const_reference value);
    void pop();
    void swap(queue& other);

    template <typename... Args>
    void insert_many_back(Args&&... args);

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
};

template <typename value_type>
template <typename... Args>
void queue<value_type>::insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
}

template <typename value_type>
queue<value_type>& queue<value_type>::operator=(queue&& q) {
    if (this != &q) {
        queue<value_type> tmp(std::move(q));
        swap(tmp);
    }
    return *this;
}

template <typename value_type>
queue<value_type>& queue<value_type>::operator=(const queue& q) {
    if (this != &q) {
        queue<value_type> tmp(q);
        swap(tmp);
    }
    return *this;
}

template <typename value_type>
queue<value_type>::queue(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr), size_(0) {
    for (const_reference item : items) {
        push(item);
    }
}

template <typename value_type>
queue<value_type>::queue(const queue& q)
    : head_(nullptr), tail_(nullptr), size_(0) {
    Node* tmp = q.head_;
    while (tmp) {
        push(tmp->data_);
        tmp = tmp->pNext_;
    }
}

template <typename value_type>
queue<value_type>::queue(queue&& q)
    : head_(q.head_), tail_(q.tail_), size_(q.size_) {
    q.head_ = nullptr;
    q.tail_ = nullptr;
    q.size_ = 0;
}

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
    } else {
        tail_->pNext_ = newNode;
        tail_ = newNode;
    }
    size_++;
}

template <typename value_type>
void queue<value_type>::swap(queue& other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

}  // namespace s21

#endif  // S21_QUEUE_H
