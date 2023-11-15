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

    void copyNode(const Node<key_type, mapped_type>* src);
    void deleteNode(Node<key_type, mapped_type>* node);
    Node<key_type, mapped_type>* eraseNode(Node<key_type, mapped_type>* node,
                                           const key_type& key);
    Node<key_type, mapped_type>* findMin(Node<key_type, mapped_type>* node);

   public:
    map();
    map(std::initializer_list<value_type> const& items);
    map(const map& m);
    map(map&& m);
    ~map();
    map& operator=(const map& m);
    map& operator=(map&& m);

    void clear();
    inline bool empty() const { return !size_; }
    inline size_type size() const { return size_; }
    size_type max_size() const { return std::numeric_limits<size_type>::max(); }
    mapped_type& at(const key_type& key);

    void swap(map& other);

   private:
    template <typename key_type, typename mapped_type>
    class MapIterator {
       private:
        Node<key_type, mapped_type>* current_;

       public:
        MapIterator(Node<key_type, mapped_type>* node) : current_(node) {}
        reference operator*() const noexcept { return current_->data_; }
        value_type* operator->() const noexcept { return &(current_->data_); }

        MapIterator operator++() {
            if (current_->right_) {
                current_ = findMin(current_->right_);
            } else {
                if (current_->parent_ &&
                    current_->parent_->data_ > current_->data_)
                    current_ = current_->parent_;
                else {
                    current_ = nullptr;
                }
            }

            return *this;
        }

        MapIterator operator--() {
            if (current_->left_) {
                current_ = current_->left_;
                while (current_->right_) {
                    current_ = current_->right_;
                }
            } else {
                if (current_->parent_ &&
                    current_->parent_->data_ < current_->data_)
                    current_ = current_->parent_;
                else {
                    current_ = nullptr;
                }
            }

            return *this;
        }

        MapIterator operator++(int) {
            MapIterator cur(*this);
            ++(*this);
            return cur;
        }

        MapIterator operator--(int) {
            MapIterator cur(*this);
            --(*this);
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
    std::pair<iterator, bool> insert(const key_type& key,
                                     const mapped_type& obj);
    std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                               const mapped_type& obj);

    mapped_type& operator[](const key_type& key) { return at(key); }
    void erase(iterator pos);
};

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node<key_type, mapped_type>*
map<key_type, mapped_type>::findMin(Node<key_type, mapped_type>* node) {
    while (node->left_) {
        node = node->left_;
    }
    return node;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node<key_type, mapped_type>*
map<key_type, mapped_type>::eraseNode(Node<key_type, mapped_type>* node,
                                      const key_type& key) {
    if (node == nullptr) return nullptr;

    if (key < node->data_.first) {
        node->left_ = eraseNode(node->left_, key);
    } else if (key > node->data_.first) {
        node->right_ = eraseNode(node->right_, key);
    } else {
        if (!node->left_ && !node->right_) {
            delete node;
            return nullptr;
        } else if (node->left_ && !node->right_) {
            Node<key_type, mapped_type>* tmp = node->left_;
            delete node;
            return tmp;
        } else if (!node->left_ && node->right_) {
            Node<key_type, mapped_type>* tmp = node->right_;
            delete node;
            return tmp;
        } else {
            Node<key_type, mapped_type>* tmp = findMin(node->right_);
            std::swap(node->data_, tmp->data_);
            delete tmp;
        }
    }
    return node;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
    root = eraseNode(root, pos.operator->()->first);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map& other) {
    std::swap(root, other.root);
    std::swap(size_, other.size_);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::map& map<key_type, mapped_type>::operator=(
    const map& m) {
    if (this != &m) {
        map<key_type, mapped_type> tmp(m);
        swap(tmp);
    }
    return *this;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::map& map<key_type, mapped_type>::operator=(
    map&& m) {
    if (this != &m) {
        map<key_type, mapped_type> tmp(std::move(m));
        swap(tmp);
    }
    return *this;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::deleteNode(Node<key_type, mapped_type>* node) {
    if (node) {
        deleteNode(node->left_);
        deleteNode(node->right_);
        delete node;
    }
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {
    deleteNode(root);
    size_ = 0;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::copyNode(
    const Node<key_type, mapped_type>* src) {
    if (src) {
        insert(src->data_.first, src->data_.second);
        size_++;
        copyNode(src->left_);
        copyNode(src->right_);
    }
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::at(const key_type& key) {
    Node<key_type, mapped_type>* current = root;
    while (current && current->data_.first != key) {
        if (key < current->data_.first)
            current = current->left_;
        else if (key > current->data_.first)
            current = current->right_;
    }
    return current ? current->data_.second : throw std::out_of_range("map::at");
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() {
    return iterator(nullptr);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() {
    if (!root) return iterator(nullptr);
    Node<key_type, mapped_type>* cur = root;
    while (cur->left_) cur = cur->left_;
    return iterator(cur);
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map& m) : root(nullptr) {
    copyNode(m.root);
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::~map() {
    clear();
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map&& m) : root(m.root), size_(m.size_) {
    m.root = nullptr;
    m.size_ = 0;
}

template <typename key_type, typename mapped_type>
inline map<key_type, mapped_type>::map() : root(nullptr), size_(0) {}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(std::initializer_list<value_type> const& items)
    : root(nullptr), size_(0) {
    for (const_reference item : items) {
        insert(item.first, item.second);
    }
}

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
            delete newNode;
            duplicate = true;
            break;
        }
    }

    if (!duplicate) {
        newNode->parent_ = parent;
        if (value.first < parent->data_.first) {
            parent->left_ = newNode;
        } else {
            parent->right_ = newNode;
        }
        size_++;
    }

    return std::make_pair(iterator(newNode), !duplicate);
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type& key,
                                   const mapped_type& obj) {
    return insert(std::make_pair(key, obj));
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    std::pair<iterator, bool> result = insert(key, obj);
    if (!result.second) {
        at(key) = obj;
    }
    return result;
}

}  // namespace s21

#endif  // S21_MAP_H
