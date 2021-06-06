#include <gtest/gtest.h>
#include "array.hpp"

using namespace skh;

TEST(array_test, constructors) {
    array<int, 2> a;
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a.max_size(), 2);

    EXPECT_THROW((array<int, 9>{1,4,5,0,0}), std::length_error);
    EXPECT_THROW((array<int, 2>{1,4,5,0,0}), std::length_error);

    array<int, 5> b{0,1,2,3,4};
    EXPECT_EQ(b.size(), 5);
    for (size_t i = 0; i < b.size(); i++) {
        EXPECT_EQ(b[i], i); 
    }
    
    std::initializer_list<double> il{1.1, 2.2, 3.3};

    EXPECT_THROW((array<double,4>(il)), std::length_error);
    EXPECT_THROW((array<double,2>(il)), std::length_error);

    array<double, 3> c(il);
    EXPECT_DOUBLE_EQ(c[0], 1.1);
    EXPECT_DOUBLE_EQ(c[1], 2.2);
    EXPECT_DOUBLE_EQ(c[2], 3.3);

    array<int, 5> d(b);
    EXPECT_EQ(b.size(), d.size());

    for (size_t i = 0; i < d.size(); i++) {
        EXPECT_EQ(b[i], d[i]);
    }

    array<int, 5> e(std::move(b));
    EXPECT_EQ(e.size(), d.size());

    for (size_t i = 0; i < e.size(); i++) {
        EXPECT_EQ(e[i], d[i]);
    }

}
