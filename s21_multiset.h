#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class multiset {
   public:
    using key_type = T;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

    multiset() : root(nullptr), size_(0) {}
    ~multiset() { clear(); }
    multiset(const multiset& ms);
    multiset(multiset&& ms);
    multiset& operator=(multiset&& ms);
    multiset& operator=(const multiset& ms);
    multiset(std::initializer_list<value_type> const& items);

    bool empty() const { return !size_; }
    size_type size() const { return size_; }
    size_type max_size() const { return std::numeric_limits<size_type>::max(); }

   private:
    template <typename value_type>
    class Node {
       public:
        value_type value;
        Node* left;
        Node* right;
        Node* parent;
        size_type count;

        Node(value_type key)
            : value(key),
              count(1),
              left(nullptr),
              right(nullptr),
              parent(nullptr) {}
    };

    Node<value_type>* root;
    size_type size_;

    template <typename value_type>
    class MultisetIterator {
       public:
        MultisetIterator(Node<value_type>* node = nullptr)
            : cur(node), counter(0) {}

        value_type operator*() { return cur ? cur->value : value_type(); }
        MultisetIterator& operator++() {
            if (!cur) return *this;

            counter++;

            if (counter >= cur->count) {
                counter = 0;
                if (cur->right) {
                    cur = cur->right;
                    while (cur->left) {
                        cur = cur->left;
                    }
                } else {
                    if (cur->parent) {
                        value_type tmp = cur->value;
                        while (cur->parent && cur->parent->value < tmp)
                            cur = cur->parent;
                        cur = cur->parent;
                    } else {
                        cur = nullptr;
                    }
                }
            }

            return *this;
        }
        MultisetIterator& operator--() {
            if (!cur) return *this;

            counter = !counter ? cur->count : counter;
            counter--;

            if (counter <= 0) {
                if (cur->left) {
                    cur = cur->left;
                    while (cur->right) {
                        cur = cur->right;
                    }
                } else {
                    if (cur->parent) {
                        value_type tmp = cur->value;
                        while (cur->parent && cur->parent->value > tmp)
                            cur = cur->parent;
                        cur = cur->parent;
                    } else {
                        cur = nullptr;
                    }
                }
                if (cur) counter = cur->count - 1;
            }

            return *this;
        }

        MultisetIterator operator++(int) {
            MultisetIterator tmp(*this);
            ++*this;
            return tmp;
        }

        MultisetIterator operator--(int) {
            MultisetIterator tmp(*this);
            --*this;
            return tmp;
        }

        bool operator==(const MultisetIterator& other) const noexcept {
            return cur == other.cur;
        }
        bool operator!=(const MultisetIterator& other) const noexcept {
            return cur != other.cur;
        }

       private:
        Node<value_type>* cur;
        size_type counter;
    };

    // class MultisetConstIterator : public MultisetIterator {};

   public:
    using iterator = MultisetIterator<value_type>;
    // using const_iterator = MultisetConstIterator<value_type>;

    iterator begin();
    iterator end() const;

    iterator insert(const value_type& value);
    iterator find(const_reference key);
    size_type count(const_reference key);
    bool contains(const_reference key);
    void erase(iterator pos);
    void clear();
    void swap(multiset& other);

    iterator lower_bound(const_reference key);
    iterator upper_bound(const_reference key);  //
   private:
    Node<value_type>* insertNode(Node<value_type>* node, const_reference val,
                                 Node<value_type>* parent);
    Node<value_type>* findNode(Node<value_type>* node, const_reference val);
    Node<value_type>* findCloseNode(Node<value_type>* node,
                                    const_reference val);
    Node<value_type>* eraseNode(Node<value_type>* node, const_reference val);
    Node<value_type>* findMinNode(Node<value_type>* node);
    Node<value_type>* findCloseMinNode(Node<value_type>* node,
                                       const_reference key);
    void deleteNode(Node<value_type>* node);
    void copyNode(const Node<value_type>* node);
    iterator last() const;
};

