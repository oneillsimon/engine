//
// Created by simon on 10/05/2020.
//
#include <gtest/gtest.h>

#include <gem/quaternion.h>

TEST(quaternion_test, quaternion_multiplication_operators) {
    auto a = gem::quaternion(3, 4, 3, 2);
    auto b = gem::quaternion(3.9f, -1, -3, 4);

    auto c = a * b;
    auto expected = gem::quaternion(10.8f, 34.7f, -12.6f, 9.3f);

    EXPECT_FLOAT_EQ(c.x, expected.x);
    EXPECT_FLOAT_EQ(c.y, expected.y);
    EXPECT_FLOAT_EQ(c.z, expected.z);
    EXPECT_FLOAT_EQ(c.w, expected.w);

    auto d = gem::quaternion(35, 4, 1, 6);
    d *= gem::quaternion(9, -51, -11, 8);

    expected = gem::quaternion(341, 120, -1879, -52);

    EXPECT_FLOAT_EQ(d.x, expected.x);
    EXPECT_FLOAT_EQ(d.y, expected.y);
    EXPECT_FLOAT_EQ(d.z, expected.z);
    EXPECT_FLOAT_EQ(d.w, expected.w);
}
