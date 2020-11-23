//
// Created by sakost on 23.11.2020.
//

#ifndef OOP_EXCERCISE_05_PENTAGON_H
#define OOP_EXCERCISE_05_PENTAGON_H


#include <utility>
#include <algorithm>
#include <stdexcept>
#include <cmath>

template <typename T>
T square_distance(const std::pair<T, T>& coord1, const std::pair<T, T>& coord2){
    return (coord2.first - coord1.first)*(coord2.first - coord1.first) + (coord2.second - coord1.second)*(coord2.second - coord1.second);
}

template<typename T, typename AreaType=long double>
struct Pentagon {
    using vertex_t = std::pair<T, T>;
    using self_type = Pentagon<T, AreaType>;
    using value_type = T;
    using area_type = AreaType;

    Pentagon() {
        int n = sizeof(m_coords) / sizeof(m_coords[0]);
        for (size_t i = 0; i < n; ++i){
            m_coords[i] = {0, 0};
        }
    }
    Pentagon(const self_type& other) = default;
    Pentagon(const self_type&& other)   noexcept{
        int n = sizeof(m_coords) / sizeof(m_coords[0]);
        for (size_t i = 0; i < n; ++i){
            m_coords[i] = other.m_coords[i];
        }
    }
    self_type &operator=(const self_type& other) = default;
    self_type &operator=(const self_type&& other)   noexcept{
        int n = sizeof(m_coords) / sizeof(m_coords[0]);
        for (size_t i = 0; i < n; ++i){
            m_coords[i] = other.m_coords[i];
        }
        return *this;
    }

    vertex_t m_coords[5];

    explicit Pentagon(vertex_t coords[5]){
        validate(coords);
    }

    static bool validate(const vertex_t *coords) {
//        return true;
        T dist = square_distance(coords[0], coords[1]);

        for (int i = 0; i < 4; ++i) {
            if(dist != square_distance(coords[i], coords[i+1])){
                throw std::logic_error("Sides of pentagon must be equal");
            }
        }
        return true;
    }

    AreaType area(){
        AreaType area = 0;
        int n = sizeof(m_coords) / sizeof(m_coords[0]);
        for (size_t i = 1; i < n; ++i)
            area += this->m_coords[i - 1].first * this->m_coords[i].second -
                    this->m_coords[i].first * this->m_coords[i - 1].second;
        area += this->m_coords[n - 1].first * this->m_coords[0].second - this->m_coords[0].first * this->m_coords[n - 1].second;
        return std::abs(area) / 2;
    }

    template <typename R, typename S>
    friend std::ostream& operator<<(std::ostream& out, const Pentagon<R, S> &pentagon){
        int n = sizeof(m_coords) / sizeof(m_coords[0]);
        for (size_t i = 0; i < n; ++i){
            out << '(' << pentagon.m_coords[i].first << ", " << pentagon.m_coords[i].second << "); ";
        }
        Pentagon<R, S>::validate(pentagon.m_coords);
        return out;
    }
    template <typename R, typename S>
    friend std::istream& operator>>(std::istream& in, Pentagon<R, S> &pentagon){
        int n = sizeof(m_coords) / sizeof(m_coords[0]);
        for (size_t i = 0; i < n; ++i){
            in >> pentagon.m_coords[i].first >> pentagon.m_coords[i].second;
        }
        Pentagon<R, S>::validate(pentagon.m_coords);
        return in;
    }
};


#endif //OOP_EXCERCISE_05_PENTAGON_H