template <typename value_type>
typename multiset<value_type>::iterator multiset<value_type>::last() const {
    Node<value_type>* cur = root;
    while (cur->right) cur = cur->right;
    return iterator(cur);
}

template <typename value_type>
typename multiset<value_type>::Node<value_type>*
multiset<value_type>::findCloseMinNode(Node<value_type>* node,
                                       const_reference key) {
    if (!node->left || node->left->value < key) return node;
    return findCloseMinNode(node->left, key);
}

template <typename value_type>
typename multiset<value_type>::Node<value_type>*
multiset<value_type>::findCloseNode(Node<value_type>* node,
                                    const_reference val) {
    if (!node) return node;
    if (node->value == val) return node;
    if (node->value < val) {
        node = findCloseNode(node->right, val);
    } else {
        node = findCloseMinNode(node, val);
    }

    return node;
}

template <typename value_type>
typename multiset<value_type>::iterator multiset<value_type>::lower_bound(
    const_reference key) {
    return iterator(findCloseNode(root, key));
    // iterator cur(findCloseNode(root, key));
    // return *cur == key ? cur : ++cur;
}

template <typename value_type>
typename multiset<value_type>::iterator multiset<value_type>::upper_bound(
    const_reference key) {
    iterator cur(findCloseNode(root, key));
    cur = *cur == key ? ++cur : cur;
    return cur != end() ? cur : iterator(nullptr);
}

template <typename value_type>
void multiset<value_type>::swap(multiset& other) {
    std::swap(root, other.root);
    std::swap(size_, other.size_);
}

template <typename value_type>
void multiset<value_type>::copyNode(const Node<value_type>* node) {
    if (node) {
        insert(node->value);
        size_++;
        copyNode(node->left);
        copyNode(node->right);
    }
}

template <typename value_type>
typename multiset<value_type>::multiset& multiset<value_type>::operator=(
    const multiset& ms) {
    if (this != &ms) {
        multiset<value_type> tmp(ms);
        swap(tmp);
    }
    return *this;
}

template <typename value_type>
typename multiset<value_type>::multiset& multiset<value_type>::operator=(
    multiset&& ms) {
    if (this != &ms) {
        multiset<value_type> tmp(std::move(ms));
        swap(tmp);
    }
    return *this;
}

template <typename value_type>
multiset<value_type>::multiset(multiset&& ms) : root(ms.root), size_(ms.size_) {
    ms.root = nullptr;
    ms.size_ = 0;
}

template <typename value_type>
multiset<value_type>::multiset(std::initializer_list<value_type> const& items)
    : root(nullptr), size_(0) {
    for (auto item : items) {
        insert(item);
    }
}

template <typename value_type>
multiset<value_type>::multiset(const multiset& ms) : root(nullptr), size_(0) {
    copyNode(ms.root);
}

template <typename value_type>
void multiset<value_type>::deleteNode(Node<value_type>* node) {
    if (node) {
        deleteNode(node->right);
        deleteNode(node->left);
        delete node;
    }
}

template <typename value_type>
void multiset<value_type>::clear() {
    deleteNode(root);
    size_ = 0;
}

template <typename value_type>
typename multiset<value_type>::Node<value_type>*
multiset<value_type>::findMinNode(Node<value_type>* node) {
    if (!node->left) return node;
    return findMinNode(node->left);
}

