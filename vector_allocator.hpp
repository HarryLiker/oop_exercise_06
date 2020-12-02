#include <iostream>
#include <memory>
#include "triangle.hpp"

template <class T>
struct Custom_allocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    Custom_allocator() noexcept {}

    template <class U>
    struct rebind {
        using other = Custom_allocator<U>;
    };

    T *allocate(size_t n) {
        std::cout << "Allocate\n";
        return static_cast<T*>(::operator new(n));
    }

    void deallocate(T *pointer, size_t) {
        std::cout << "Deallocate: " << pointer << "\n";
        ::delete(pointer);
    }

    template <typename U, typename... Args>
    void construct(U *pointer, Args &&... args) {
        new (pointer) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        std::cout << "Destroy\n";
        p->~T();
    }
};


template <class T, class ALLOCATOR>
struct Stack {
    struct StackNode {
        using allocator_type = typename ALLOCATOR::template rebind<StackNode>::other;

        T Data;

        std::shared_ptr<StackNode> Next;

        StackNode(const T &data): Data(data) {}
        ~StackNode() {}

        static allocator_type get_allocator() {
            static allocator_type allocator;
            return allocator;
        }

        void *operator new(size_t size) {
            return get_allocator().allocate(sizeof(StackNode));
        }

        void operator delete(void *pointer) {
            get_allocator().destroy((StackNode*)pointer);
            get_allocator().deallocate((StackNode*)pointer, sizeof(StackNode));
        }
    };

    std::shared_ptr<StackNode> TopNode;
    size_t Size = 0;

    void push(const T &data) {
        std::shared_ptr<StackNode> current = std::shared_ptr<StackNode>(new StackNode(data));
        if (!TopNode) {
            TopNode = current;
        }
        else {
            std::shared_ptr<StackNode> new_pointer {current};
            new_pointer->Next = TopNode;
            TopNode = new_pointer;
        }
        Size++;
    }

    void pop() {
        if (TopNode) {
            TopNode = TopNode->Next;
        }
    }
};