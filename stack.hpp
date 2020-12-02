#pragma once

#include <iostream>
#include <memory>
//#include "iterator.hpp"
#include <exception>
#include "allocator.hpp"

template <class T, class ALLOCATOR>
class Stack {
private:
    struct Node;

    using allocator_type = typename ALLOCATOR::template rebind<Node>::other;

    struct deleter {
        allocator_type stack_node_deleter;
        deleter(): stack_node_deleter() {};
        deleter(allocator_type *another_deleter): stack_node_deleter(another_deleter) {}

        void operator() (void *pointer) {
            stack_node_deleter.deallocate((Node*)pointer, 1);
        }
    };


    struct Node {
        T Data;
        std::shared_ptr<Node> Next;

        Node() noexcept: Data(), Next(nullptr) {};
        explicit Node(const T &element) noexcept: Data(element), Next(nullptr) {}

        friend bool operator == (const Node &left_value, const Node &right_value) {
            return &left_value.Data == &right_value.Data;
        }

        friend bool operator != (const Node &left_value, const Node &right_value) {
            return &left_value.Data != &right_value.Data;
        }

        friend std::ostream &operator<< (std::ostream & output, const Node &node) {
            output << node.Data;
            return output;
        }
    };

public:

    class StackIterator {
    private:
        std::shared_ptr<Node> Iterator;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        StackIterator(): Iterator(nullptr) {}

        explicit StackIterator(const std::shared_ptr<Node> &another_iter): Iterator(another_iter) {}

        void unvalidate() {
            Iterator = nullptr;
        }

        bool IsNull() {
            return Iterator == nullptr;
        }

        bool operator!=(const StackIterator &other_iterator) {
            return &other_iterator.Iterator->Data != &this->Iterator->Data;
        }

        bool operator==(const StackIterator &other_iterator) {
            return &other_iterator.Iterator->Data == &this->Iterator->Data;
        }

        StackIterator & operator++ () {
            if (this->Iterator != nullptr) {
                this->Iterator = this->Iterator->Next;
                return *this;
            }
            else {
                throw(std::runtime_error("Iterator points to nullptr!"));
            }
        }

        Node &operator*() {
            return *Iterator;
        }
    };

private:
    std::shared_ptr<Node> TopNode;
    int Size = 0;
    deleter stack_deleter;
    
public:  
    Stack() noexcept: TopNode() {}

    int FindSize() {
        return Size;
    }

    void Push(const T &element) {
        Node *new_node = stack_deleter.stack_node_deleter.allocate(sizeof(Node));
        stack_deleter.stack_node_deleter.construct(new_node, element);
        std::shared_ptr<Node> new_node_shared(new_node, stack_deleter);
        new_node_shared->Next = TopNode;
        TopNode = new_node_shared;
        Size++;
    }

    void Pop() {
        if (TopNode) {
            TopNode = TopNode->Next;
            Size--;
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

    void Insert(StackIterator iter, const T &element) {
        Node* new_node = stack_deleter.stack_node_deleter.allocate(sizeof(Node));
        stack_deleter.stack_node_deleter.construct(new_node, element);
        std::shared_ptr<Node> new_node_shared(new_node, stack_deleter);
        if (TopNode) {
            if (*iter == *TopNode) {
                new_node_shared->Next = TopNode;
                TopNode = new_node_shared;
                iter.unvalidate();
                return;
            }
            std::shared_ptr<Node> previous_node = TopNode;
            while (*previous_node->Next != *iter) {
                previous_node = previous_node->Next;
            }
            if (iter.IsNull()) {
                previous_node->Next = new_node_shared;
            }
            else {
                new_node_shared->Next = previous_node->Next;
                previous_node->Next = new_node_shared;
            }
        }
        else {
            TopNode = new_node_shared;
        }
        Size++;
        iter.unvalidate();
    }

    void Erase(StackIterator iter) {
        if (iter.IsNull()) {

        }
        else {
            if (*iter == *TopNode) {
                TopNode = TopNode->Next;
            }
            else {
                std::shared_ptr<Node> previous_node = TopNode;
                while (*previous_node->Next != *iter) {
                    previous_node = previous_node->Next;
                }
                previous_node->Next = previous_node->Next->Next;
                (*iter).Next = nullptr;
            }
            iter.unvalidate();
        }
        Size--;
    }


    StackIterator begin() {
        return StackIterator(TopNode);
    }

    StackIterator end() {
        return StackIterator(nullptr);
    }

    ~Stack() {}
};
