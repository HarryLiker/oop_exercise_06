#pragma once

#include <iostream>
#include <memory>
#include <iterator>
#include <exception>


template <class T>
struct Node;

template <class T>
void operator++(std::shared_ptr<Node<T>> &current_node) {
    if (current_node) {
        current_node = current_node->Next; // ????????????????????????????
    }
    else {
        throw std::out_of_range("Iterator has already nullptr\n");
    }
}

template <class T>
bool operator!=(const Node<T> &left_value, const Node<T> &right_value) {
    return &left_value != &right_value;
}

template <class T>
bool operator==(const Node<T> &left_value, const Node<T> &right_value) {
    return &left_value.Data == &right_value.Data;
}

template <class T>
std::ostream &operator<<(std::ostream &cout, const Node<T> &node) {
    cout << node.Data;
    return cout;
}


template <class T> 
struct Node {
    T Data; 
    std::shared_ptr<Node> Next;

    Node(): Next(nullptr) {}

    Node(const T &data): Data(data), Next(nullptr) {} 

    friend void operator++<>(std::shared_ptr<Node<T>> &node);

    friend bool operator!=<>(const Node<T> &left_value, const Node<T> &right_value);

    friend bool operator==<>(const Node<T> &left_value, const Node<T> &right_value);

    friend std::ostream &operator<<<>(std::ostream &cout, const Node<T> &node);
};



template <class T>
class Stack {
private:
    size_t Size = 0;
    std::shared_ptr<Node<T>> TopNode; 
public:

    class StackIterator {
    private:
        std::shared_ptr<Node<T>> Iterator;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        StackIterator(): Iterator(nullptr) {}

        explicit StackIterator(const std::shared_ptr<Node<T>> &another_iter): Iterator(another_iter) {}

        bool IsNull() {
            return Iterator == nullptr;
        }

        friend void operator++(StackIterator &iter) {
            ++iter.Iterator;
        }

        friend bool operator!=(const Stack<T>::StackIterator &left_value, const Stack<T>::StackIterator &right_value) {
            return left_value.Iterator != right_value.Iterator;
        }

        friend std::ostream &operator<<(std::ostream &out, const StackIterator &iter) {
            out << *iter.Iterator;
            return out;
        }

        Node<T> &operator*() {
            return *Iterator;
        }
    };

    Stack() noexcept: TopNode(nullptr) {}

    void Push(const T &element) {
        if (Size == 0) {
            Node<T> *new_node = new Node<T>(element);
            std::shared_ptr<Node<T>> new_pointer {new_node};
            TopNode = new_pointer;
        }
        else {
            Node<T> *new_node = new Node<T>(element);
            std::shared_ptr<Node<T>> new_pointer {new_node};
            new_pointer->Next = TopNode;
            TopNode = new_pointer;
        }
        Size++;
    }

    void Pop() {
        if (TopNode) {
            TopNode = TopNode->Next;
        }
        else {
            throw ("Stack is empty!\n");
        }
    }

    T Top() {
        if (TopNode) {
            return TopNode->Data;
        }
        else {
            throw ("Stack is empty!\n");
        }
    }

    void Erase(StackIterator iter) {
        if (iter->IsNull()) {
        }
    }
    
    StackIterator begin() {
        return StackIterator(TopNode);
    }

    StackIterator end() {
        return StackIterator(nullptr);
    }

};
