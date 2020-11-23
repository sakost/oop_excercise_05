//
// Created by sakost on 22.11.2020.
//

#ifndef OOP_EXCERCISE_05_FORWARD_VECTOR_ITERATOR_H
#define OOP_EXCERCISE_05_FORWARD_VECTOR_ITERATOR_H

#include <iterator>
#include <type_traits>
#include <memory>
#include <exception>
#include <cassert>
#include <functional>

template<typename container_type, typename T>
struct ForwardVectorIterator {
    using self_type = ForwardVectorIterator<container_type, T>;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;

    using size_type = std::size_t;

    bool compatible(self_type const &other) const {
        return container == other.container;
    }

    ForwardVectorIterator(value_type *ptr, container_type *container, size_type index) : container(container),
                                                                                         index(index) {
        this->ptr = ptr;
    }

    ForwardVectorIterator() = default;

    ForwardVectorIterator(self_type const &o) = default;

    ForwardVectorIterator &operator=(self_type const &o) = default;

    ~ForwardVectorIterator() = default;

    self_type &operator++() {
        if (++index > container->size()) {
            throw std::out_of_range("Iterator cannot be incremented past the end of range.");
        }
        return *this;
    }

    self_type operator++(int) {
        self_type tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(self_type const &other) const {
        assert(compatible(other));
        return index == other.index;
    }

    bool operator!=(self_type const &other) const {
        return !(*this == other);
    }

    reference operator*() const {
        if (ptr == nullptr) {
            throw std::bad_function_call();
        }
        return *(ptr + index);
    }

    reference operator->() const {
        if (ptr == nullptr) {
            throw std::bad_function_call();
        }
        return *(ptr->get() + index);
    }


    difference_type operator-(const self_type &other) const {
        return difference_type(index - other.index);
    }

    self_type &operator--() {
        if (index <= 0) {
            throw std::out_of_range("Iterator cannot be decremented past the end of range.");
        }
        index--;
        return *this;
    }

    self_type operator--(int) {
        self_type tmp = *this;
        --*this;
        return tmp;
    }


    value_type *ptr = nullptr;
    container_type *container = nullptr;
    size_type index = 0;
};


#endif //OOP_EXCERCISE_05_FORWARD_VECTOR_ITERATOR_H
