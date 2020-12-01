#include <iostream>
#include <algorithm>
#include "stack.hpp"
#include "triangle.hpp"

int menu() {
    while(1) {
        Stack<Triangle<int>> stack;
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
            break;
        }
        case 2:
        {
            int x,y;
            int side;
            std::cout << "Write the center coordinates: ";
            std::cin >> x >> y;
            std::cout << "Write size of the triangle: ";
            std::cin >> side;
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            break;
        }
        case 6:
        {
            std::cout << "The program has been completed.\n";
            break;
        }
        default:
            std::cout << "Entered invalid action!\n";
            break;
        }
        std::cout << "\n";
    }
}