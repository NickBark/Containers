#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>   // size_t
#include <iostream>  // cout
#include <limits>

namespace s21 {
template <typename T>
class list {
   public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    list();
    ~list();
    list(size_type n);
    list(std::initializer_list<value_type> const& items);
    list(const list& l);
    list(list&& l);

    void push_back(const_reference value);
    // void push_front(const_reference value);

    void print_list();
    size_type size() { return sizeOfList; }
    size_type max_size() const { return std::numeric_limits<size_type>::max(); }

    const_reference front() const { return head->data; }
    const_reference back() const { return tail->data; }

    reference operator[](const int& index);

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

    template <typename value_type>
    class ListIterator {
       protected:
        Node<value_type>* cur;

        ListIterator& operator=(ListIterator& other) {
            cur = other.cur;
            return *this;
        }

       public:
        ListIterator(Node<value_type>* it) : cur(it) {}
        reference operator*() const { return cur->data; }
        ListIterator& operator++() {
            if (!cur->pNext) throw std::out_of_range("End of list");
            cur = cur->pNext;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator<value_type> it = *this;
            if (!cur->pNext) throw std::out_of_range("End of list");
            cur = cur->pNext;
            return it;
        }

        ListIterator& operator--() {
            cur = cur->pPrev;
            return *this;
        }

        // ListIterator operator--(int);
        ListIterator operator--(int) {
            ListIterator<value_type> it = *this;
            cur = cur->pPrev;
            return it;
        }

        bool operator==(const ListIterator& other) { return cur == other.cur; }
        bool operator!=(const ListIterator& other) { return cur != other.cur; }
    };

    template <typename value_type>
    class ListConstIterator : public ListIterator<value_type> {
       public:
        ListConstIterator(const Node<value_type>* it)
            : ListIterator<value_type>(const_cast<Node<T>*>(it)) {}

        const_reference operator*() const { return this->cur->data; }
    };

   public:
    using iterator = ListIterator<T>;
    using const_iterator = ListConstIterator<T>;

    iterator begin() {
        if (!head) throw std::out_of_range("The list has no elements");
        return ListIterator(head);
    }

    const_iterator begin() const {
        if (!head) throw std::out_of_range("The list has no elements");
        return ListConstIterator(head);
    }

    iterator end() {
        if (!tail) throw std::out_of_range("The list has no elements");
        return ListIterator(tail->pNext);
    }

    const_iterator end() const {
        if (!tail) throw std::out_of_range("The list has no elements");
        return ListIterator(tail->pNext);
    }
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
void list<value_type>::print_list() {
    std::cout << "start print list" << std::endl;
    Node<value_type>* current = head;
    while (current) {
        std::cout << current->data << std::endl;
        current = current->pNext;
    }
}

template <typename value_type>
list<value_type>::list(size_type n)
    : sizeOfList(0), head(nullptr), tail(nullptr) {
    for (size_type i = 0; i < n; i++) {
        push_back(value_type());
    }
}

template <typename value_type>
typename list<value_type>::reference list<value_type>::operator[](
    const int& index) {
    if (index < 0 || index >= sizeOfList)
        throw std::out_of_range("Out of list");
    Node<value_type>* cur = head;
    for (size_type i = 0; i < index; i++) {
        cur = cur->pNext;
    }
    return cur->data;
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const& items)
    : sizeOfList(0), head(nullptr), tail(nullptr) {
    for (const_reference item : items) {
        push_back(item);
    }
}

template <typename value_type>
list<value_type>::list(const list& l)
    : sizeOfList(0), head(nullptr), tail(nullptr) {
    const_iterator it = l.begin();
    for (size_type i = 0; i < l.sizeOfList - 1; i++) {
        push_back(*it++);
    }
    push_back(*it);
}

template <typename value_type>
list<value_type>::list(list&& l)
    : sizeOfList(l.sizeOfList), head(l.head), tail(l.tail) {
    l.sizeOfList = 0;
    l.head = nullptr;
    l.tail = nullptr;
}

}  // namespace s21

#endif  // S21_LIST_H
