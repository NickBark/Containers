#include <list>

#include "s21_containers.h"

int main() {
    s21::list<std::string> list;
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    // list.print_list();

    std::cout << list.front() << std::endl;

    // int a = 5;
    // int b = 6;
    // int *p1 = &a;
    // int *p2 = p1;
    // p1 = &b;
    // std::cout << *p1 << " " << *p2 << std::endl;

    return 0;
}