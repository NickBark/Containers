#ifndef S21_MAP_H
#define S21_MAP_H

#include <cstddef>   // size_t
#include <iostream>  // cout

namespace s21 {
template <typename Key, typename T>
class map {
   public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

   private:
    template <typename key_type, typename mapped_type>
    class Node {
       public:
        value_type data_;
        Node* left_;
        Node* right_;
        Node* parrent_;

        inline Node(const value_type& data) noexcept
            : data_(data), left_(nullptr), right_(nullptr), parrent_(nullptr) {}
    };
    Node<key_type, mapped_type>* root;
    size_type size_;

    map();

    void clear();
};

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map() : root(nullptr), size_(0) {}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {}

}  // namespace s21

#endif  // S21_MAP_H
