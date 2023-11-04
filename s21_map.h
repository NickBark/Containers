#ifndef S21_MAP_H
#define S21_MAP_H

#include <cstddef>   // size_t
#include <iostream>  // cout

namespace s21 {
template <typename Key, typename T>
class map {
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;

    template <typename key_type, typename mapped_type>
    class Node {
       public:
    };
};
}  // namespace s21

#endif  // S21_MAP_H