#pragma once 
#include <vector>

template <class T, std::size_t BLOCK_SIZE>
class Allocator {
private:
    char *used_blocks;
    void **free_blocks;
    size_t free_count;
public:
    //using allocator_type = linear_allocator_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

    Allocator() {
        static_assert(BLOCK_SIZE > 0);
        used_blocks = (char*) malloc(sizeof(T) * BLOCK_SIZE);
        free_blocks = (void**) malloc(sizeof(void*) * BLOCK_SIZE);
        
        for (size_t i = 0; i < BLOCK_SIZE; i++) {
            free_blocks[i] = used_blocks + i * sizeof(T);
        }
        free_count = BLOCK_SIZE;
    }

    T* Allocate(size_t n) {
        T* result = nullptr;
        if (free_count > 0) {
            result = (T*)free_blocks[--free_count];
        }
        else {
            std::cout << "Allocator: No memory exeption!\n";
        }
        return result;
    }

    void Deallocate(T* pointer, size_t) {
        free_blocks[free_count++] = pointer;
    }

    void destroy(pointer p) {
        p->~T();
    }

    ~Allocator() {
        delete free_blocks;
        delete used_blocks;
    }
};