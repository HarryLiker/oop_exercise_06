#pragma once 
#include <iterator>

template <class T>
class TIterator {
private:
    std::shared_ptr<T> Iterator;
public:
    using iterator_categoty = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    TIterator(): Iterator(nullptr) {}

    explicit TIterator(const std::shared_ptr<N> &another_iter): Iterator(another_iter) {}

    bool operator== (const TIterator &second_iter) {
        return (Iterator == second_iter.Iterator);
    }

    bool operator!= (const TIterator &second_iter) {
        return (Iterator != second_iter.Iterator);
    }

    TIterator operator++ () {
        ++iter.Iterator;
    }

    T &operator*() {
        return *Iterator;
    }


};