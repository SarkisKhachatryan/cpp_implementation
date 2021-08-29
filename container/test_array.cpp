#include <stdexcept> //std::length_error, std::out_of_range
#include <string> //std::string
#include <initializer_list> //std::initializer_list

#include <gtest/gtest.h>

#include "array.hpp" //skh::array

using namespace skh;

TEST(array_test, constructors) {
   array<int, 2> a;
   EXPECT_EQ(a.size(), 2);
   EXPECT_EQ(a.max_size(), 2);

   EXPECT_THROW((array<int, 9>{1, 4, 5, 0, 0}), std::length_error);
   EXPECT_THROW((array<int, 2>{1, 4, 5, 0, 0}), std::length_error);

   array<int, 5> b{0, 1, 2, 3, 4};
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

   array<int, 5> f;
   f = e;
   EXPECT_EQ(e.size(), f.size());
   for (size_t i = 0; i < f.size(); i++) {
       EXPECT_EQ(e[i], f[i]);
   }

   array<unsigned long, 2> g;
   g = array<unsigned long, 2>{0, 1};
   EXPECT_EQ(g.size(), 2);
   EXPECT_EQ(static_cast<unsigned long>(0), g[0]);
   EXPECT_EQ(static_cast<unsigned long>(1), g[1]);
}

TEST(array_test, element_access) {
   array<int, 3> a{0, 1, 2};

   EXPECT_EQ(a[0], 0);
   EXPECT_EQ(a[1], 1);
   EXPECT_EQ(a[2], 2);

   EXPECT_EQ(a.at(0), 0);
   EXPECT_EQ(a.at(1), 1);
   EXPECT_EQ(a.at(2), 2);

   EXPECT_EQ(a.front(), 0);
   EXPECT_EQ(a.back(), 2);

   int* ptr_a = a.data();
   EXPECT_EQ(*ptr_a, 0);
   ptr_a++;
   EXPECT_EQ(*ptr_a, 1);
   --ptr_a;
   EXPECT_EQ(*ptr_a, 0);
   ptr_a = ptr_a + 2;
   EXPECT_EQ(*ptr_a, 2);

   EXPECT_THROW(a.at(88), std::out_of_range);
   EXPECT_EQ(a.at(2) = 90, 90);

   const array<int, 3> b{10, 20, 30};
   EXPECT_EQ(b.at(0), 10);
   EXPECT_EQ(b.at(1), 20);
   EXPECT_EQ(b.at(2), 30);

   EXPECT_EQ(b[0], 10);
   EXPECT_EQ(b[1], 20);
   EXPECT_EQ(b[2], 30);

   EXPECT_EQ(b.front(), 10);
   EXPECT_EQ(b.back(), 30);

   EXPECT_THROW(b.at(88), std::out_of_range);

   const int* ptr_b = b.data();
   EXPECT_EQ(*ptr_b, 10);
   ptr_b++;
   EXPECT_EQ(*ptr_b, 20);
   --ptr_b;
   EXPECT_EQ(*ptr_b, 10);
   ptr_b = ptr_b + 2;
   EXPECT_EQ(*ptr_b, 30);
}

TEST(array_test, operations_and_capacity) {
   array<int, 0> a;
   EXPECT_TRUE(a.empty());
   EXPECT_EQ(a.size(), 0);

   struct X {
       int x = 10;
       double y = 1234.543;
       std::string z = "EMPTY";
   } x;

   array<X, 2> b;
   EXPECT_EQ(b[0].x, 10);
   EXPECT_DOUBLE_EQ(b.at(1).y, 1234.543);
   EXPECT_EQ(b.at(1).z, std::string{"EMPTY"});
   X neo_x;
   neo_x.x = 2345450;
   neo_x.y = 11324.453672;
   neo_x.z = "filled";

   b.fill(neo_x);
   EXPECT_EQ(b[0].x, 2345450);
   EXPECT_DOUBLE_EQ(b.at(1).y, 11324.453672);
   EXPECT_EQ(b.at(1).z, std::string{"filled"});

   array<X, 2> c;
   c.swap(b);
   EXPECT_EQ(c[0].x, 2345450);
   EXPECT_DOUBLE_EQ(c.at(1).y, 11324.453672);
   EXPECT_EQ(c.at(1).z, std::string{"filled"});
}
