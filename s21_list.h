#ifndef S21_LIST_H
#define S21_LIST_H

#include <algorithm>  // sort
#include <cstddef>    // size_t
#include <iostream>   // cout
#include <limits>     // initializer_list

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
    void push_front(const_reference value);
    void pop_back();
    void pop_front();
    void swap(list& other);
    void reverse();
    void clear();

    // void sort() { std::sort(begin(), end()); }

    void print_list();
    bool empty() const;
    size_type size() { return sizeOfList; }
    size_type max_size() const;

    const_reference front() const { return head->data; }
    const_reference back() const { return tail->data; }

    list<value_type>& operator=(list&& l);
    list<value_type>& operator=(const list& l);

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

        friend class list;

       public:
        ListIterator(Node<value_type>* it) : cur(it) {}
        reference operator*() const { return cur->data; }
        ListIterator& operator++() {
            // if (!cur->pNext) throw std::out_of_range("End of list");
            cur = cur->pNext;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator<value_type> it = *this;
            // if (!cur->pNext) {
            //     cur = cur->pNext;
            //     return it;
            //     throw std::out_of_range("End of list");
            // }
            cur = cur->pNext;
            return it;
        }

        ListIterator& operator--() {
            cur = cur->pPrev;
            return *this;
        }

        ListIterator operator--(int) {
            ListIterator<value_type> it = *this;
            cur = cur->pPrev;
            return it;
        }

        ListIterator& operator-=(size_type n) {
            for (size_type i = 0; i < n; ++i) {
                if (!cur->pPrev) {
                    throw std::out_of_range("End of list");
                }
                cur = cur->pPrev;
            }
            return *this;
        }

        ListIterator operator-(size_type n) const {
            ListIterator<value_type> it = *this;
            for (size_type i = 0; i < n; ++i) {
                if (!it.cur->pPrev) {
                    throw std::out_of_range("End of list");
                }
                it.cur = it.cur->pPrev;
            }
            return it;
        }

        ListIterator& operator+=(size_type n) {
            for (size_type i = 0; i < n; ++i) {
                if (!cur->pNext) {
                    throw std::out_of_range("End of list");
                }
                cur = cur->pNext;
            }
            return *this;
        }

        ListIterator operator+(size_type n) const {
            ListIterator<value_type> it = *this;
            for (size_type i = 0; i < n; ++i) {
                if (!it.cur->pNext) {
                    throw std::out_of_range("End of list");
                }
                it.cur = it.cur->pNext;
            }
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

    iterator insert(iterator pos, const_reference value);

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
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
    Node<value_type>* newNode = new Node<value_type>(value);
    if (pos.cur == head) {
        newNode->pNext = head;
        head->pPrev = newNode;
        head = newNode;
    } else {
        newNode->pNext = pos.cur;
        newNode->pPrev = pos.cur->pPrev;
        pos.cur->pPrev->pNext = newNode;
        pos.cur->pPrev = newNode;
    }

    return iterator(newNode);
}

template <typename value_type>
void list<value_type>::reverse() {
    iterator itB = begin();
    iterator itE = begin();
    itE += sizeOfList - 1;
    for (size_type i = 0; i < sizeOfList / 2; i++) {
        std::swap(*itB++, *itE--);
    }
}

template <typename value_type>
void list<value_type>::clear() {
    Node<value_type>* cur = head;
    for (size_type i = 0; i < sizeOfList; i++) {
        cur = head->pNext;
        delete head;
        head = cur;
    }
    sizeOfList = 0;
    head = nullptr;
    tail = nullptr;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() const {
    return std::numeric_limits<size_type>::max();
}

template <typename value_type>
void list<value_type>::swap(list<value_type>& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(sizeOfList, other.sizeOfList);
}

template <typename value_type>
bool list<value_type>::empty() const {
    return !sizeOfList;
}

template <typename value_type>
list<value_type>::list() : sizeOfList(0), head(nullptr), tail(nullptr) {}

template <typename value_type>
list<value_type>::~list() {
    clear();
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(const list& l) {
    if (this != &l) {
        list<value_type> tmp = list(l);
        swap(tmp);
    }
    return *this;
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(list&& l) {
    if (this != &l) {
        list<value_type> tmp = list(std::move(l));
        swap(tmp);
    }
    return *this;
}

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
void list<value_type>::push_front(const_reference value) {
    if (!head) {
        head = new Node<value_type>(value);
        tail = head;
    } else {
        Node<value_type>* newNode = new Node<value_type>(value);
        newNode->pNext = head;
        head->pPrev = newNode;
        head = newNode;
    }
    sizeOfList++;
}

template <typename value_type>
void list<value_type>::pop_back() {
    if (!head) throw std::out_of_range("Container is empty");
    if (tail->pPrev) {
        Node<value_type>* tmp = tail;
        tail = tail->pPrev;
        tail->pNext = nullptr;
        sizeOfList--;
        delete tmp;
    } else {
        delete tail;
        head = nullptr;
        tail = nullptr;
        sizeOfList--;
    }
}

template <typename value_type>
void list<value_type>::pop_front() {
    if (!head)
        throw std::out_of_range("Container is empty");
    else if (head->pNext) {
        Node<value_type>* tmp = head;
        head = head->pNext;
        head->pPrev = nullptr;
        sizeOfList--;
        delete tmp;
    } else {
        delete head;
        head = nullptr;
        tail = nullptr;
        sizeOfList--;
    }
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
