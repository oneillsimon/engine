//
// Created by simon on 06/06/2020.
//

#include <gtest/gtest.h>

#include <gem/angle.h>
#include <gem/matrix4.h>
#include <gem/vector3.h>

TEST(matrix4_test, translate) {
    auto v = gem::vector3<float>{ 45.0f, 3.1f, 1.0f, };

    auto expected = gem::matrix4<float> {
            { 1, 0, 0, v.x },
            { 0, 1, 0, v.y },
            { 0, 0, 1, v.z },
            { 0, 0, 0, 1 },
    };

    EXPECT_EQ(gem::matrix4<float>::translation(v.x, v.y, v.z), expected);
    EXPECT_EQ(gem::matrix4<float>::translation(v), expected);
}

TEST(matrix4_test, scale) {
    auto v = gem::vector3<float>{ 2.0f, 6.0f, 100.0f, };

    auto expected = gem::matrix4<float> {
            { v.x, 0, 0, 0 },
            { 0, v.y, 0, 0 },
            { 0, 0, v.z, 0 },
            { 0, 0, 0, 1 },
    };

    EXPECT_EQ(gem::matrix4<float>::scale(v.x, v.y, v.z), expected);
    EXPECT_EQ(gem::matrix4<float>::scale(v), expected);
}