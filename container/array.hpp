//author sargis khachatryan

#ifndef SKH_ARRAY_HPP
#define SKH_ARRAY_HPP

#include <algorithm> //std::copy, std::move, std::swap
#include <cstdio> //std::size_t
#include <stdexcept> //std::length_error, std::out_of_range
#include <initializer_list> //std::initializer_list

namespace skh 
{

template<typename T, std::size_t N>
class array {
///////////////////////////////     TYPES     ///////////////////////////////
public:
using value_type = T;
using size_type = std::size_t;
using reference = value_type&;
using const_reference = const value_type&;
using pointer = value_type*;
using const_pointer = const value_type*;
/////////////////////     Constructors & =operators     /////////////////////
public:
    /**
     * @brief Construct a new array object
     * default constructor, elements are not initialized
     */
    constexpr array() {}

    /**
     * @brief Construct a new array object
     * fill an array with the given elements
     * @param list initializer list consisting of T type elements
     */
    constexpr array(const std::initializer_list<T>& list) {
        if (list.size() != N) {
            throw std::length_error("Initializer list size is not same as array's.");
        }

        auto it = list.begin();
        for(size_type i = 0; i < list.size(); ++i) {
            _data[i] = *it;
            ++it;
        }
    }

    /**
     * @brief Construct a new array object
     * fill an array with the given elements
     * @param list initializer list consisting of T type elements
     */
    constexpr array(std::initializer_list<T>&& list) {
        if (list.size() != N) {
            throw std::length_error("Initializer list size is not same as array's.");
        }

        auto it = list.begin();
        for(size_type i = 0; i < list.size(); ++i) {
            _data[i] = std::move(*it);
            ++it;
        }
    }

public:
    /**
     * @brief Copy constructor
     * @param rhs is an array to be copied
     */
    constexpr array(const array& rhs) {
        for(size_type i = 0; i < N; ++i) {
            _data[i] = rhs[i];
        }
    }

    /**
     * @brief Move constructor
     * @param rhs is an array to be moved
     */
    constexpr array(array&& rhs) noexcept {
        for(size_type i = 0; i < N; ++i) {
            _data[i] = std::move(rhs[i]);
        }
    }

    /**
     * @brief copy assignment operator
     * with const
     * @param rhs array to be copied
     * @return array& with elements of rhs
     */
    constexpr array& operator=(const array& rhs) {
        if (this != &rhs) {
            std::copy(rhs.data(), rhs.data() + N, _data);
        }
        return *this;
    }

    /**
     * @brief move assignment operator
     * @param rhs array to be moved
     * @return array& with moved elements of rhs
     */
    constexpr array& operator=(array&& rhs) noexcept {
        if (this != &rhs) {
            for (size_type i = 0; i < N; ++i) {
                _data[i] = std::move(rhs[i]);
            }
        }
        return *this;
    }

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
    constexpr reference at(size_type pos) {
        if (pos >= N) {
            throw std::out_of_range("Invalid index, out of bounds.");
        }
        return _data[pos];
    }

    constexpr const_reference at(size_type pos) const {
        if (pos >= N) {
            throw std::out_of_range("Invalid index, out of bounds.");
        }
        return _data[pos];
    }

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
    constexpr reference operator[](size_type pos) noexcept {
        return _data[pos];
    }

    constexpr const_reference operator[](size_type pos) const noexcept {
        return _data[pos];
    }

public:
    /**
     * @brief Returns a reference to the first element in the container.
     * Calling front on an empty container is undefined.
     * 
     * @note For a container c, the expression c.front() 
     * is equivalent to *c.begin().
     * @return reference to the first element
     */
    constexpr reference front() noexcept {
        return _data[0];
    }

    constexpr const_reference front() const noexcept {
        return _data[0];
    }

    /**
     * @brief Returns a reference to the last element in the container.
     * Calling back on an empty container causes undefined behavior. 
     * 
     * @note For a non-empty container c, the expression c.back() 
     * is equivalent to *std::prev(c.end())
     * @return Reference to the last element 
     */
    constexpr reference back() noexcept {
        return _data[N - 1];
    }

    constexpr const_reference back() const noexcept {
        return _data[N - 1];
    }

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
    constexpr pointer data() noexcept {
        return _data;
    }

    constexpr const_pointer data() const noexcept {
        return _data;
    }

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
    [[nodiscard]] constexpr bool empty() const noexcept {
        return N == 0;
    }

    /**
     * @brief Returns the number of elements in the container, 
     * i.e. std::distance(begin(), end()).
     * 
     * @return The number of elements in the container 
     */
    constexpr size_type size() const noexcept {
        return N;
    }

    /**
     * @brief Returns the maximum number of elements the container 
     * is able to hold due to system or library implementation limitations,
     * i.e. std::distance(begin(), end()) for the largest container. 
     * 
     * @return Maximum number of elements 
     */
    constexpr size_type max_size() const noexcept {
        return N;
    }

/////////////////////////////     Operations     ////////////////////////////
public:
    /**
     * @brief Assigns the given value value to all elements in the container
     * 
     * @param value the value to assign to the elements
     */
    constexpr void fill(const T& value) {
        for (size_type i = 0; i < N; ++i) {
            _data[i] = value;
        }
    }

    /**
     * @brief Exchanges the contents of the container with those of other.
     * 
     * @param other container to exchange the contents with
     */
    constexpr void swap(array& rhs) noexcept { //TODO noexcept(std::is_nothrow_swappable_v<T>)
        for (size_type i = 0; i < N; ++i) {
            std::swap(_data[i], rhs[i]);
        }
    } 

private:
    value_type _data[N];
};

//TODO non member functions
} //namespace skh

#endif //SKH_ARRAY_HPP