template <typename value_type>
typename multiset<value_type>::Node<value_type>*
multiset<value_type>::eraseNode(Node<value_type>* node, const_reference val) {
    if (node->value == val) {
        if (node->count > 1) {
            node->count--;
            return node;
        }
        if (!node->left && !node->right) {
            if (node->parent) {
                if (node->parent->right == node) node->parent->right = nullptr;
                if (node->parent->left == node) node->parent->left = nullptr;
            }
            delete node;
            return nullptr;
        } else if (!node->left) {
            Node<value_type>* tmp = node->right;
            if (node->parent) {
                if (node->parent->right == node) node->parent->right = tmp;
                if (node->parent->left == node) node->parent->left = tmp;
            }
            tmp->parent = node->parent;
            delete node;
            return tmp;
        } else if (!node->right) {
            Node<value_type>* tmp = node->left;
            if (node->parent) {
                if (node->parent->right == node) node->parent->right = tmp;
                if (node->parent->left == node) node->parent->left = tmp;
            }
            tmp->parent = node->parent;
            delete node;
            return tmp;
        }

        Node<value_type>* minNodeInRightSubtree = findMinNode(node->right);
        node->value = minNodeInRightSubtree->value;
        node->count = minNodeInRightSubtree->count;
        minNodeInRightSubtree->count = 1;  // need test
        node->right = eraseNode(node->right, minNodeInRightSubtree->value);

        // return node;
    } else if (node->value < val) {
        node->right = node->right ? eraseNode(node->right, val) : nullptr;
    } else if (node->value > val) {
        node->left = node->left ? eraseNode(node->left, val) : nullptr;
    }

    return node;
}

template <typename value_type>
void multiset<value_type>::erase(iterator pos) {
    if (contains(*pos)) {
        if (root) root = eraseNode(root, *pos);
        size_--;
    }
}

// if (!pos.cur->left && !pos.cur->right) {
//     if (pos.cur == pos.cur->parent->right) {
//         pos.cur->parent->right = nullptr;
//     } else if (pos.cur == pos.cur->parent->left) {
//         pos.cur->parent->left = nullptr;
//     }
//     delete pos.cur;
// }

template <typename value_type>
bool multiset<value_type>::contains(const_reference key) {
    Node<value_type>* tmp = findNode(root, key);
    return tmp ? true : false;
}

template <typename value_type>
typename multiset<value_type>::size_type multiset<value_type>::count(
    const_reference key) {
    Node<value_type>* tmp = findNode(root, key);
    return tmp ? tmp->count : 0;
}

template <typename value_type>
typename multiset<value_type>::Node<value_type>* multiset<value_type>::findNode(
    Node<value_type>* node, const_reference val) {
    if (!node || node->value == val) return node;

    if (node->value < val) {
        node = findNode(node->right, val);
    } else if (node->value > val) {
        node = findNode(node->left, val);
    }

    return node;
}

template <typename value_type>
typename multiset<value_type>::iterator multiset<value_type>::find(
    const_reference key) {
    Node<value_type>* tmp = findNode(root, key);
    return iterator(tmp ? tmp : nullptr);
}

template <typename value_type>
typename multiset<value_type>::Node<value_type>*
multiset<value_type>::insertNode(Node<value_type>* node, const_reference val,
                                 Node<value_type>* parent) {
    if (node) {
        if (val == node->value) node->count++;
        if (val < node->value) {
            node->left = insertNode(node->left, val, node);
        }
        if (val > node->value) {
            node->right = insertNode(node->right, val, node);
        }
    } else {
        node = new Node(val);
        node->parent = parent;
    }
    return node;
}

template <typename value_type>
typename multiset<value_type>::iterator multiset<value_type>::insert(
    const_reference value) {
    root = insertNode(root, value, nullptr);
    size_++;
    return find(value);
}

template <typename value_type>
typename multiset<value_type>::iterator multiset<value_type>::begin() {
    if (!root) return iterator(nullptr);
    Node<value_type>* tmp = root;
    while (tmp->left) tmp = tmp->left;
    return iterator(tmp);
}

template <typename value_type>
typename multiset<value_type>::iterator multiset<value_type>::end() const {
    // Node<value_type>* tmp = root;
    // while (tmp->right) tmp = tmp->right;

    return iterator(nullptr);
}

}  // namespace s21

#endif  // S21_MULTISET_H
