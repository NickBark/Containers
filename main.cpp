#include <algorithm>
#include <iostream>
#include <list>

#include "s21_containers.h"

int main() {
    s21::list<int> qqq = {1, 2, 3};
    s21::list<int> ppp = {4, 5, 6};
    ppp.merge(qqq);
    ppp.print_list();
    // ppp.print_list();
    // std::cout << *it1 << " " << *it2 << std::endl;
    // s21::list<int> qqq = {4, 5, 6};
    // auto its = ppp.begin();
    // its++;

    // ppp.splice(its, qqq);
    // ppp.unique();

    // auto it = ppp.begin();

    // it++;
    // it++;
    // it--;
    // auto it2 = ppp.begin();
    // ppp.insert(it, 21);
    // for (size_t i = 0; i < ppp.size(); i++) {
    //     std::cout << *it++ << std::endl;
    // }
    // std::cout << "------" << std::endl;
    // for (size_t i = 0; i < qqq.size(); i++) {
    //     std::cout << *itq++ << std::endl;
    // }
    // // ppp.print_list();
    // ppp.erase(it);
    // it2 = ppp.begin();
    // for (size_t i = 0; i < ppp.size(); i++) {
    //     std::cout << *it2++ << std::endl;
    // }
    // ppp.print_list();
    // std::cout << ppp.size() << std::endl;
    // try {
    //     std::reverse(ppp.begin(), ppp.end());
    //     // it += 2;
    //     // std::cout << *(it) << std::endl;
    //     // it -= 2;
    //     // std::cout << *(it) << std::endl;

    //     // ppp.sort();

    //     ppp.print_list();
    // } catch (std::exception& e) {
    //     std::cout << e.what() << std::endl;
    // }

    // const s21::list<int> lll = {1, 2, 2, 3};
    // auto it = lll.begin();
    // ppp[0] = 3;
    // ppp[1] = 3;
    // qqq.print_list();
    // ppp.print_list();
    // s21::list<int>::iterator it = ppp.begin();
    // list.push_back("a");
    // list.push_back("b");
    // list.push_back("c");
    // list.print_list();

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