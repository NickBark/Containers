#include "s21_containers.h"

int main() {
    s21::list<int> ppp = {1, 2, 3, 4};
    s21::list<int> qqq(ppp);
    // const s21::list<int> lll = {1, 2, 2, 3};
    // auto it = lll.begin();
    ppp[0] = 3;
    ppp[1] = 3;
    qqq.print_list();
    ppp.print_list();
    s21::list<int>::iterator it = ppp.begin();
    // list.push_back("a");
    // list.push_back("b");
    // list.push_back("c");
    // list.print_list();

    std::cout << std::endl << ppp.max_size() << std::endl;
    // std::cout << "num of elem " << list.size() << std::endl;

    // auto it = list.begin();
    // auto it2 = list.begin();
    // s21::list<std::string>::iterator it2 = list.begin();
    // std::cout << *(++it) << std::endl;
    // try {
    //     // it++;
    //     // it++;
    //     // it++;
    //     // it++;
    //     // it--;
    //     std::cout << *it2 << std::endl;
    // } catch (std::exception& e) {
    //     std::cout << e.what() << std::endl;
    // }
    // std::cout << *it++ << std::endl;
    // std::cout << *it << std::endl;
    // it++;
    // int a = 5;
    // int b = 6;
    // int *p1 = &a;
    // int *p2 = p1;
    // p1 = &b;
    // std::cout << *p1 << " " << *p2 << std::endl;

    return 0;
}