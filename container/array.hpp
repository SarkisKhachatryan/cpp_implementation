//author sargis khachatryan

#ifndef SKH_ARRAY_HPP
#define SKH_ARRAY_HPP

#include <cstdio>
#include <initializer_list>

namespace skh 
{

template<typename T, std::size_t N>
class array {
public:
    /**
     * @brief Construct a new array object
     * default constructor, all elements are zero initialized
     */
    array() : _size(N) {};

    /**
     * @brief Construct a new array object
     * fills an array with given value
     * @param value which should be inserted into array
     */
    array(T value) : _size(N) {
        for (size_t i = 0; i < _size - 1; ++i) {
            _data[i] = value;
        }
    };

    /**
     * @brief Construct a new array object
     * fill an array with the given elements
     * @param list initializer list consistion of T type elements
     */
    array(std::initializer_list<T> list) : _size(N) {
        if (list.size() > _size) {
            throw("Initializer list size is bigger than an array size");
        }
        for (std::size_t i = 0; i < list.size(); ++i) {
            auto it = list.begin();
            _data[i] = *it;
            ++it;
        }
    }

    /**
     * @brief Copy constructor
     * 
     * @param rhs is an array to be copied
     */
    array(const array& rhs) : _size(rhs.size()) {
        T* rhs_data = rhs.data();
        for (size_t i = 0; i < _size; ++i, ++rhs_data) {
            _data[i] = rhs_data[i];
        }
    }

    /**
     * @brief Move constructor
     * 
     * @param rhs is an array to be moved
     */
    array(array&& rhs) : _size(std::move(rhs.size())) {
        T* rhs_data = rhs.data();
        for (size_t i = 0; i < _size; ++i, ++rhs_data) {
            _data[i] = std::move(rhs_data[i]);
        }
    }

    std::size_t size() const {
        return _size;
    }

    const T* data() const {
        return _data;
    }


private:
    std::size_t _size;
    T _data[N];
};

} //namespace skh

#endif //SKH_ARRAY_HPP
