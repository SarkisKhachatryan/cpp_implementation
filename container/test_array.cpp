#include <gtest/gtest.h>
#include "array.hpp"

using namespace skh;

TEST(array_test, constructors) {
    array<int, 2> a;

    EXPECT_EQ(a[0], 0);
    EXPECT_EQ(a.size(), 2);
    
}
