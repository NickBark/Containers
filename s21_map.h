#ifndef S21_MAP_H
#define S21_MAP_H

#include <cstddef>   // size_t
#include <iostream>  // cout
#include <limits>    // initializer_listq

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
    map(std::initializer_list<value_type> const& items);

    void clear();
    inline bool empty() const { return !size_; }
    inline size_type size() const { return size_; }
    size_type max_size() const { return std::numeric_limits<size_type>::max(); }

    template <typename key_type, typename mapped_type>
    class MapIterator {
       private:
        Node<key_type, mapped_type>* current_;

       public:
        MapIterator(Node<key_type, mapped_type>* node) : current_(node) {}
        reference operator*() const noexcept { return current_->data_; }
        MapIterator operator++(int) {}
        MapIterator operator++() {}

        bool operator==(const MapIterator& other) const noexcept {
            return current_ == other.current_;
        }
        bool operator!=(const MapIterator& other) const noexcept {
            return current_ != other.current_;
        }
    };
};

template <typename key_type, typename mapped_type>
inline map<key_type, mapped_type>::map() : root(nullptr), size_(0) {}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(
    std::initializer_list<value_type> const& items) {}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {}

}  // namespace s21

#endif  // S21_MAP_H
