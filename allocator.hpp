#pragma once 

#include <iostream>
#include <vector>

template<class T, size_t BLOCK_SIZE>
class Allocator {
private:
    T* Buffer;
    std::vector<T*> Vector;
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    Allocator(): Buffer{}, Free_index(0) {
        static_assert(BLOCK_SIZE > 0);
    }

    T *Allocate(const std::size_t &size) {
        if (Buffer == nullptr) {
            Buffer = new T[BLOCK_SIZE];
            for (std::size_t i = 0; i < BLOCK_SIZE; i++) {
                Vector[i] = &Buffer[i];
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
    struct Rebind {
        using other = Allocator<U, BLOCK_SIZE>;
    }

    void Dellocate(T* pointer, std::size_t) {
        Vector.erase(pointer);
    }

    ~Allocator() {
        delete [] Buffer;
    }
};