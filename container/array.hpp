//author sargis khachatryan

#ifndef SKH_ARRAY_HPP
#define SKH_ARRAY_HPP

#include <algorithm> //std::copy, std::move, std::swap
#include <cstdio> //std::size_t
#include <stdexcept> //std::length_error, std::out_of_range
#include <initializer_list> //std::initializer_list

namespace skh 
{

using value_type = T;
using size_type = std::size_t;
using reference = value_type&;
using const_reference = const value_type&;
using pointer = value_type*;
using const_pointer = const value_type*;

template<typename value_type, size_type N>
class array {
/////////////////////     Constructors & =operators     /////////////////////
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

public:
    /**
     * @brief Copy constructor
     * @param rhs is an array to be copied
     */
    constexpr array(const array& rhs);

    /**
     * @brief Move constructor
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

///////////////////////////     Element access     //////////////////////////
public:
    /**
     * @brief Returns a reference to the element at specified location pos, 
     * with bounds checking. 
     * 
     * If pos is not within the range of the container, an exception 
     * of type std::out_of_range is thrown. std::out_of_range if 
     * !(pos < size()). 
     * 
     * @param pos position of the element to return
     * @return reference to element at index pos
     */
    constexpr reference at(size_type pos);
    constexpr const_reference at(size_type pos) const;

    /**
     * @brief Returns a reference to the element at specified location pos.
     * No bounds checking is performed. 
     * 
     * Unlike std::map::operator[], this operator never inserts a 
     * new element into the container. Accessing a nonexistent element 
     * through this operator is undefined behavior.
     * 
     * @param pos position of the element to return
     * @return Reference to the requested element.  
     */
    constexpr reference operator[](size_type pos);
    constexpr const_reference operator[](size_type pos) const;

public:
    /**
     * @brief Returns a reference to the first element in the container.
     * Calling front on an empty container is undefined.
     * 
     * @note For a container c, the expression c.front() 
     * is equivalent to *c.begin().
     * @return reference to the first element
     */
    constexpr reference front();
    constexpr const_reference front() const;

    /**
     * @brief Returns a reference to the last element in the container.
     * Calling back on an empty container causes undefined behavior. 
     * 
     * @note For a non-empty container c, the expression c.back() 
     * is equivalent to *std::prev(c.end())
     * @return Reference to the last element 
     */
    constexpr reference back();
    constexpr const_reference back() const;

    /**
     * @brief Returns pointer to the underlying array serving as element 
     * storage.
     * 
     * The pointer is such that range [data(); data() + size()) is always 
     * a valid range, even if the container is empty (data() is not 
     * dereferenceable in that case).
     * 
     * @note If size() is 0, data() may or may not return a null pointer.
     * @return Pointer to the underlying element storage. For non-empty 
     * containers, the returned pointer compares equal to the address 
     * of the first element.  
     */
    constexpr pointer data();
    constexpr const_pointer data() const;

/////////////////////////////     Iteretors     /////////////////////////////
public:
//TODO

//////////////////////////////     Capacity     /////////////////////////////
public:
    /**
     * @brief Checks if the container has no elements, 
     * i.e. whether begin() == end().
     * 
     * @return true if the container is empty
     * @return false otherwise
     */
    [[nondiscard]] constexpr bool empty() const noexcept;

    /**
     * @brief Returns the number of elements in the container, 
     * i.e. std::distance(begin(), end()).
     * 
     * @return The number of elements in the container 
     */
    constexpr size_type size() const noexcept;

    /**
     * @brief Returns the maximum number of elements the container 
     * is able to hold due to system or library implementation limitations,
     * i.e. std::distance(begin(), end()) for the largest container. 
     * 
     * @return Maximum number of elements 
     */
    constexpr size_type max_size() const noexcept;

/////////////////////////////     Operations     ////////////////////////////
public:
    /**
     * @brief Assigns the given value value to all elements in the container
     * 
     * @param value the value to assign to the elements
     */
    constexpr void fill(const T& value);

