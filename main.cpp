#include <iostream>
#include "menu.hpp"
#include "allocator2.hpp"
#include <stack>
#include <list>
#include <vector>
#include <algorithm>

#include "stack.hpp"

int main() {
    std::cout << "//////////////////////////////////////////////////////\n";
    std::vector<int> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(1);
    std::cout << vec[0] << "\n";

    std::cout << "//////////////////////////////////////////////////////\n";

    Stack<int> stc;
    stc.Push(1);
    stc.Push(2);
    stc.Push(3);
    stc.Push(4);
    stc.Push(5);
    stc.Push(6);
    stc.Push(7);
    stc.Pop();
    stc.Pop();
    stc.Top();

    auto print_elem = [](const Node<int> &elem) {
        std::cout << elem << "\n";
    };

    std::for_each(stc.begin(), stc.end(), print_elem);
    std::cout << "Top element = " << stc.Top() << "\n";
}