//author sargis khachatryan

#ifndef SKH_ARRAY_HPP
#define SKH_ARRAY_HPP
#include <cstdio>

namespace skh 
{

template<typename T, std::size_t N>
class array {
public:
    array() : _size(N) {};

    // array()

private:
    std::size_t _size;
    T* _begin;
    T* _end;
};

} //namespace skh

#endif //SKH_ARRAY_HPP