    /**
     * @brief Exchanges the contents of the container with those of other.
     * 
     * @param other container to exchange the contents with
     */
    constexpr void swap(array& rhs) noexcept; //TODO noexcept(std::is_nothrow_swappable_v<T>)

private:
    value_type _data[N];
};

//TODO non member functions

/////////////////////////////////////////////////////////////////////////////
//////////////////////////     Implementation     ///////////////////////////
/////////////////////////////////////////////////////////////////////////////

template<typename value_type, size_type N>
constexpr array<value_type,N>::array() {};

template<typename value_type, size_type N>
constexpr array<value_type,N>::array(const std::initializer_list<value_type>& list) {
    if constexpr(list.size() != N) {
        throw std::length_error("Initializer list size is not same as array's.");
    }

    auto it = list.begin();
    for(size_type i = 0; i < list.size(); ++i) {
        _data[i] = *it;
        ++it;
    }
}

template<typename value_type, size_type N>
constexpr array<value_type,N>::array(std::initializer_list<value_type>&& list) {
    if constexpr(list.size() != N) {
        throw std::length_error("Initializer list size is not same as array's.");
    }

    auto it = list.begin();
    for(size_type i = 0; i < list.size(); ++i) {
        _data[i] = std::move(*it);
        ++it;
    }
}

template<typename value_type, size_type N>
constexpr array<value_type,N>::array(const array& rhs) {
    for(size_type i = 0; i < N; ++i) {
        _data[i] = rhs[i];
    }
}

template<typename value_type, size_type N>
constexpr array<value_type,N>::array(array&& rhs) noexcept {
    for(size_type i = 0; i < N; ++i) {
        _data[i] = std::move(rhs[i]);
    }
}

template<typename value_type, size_type N>
constexpr array<value_type,N>& array<value_type,N>::operator=(array& rhs) {
    for(size_type i = 0; i < N; ++i) {
        std::swap(_data[i], rhs[i]);
    }
    return *this;
}

template<typename value_type, size_type N>
constexpr array<value_type,N>& array<value_type,N>::operator=(const array& rhs){
    if constexpr(this != &rhs) {
        std::copy(rhs.data(), rhs.data() + N, _data);
    }
    return *this;
}

template<typename value_type, size_type N>
constexpr array<value_type,N>& array<value_type,N>::operator=(array&& rhs) noexcept {
    if constexpr(this != &rhs) {
        for (size_type i = 0; i < N; ++i) {
            _data[i] = std::move(rhs[i])
        }
    }
    return *this;
}

template<typename value_type, size_type N>
constexpr reference array<value_type,N>::at(size_type pos) {
    if constexpr(pos >= N) {
        throw std::out_of_range("Invalid index, out of bounds.")
    }
    return _data[pos];
}

template<typename value_type, size_type N>
constexpr const_reference array<value_type,N>::at(size_type pos) const {
    if constexpr(pos >= N) {
        throw std::out_of_range("Invalid index, out of bounds.")
    }
    return _data[pos];
}

template<typename value_type, size_type N>
constexpr reference array<value_type,N>::operator[](size_type pos) {
    return _data[pos]; 
}

template<typename value_type, size_type N>
constexpr const_reference array<value_type,N>::operator[](size_type pos) const {
    return _data[pos];
}

template<typename value_type, size_type N>
constexpr reference array<value_type,N>::front() {
    return _data[0]; 
}

template<typename value_type, size_type N>
constexpr const_reference array<value_type,N>::front() const {
    return _data[0];
}

template<typename value_type, size_type N>
constexpr reference array<value_type,N>::back() {
    return _data[N - 1]; 
}

template<typename value_type, size_type N>
constexpr const_reference array<value_type,N>::back() const {
    return _data[N - 1];
}

template<typename value_type, size_type N>
constexpr reference array<value_type,N>::data() {
    return _data; 
}

template<typename value_type, size_type N>
constexpr const_reference array<value_type,N>::data() const {
    return _data;
}

template<typename value_type, size_type N>
[[nondiscard]] constexpr bool empty() const noexcept {
    return N == 0;
}

template<typename value_type, size_type N>
constexpr size_type size() const noexcept {
    return N;
}

template<typename value_type, size_type N>
constexpr size_type max_size() const noexcept {
    return N;
}

template<typename value_type, size_type N>
constexpr void fill(const T& value) {
    for (size_type i = 0; i < N; ++i) {
        _data[i] = value;
    }
}

template<typename value_type, size_type N>
constexpr void swap(array& rhs) noexcept {
    for (size_type i = 0; i < N; ++i) {
        std::swap(_data[i], rhs[i]);
    }
}


} //namespace skh

#endif //SKH_ARRAY_HPP
