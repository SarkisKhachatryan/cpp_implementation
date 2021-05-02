//author sargis khachatryan

#ifndef SKH_ARRAY_HPP
#define SKH_ARRAY_HPP

#include <algorithm> //std::copy, std::move, std::swap
#include <cstdio> //std::size_t
#include <stdexcept> //std::length_error
#include <initializer_list> //std::initializer_list

namespace skh 
{

template<typename T, std::size_t N>
class array {

public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

public:
    /**
     * @brief Construct a new array object
     * default constructor, all elements are zero initialized
     */
    constexpr array();

    /**
     * @brief Construct a new array object
     * fill an array with the given elements
     * @param list initializer list consisting of T type elements
     */
    constexpr array(const std::initializer_list<T>& list);

    /**
     * @brief Construct a new array object
     * fill an array with the given elements
     * @param list initializer list consisting of T type elements
     */
    constexpr array(std::initializer_list<T>&& list);

    /**
     * @brief Copy constructor
     * 
     * @param rhs is an array to be copied
     */
    constexpr array(const array& rhs);

    /**
     * @brief Move constructor
     * 
     * @param rhs is an array to be moved
     */
    constexpr array(array&& rhs) noexcept;

    /**
     * @brief copy assignment operator
     * (copy-and-swap idiom)
     * @param rhs array to be copied
     * @return array& with elements of rhs
     */
    constexpr array& operator=(array& rhs);

    /**
     * @brief copy assignment operator
     * with const
     * @param rhs array to be copied
     * @return array& with elements of rhs
     */
    constexpr array& operator=(const array& rhs);

    /**
     * @brief move assignment operator
     * @param rhs array to be moved
     * @return array& with moved elements of rhs
     */
    constexpr array& operator=(array&& rhs) noexcept;

    constexpr size_type size() const {
        return _size;
    }

    constexpr pointer data() {
        return _data;
    }

    constexpr const_pointer data() const {
        return _data;
    }

private:
    value_type _data[N];
};

template<typename T, std::size_t N>
constexpr array<T,N>::array() {};

template<typename T, std::size_t N>
constexpr array<T,N>::array(const std::initializer_list<T>& list) {
    if constexpr(list.size() != N) {
        throw std::length_error("Initializer list size is not same as array's.");
    }

    auto it = list.begin();
    for(size_type i = 0; i < list.size(); ++i) {
        _data[i] = *it;
        ++it;
    }
}

template<typename T, std::size_t N>
constexpr array<T,N>::array(std::initializer_list<T>&& list) {
    if constexpr(list.size() != N) {
        throw std::length_error("Initializer list size is not same as array's.");
    }

    auto it = list.begin();
    for(size_type i = 0; i < list.size(); ++i) {
        _data[i] = std::move(*it);
        ++it;
    }
}

template<typename T, std::size_t N>
constexpr array<T,N>::array(const array& rhs) {
    for(size_type i = 0; i < N; ++i) {
        _data[i] = rhs[i];
    }
}

template<typename T, std::size_t N>
constexpr array<T,N>::array(array&& rhs) noexcept {
    for(size_type i = 0; i < N; ++i) {
        _data[i] = std::move(rhs[i]);
    }
}

template<typename T, std::size_t N>
constexpr array<T,N>& array<T,N>::operator=(array& rhs) {
    for(size_type i = 0; i < N; ++i) {
        std::swap(_data[i], rhs[i]);
    }
    return *this;
}

template<typename T, std::size_t N>
constexpr array<T,N>& array<T,N>::operator=(const array& rhs){
    if constexpr(this != &rhs) {
        std::copy(rhs.data(), rhs.data() + N, _data);
    }
    return *this;
}

template<typename T, std::size_t N>
constexpr array<T,N>& array<T,N>::operator=(array&& rhs) noexcept {
    if (this != &rhs) {
        for (size_type i = 0; i < N; ++i) {
            _data[i] = std::move(rhs[i])
        }
    }
    return *this;
}



} //namespace skh

#endif //SKH_ARRAY_HPP
