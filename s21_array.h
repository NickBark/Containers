#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <cstddef>

namespace s21 {
template <typename T, size_t N>
class array {
   public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

   private:
    value_type arr[N];
};
}  // namespace s21

#endif  // S21_ARRAY_H