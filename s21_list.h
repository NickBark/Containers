#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>   // size_t
#include <iostream>  // cout

namespace s21 {
template <typename T>
class list {
   public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    // using iterator = ListIterator<T>;
    // using const_iterator = ListConstIterator<T>;
    using size_type = size_t;

   private:
    template <typename value_type>
    class Node {
       public:
        Node(const_reference value = value_type(), Node* next = nullptr,
             Node* prev = nullptr)
            : data(value), pNext(next), pPrev(prev) {}

        value_type data;
        Node* pNext;
        Node* pPrev;
    };

    Node<T>* head;
    Node<T>* tail;
    size_type sizeOfList;

   public:
    list();
    ~list();

    void push_back(const_reference value);
    void push_front(const_reference value);

    void print_list();
    size_type size();

    const_reference front() const;
    const_reference back() const;

    // list(size_type n) {}
    // list(std::initializer_list<value_type> const& items) {}
    // list(const list& l) {}
    // list(list&& l) {}

    // list operator=(list&& l) {}

    // iterator begin();
    // iterator end();

    // class iterator {
    // ;
    // };
};

template <typename value_type>
list<value_type>::list() : sizeOfList(0), head(nullptr), tail(nullptr) {}

template <typename value_type>
list<value_type>::~list() {}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
    if (!head) {
        head = new Node<value_type>(value);
        tail = head;
    } else {
        tail->pNext = new Node<value_type>(value);
        tail->pNext->pPrev = tail;
        tail = tail->pNext;
    }
    sizeOfList++;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
    return head->data;
}

template <typename value_type>
const value_type& list<value_type>::back() const {
    return tail->data;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() {
    return sizeOfList;
}

template <typename value_type>
void list<value_type>::print_list() {
    std::cout << "start print list" << std::endl;
    Node<value_type>* current = head;
    while (current) {
        std::cout << current->data << std::endl;
        current = current->pNext;
    }
}

}  // namespace s21

#endif  // S21_LIST_H