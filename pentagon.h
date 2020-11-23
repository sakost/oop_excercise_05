//
// Created by sakost on 23.11.2020.
//

#ifndef OOP_EXCERCISE_05_PENTAGON_H
#define OOP_EXCERCISE_05_PENTAGON_H


#include <utility>
#include <algorithm>
#include <stdexcept>
#include <cmath>


template<typename T, typename AreaType=long double>
struct Pentagon {
    using self_type = Pentagon<T, AreaType>;
    using value_type = T;
    using area_type = AreaType;
    static const int sides_count = 5;

    Pentagon() {
        m_side_length = 1;
    }

    Pentagon(const self_type &other) = default;

    Pentagon(const self_type &&other) noexcept {
        m_side_length = other.m_side_length;
    }

    self_type &operator=(const self_type &other) = default;

    self_type &operator=(const self_type &&other) noexcept {
        m_side_length = other.m_side_length;
        return *this;
    }

    area_type m_side_length;

    explicit Pentagon(area_type side_length) {
        m_side_length = side_length;
    }

    AreaType area() {
        AreaType area = 0;
        area_type a = m_side_length / 2 / tanf128(180.l / sides_count);
        area = m_side_length * sides_count * a / 2;
        return area;
    }

    template<typename R, typename S>
    friend std::ostream &operator<<(std::ostream &out, const Pentagon<R, S> &pentagon) {
        out << "Side length: " << pentagon.m_side_length;
        return out;
    }

    template<typename R, typename S>
    friend std::istream &operator>>(std::istream &in, Pentagon<R, S> &pentagon) {
        in >> pentagon.m_side_length;
        if (pentagon.m_side_length <= 0) {
            throw std::logic_error("Size of sides of figure must be above zero");
        }
        return in;
    }
};


#endif //OOP_EXCERCISE_05_PENTAGON_H
