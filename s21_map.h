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
        Node* parent_;

        inline Node(const value_type& data) noexcept
            : data_(data), left_(nullptr), right_(nullptr), parent_(nullptr) {}
    };
    Node<key_type, mapped_type>* root;
    size_type size_;

   public:
    map();
    map(std::initializer_list<value_type> const& items);

    void clear();
    inline bool empty() const { return !size_; }
    inline size_type size() const { return size_; }
    size_type max_size() const { return std::numeric_limits<size_type>::max(); }

   private:
    template <typename key_type, typename mapped_type>
    class MapIterator {
       private:
        Node<key_type, mapped_type>* current_;

       public:
        MapIterator(Node<key_type, mapped_type>* node) : current_(node) {}
        reference operator*() const noexcept { return current_->data_; }

        MapIterator operator++() {
            if (current_->right_) {
                current_ = current_->right_;
                while (current_->left_) {
                    current_ = current_->left_;
                }
            } else {
                if (current_->parent_) current_ = current_->parent_;
            }
            return *this;
        }

        MapIterator operator++(int) {
            MapIterator cur(*this);
            ++(*this);
            return cur;
        }

        bool operator==(const MapIterator& other) const noexcept {
            return current_ == other.current_;
        }
        bool operator!=(const MapIterator& other) const noexcept {
            return current_ != other.current_;
        }
    };

   public:
    using iterator = MapIterator<key_type, mapped_type>;
    iterator begin();
    iterator end();

    std::pair<iterator, bool> insert(const value_type& value);
};

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() {
    Node<key_type, mapped_type>* cur = root;
    while (cur->right_) cur = cur->right_;
    return iterator(cur);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() {
    Node<key_type, mapped_type>* cur = root;
    while (cur->left_) cur = cur->left_;
    return iterator(cur);
}

template <typename key_type, typename mapped_type>
inline map<key_type, mapped_type>::map() : root(nullptr), size_(0) {}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(std::initializer_list<value_type> const& items)
    : root(nullptr), size_(0) {
    for (const_reference item : items) {
    }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const value_type& value) {
    Node<key_type, mapped_type>* newNode =
        new Node<key_type, mapped_type>(value);
    if (!root) {
        root = newNode;
        size_++;
        return std::make_pair(iterator(root), true);
    }

    Node<key_type, mapped_type>* cur = root;
    Node<key_type, mapped_type>* parent = nullptr;
    bool duplicate = false;

    while (cur) {
        parent = cur;
        if (value.first < cur->data_.first) {
            cur = cur->left_;
        } else if (value.first > cur->data_.first) {
            cur = cur->right_;
        } else {
            duplicate = true;
            break;
        }
    }

    if (!duplicate) {
        if (value.first < parent->data_.first) {
            parent->left_ = newNode;
            parent->left_->parent_ = parent;
        } else {
            parent->right_ = newNode;
            parent->right_->parent_ = parent;
        }
        size_++;
    }

    return std::make_pair(iterator(newNode), !duplicate);
}

}  // namespace s21

#endif  // S21_MAP_H
