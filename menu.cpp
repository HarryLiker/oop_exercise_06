#include <iostream>
#include <algorithm>
#include "stack.hpp"
#include "triangle.hpp"
#include <exception>

int menu() {
    const std::size_t BLOCK_SIZE = 256;
    Stack<Triangle<int>, allocator<Triangle<int>, BLOCK_SIZE>> stack;
    while(1) {
        std::cout << "Menu:\n";
        std::cout << "1 - Add figure in collection as stack\n";
        std::cout << "2 - Add figure in collection by index\n";
        std::cout << "3 - Delete figure from the collection as from stack\n";
        std::cout << "4 - Delete figure from the collection by index\n";
        std::cout << "5 - Print figures from the collection\n";
        std::cout << "6 - End the program\n";
        int variant = 0;
        std::cout << "Enter an action: ";
        std::cin >> variant;
        switch (variant) {
        case 1:
        {
            int x,y;
            int side;
            std::cout << "Write the center coordinates: ";
            std::cin >> x >> y;
            std::cout << "Write size of the triangle: ";
            std::cin >> side;
            stack.Push(Triangle<int>(std::pair<int,int> {x, y}, side));
            std::cout << "The figure has been added\n";
            break;
        }
        case 2:
        {
            
            int x,y;
            int side;
            int index;
            std::cout << "Write the center coordinates: ";
            std::cin >> x >> y;
            std::cout << "Write size of the triangle: ";
            std::cin >> side;
            std::cout << "Write an index: ";
            std::cin >> index;
            try {
                if (stack.FindSize() + 1 < index) {
                    throw std::invalid_argument("Entered the wrong index!\n");
                }
                else {
                    auto iterator = stack.begin();
                    while(--index) {
                        ++iterator;
                    }
                    stack.Insert(iterator, Triangle<int>(std::pair<int,int> {x, y}, side));
                    std::cout << "The figure has been added\n";
                }
            }
            catch (std::invalid_argument &argument){
                std::terminate();
            }
            break;
        }
        case 3:
        {
            stack.Pop();
            std::cout << "The figure has been removed\n";
            break;
        }
        case 4:
        {
            int index;
            std::cout << "Enter the position of the element to remove: ";
            std::cin >> index;
            try {
                auto iterator = stack.begin();
                while (--index) {
                    ++iterator;
                }
                stack.Erase(iterator);
                std::cout << "The figure has been removed\n";
            }
            catch(std::runtime_error &error) {
                std::cout << error.what() << "\n";
            }
            break;
        }
        case 5:
        {
            
            auto print_stack = [](const auto & figure) {
                std::cout << figure << "\n";
            };
            std::cout << "All figures:\n";
            std::for_each(stack.begin(), stack.end(), print_stack);
            
            break;
        }
        case 6:
        {
            std::cout << "The program has been completed.\n";
            return 0;
            break;
        }
        default:
            std::cout << "Entered invalid action!\n";
            break;
        }
        std::cout << "\n";
    }
}