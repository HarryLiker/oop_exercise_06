#pragma once 

#include <iostream>
#include <vector>

template<class T, size_t BLOCK_SIZE>
class Allocator {
private:
    T* Buffer;
    std::vector<T*> Vector;
public:
    using allocator_type = Allocator;
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    Allocator(): Vector(), Buffer(nullptr) {
        static_assert(BLOCK_SIZE > 0);
    }

    explicit Allocator (const Allocator<T, BLOCK_SIZE> &another_allocator): Allocator() {
        Buffer = new T[BLOCK_SIZE];
        for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
            Buffer[i] = another_allocator.Buffer[i];
            Vector.push_back(&Buffer[i]);
        }
    }

    T *allocate(const std::size_t &size) {
        if (Buffer == nullptr) {
            Buffer = new T[BLOCK_SIZE];
            for (std::size_t i = 0; i < BLOCK_SIZE; i++) {
                Vector.push_back(&Buffer[i]);
            }
        }
        if (Vector.size() < size) {
            throw(std::bad_alloc());
        }
        else {
            T* pointer = Vector.front();
            for (std::size_t i = 0; i < size; ++i) {
                Vector.pop_back();
            }
            return pointer;
        }
    }

    template<class U>
    struct rebind {
        using other = Allocator<U, BLOCK_SIZE>;
    };

    void deallocate(T* pointer, std::size_t) {
        ;
    }

    template<class OTHER_T, class... ARGS>
    void construct(OTHER_T* p, ARGS... arguments) {
        *p = OTHER_T(std::forward<ARGS>(arguments)...);
    }

    ~Allocator() {
        delete [] Buffer;
    }
};