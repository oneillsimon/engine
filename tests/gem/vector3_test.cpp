//
// Created by simon on 10/05/2020.
//
#include <gtest/gtest.h>

#include <gem/vector3.h>

TEST(vector3_test, default_initialisation) {
    auto v = gem::vector3<int>();

    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
    EXPECT_EQ(v.z, 0);
}

TEST(vector3_test, initialisation) {
    auto v = gem::vector3<int>(1, 2, 3);

    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
}

TEST(vector3_test, scalar_initialisation) {
    auto v = gem::vector3<float>(10.6f);

    EXPECT_EQ(v.x, 10.6f);
    EXPECT_EQ(v.y, 10.6f);
    EXPECT_EQ(v.z, 10.6f);
}

TEST(vector3_test, array_initialisation) {
    auto values = std::array<int, 3>{ 4, 5, 6 };
    auto v = gem::vector3<int>(values);

    EXPECT_EQ(v.x, 4);
    EXPECT_EQ(v.y, 5);
    EXPECT_EQ(v.z, 6);
}

TEST(vector3_test, square_brackets_operator) {
    auto v = gem::vector3<int>(1, 2, 3);

    EXPECT_TRUE(v[0] == v.x && v[0] == 1);
    EXPECT_TRUE(v[1] == v.y && v[1] == 2);
    EXPECT_TRUE(v[2] == v.z && v[2] == 3);

    v[0] = 10;
    EXPECT_EQ(v.x, 10);

    v[0] -= 10;
    EXPECT_EQ(v.x, 0);
}

TEST(vector3_test, equality_operator) {
    auto a = gem::vector3<int>(1, 2, 3);
    auto b = gem::vector3<int>(1, 2, 3);

    EXPECT_TRUE(a == b);

    a.x++;
    EXPECT_FALSE(a == b);
}

TEST(vector3_test, inequality_operator) {
    auto a = gem::vector3<int>(1, 2, 3);
    auto b = gem::vector3<int>(4, 5, 6);

    EXPECT_TRUE(a != b);

    a = b;
    EXPECT_FALSE(a != b);
}

TEST(vector3_test, vector_addition_operators) {
    auto a = gem::vector3<int>(1, 9, 1);
    auto b = gem::vector3<int>(9, 1, 9);

    auto c = a + b;
    EXPECT_EQ(c, gem::vector3<int>(10, 10, 10));

    c += c;
    EXPECT_EQ(c, gem::vector3<int>(20, 20, 20));
}

TEST(vector3_test, vector_subtraction_operators) {
    auto a = gem::vector3<int>(5, 5, 5);
    auto b = gem::vector3<int>(3, 3, -3);

    auto c = a - b;
    EXPECT_EQ(c, gem::vector3<int>(2, 2, 8));

    c -= c;
    EXPECT_EQ(c, gem::vector3<int>(0, 0, 0));
}

TEST(vector3_test, vector_multiplication_operators) {
    auto a = gem::vector3<int>(1, 2, 3);
    auto b = gem::vector3<int>(1, 10, 100);

    auto c = a * b;
    EXPECT_EQ(c, gem::vector3<int>(1, 20, 300));

    auto d = gem::vector3<int>(2, 4, 8);
    d *= d;
    EXPECT_EQ(d, gem::vector3<int>(4, 16, 64));
}

TEST(vector3_test, vector_divisionion_operators) {
    auto a = gem::vector3<int>(10, 15, 100);
    auto b = gem::vector3<int>(2, 5, 10);

    auto c = a / b;
    EXPECT_EQ(c, gem::vector3<int>(5, 3, 10));

    auto d = gem::vector3<int>(9, 15, 49);
    d /= d;
    EXPECT_EQ(d, gem::vector3<int>(1, 1, 1));
}

TEST(vector3_test, scalar_addition_operators) {
    auto a = gem::vector3<float>();
    auto b = a + 5.0f;

    EXPECT_EQ(b, gem::vector3<float>(5.0f, 5.0f, 5.0f));

    b += 1.0f;
    EXPECT_EQ(b, gem::vector3<float>(6.0f, 6.0f, 6.0f));
}

TEST(vector3_test, scalar_subtraction_operators) {
    auto a = gem::vector3<float>();
    auto b = a - 1.0f;

    EXPECT_EQ(b, gem::vector3<float>(-1.0f, -1.0f, -1.0f));

    b -= 9.0f;
    EXPECT_EQ(b, gem::vector3<float>(-10.0f, -10.0f, -10.0f));
}

TEST(vector3_test, scalar_multiplication_operators) {
    auto a = gem::vector3<int>(1, 2, 10);
    auto b = a * 2;

    EXPECT_EQ(b, gem::vector3<int>(2, 4, 20));

    b *= 2;
    EXPECT_EQ(b, gem::vector3<int>(4, 8, 40));
}

TEST(vector3_test, scalar_division_operators) {
    auto a = gem::vector3<float>(10.0f, 20.0f, 1.0f);
    auto b = a / 2.0f;

    EXPECT_EQ(b, gem::vector3<float>(5.0f, 10.0f, 0.5f));

    b /= 10.0f;
    EXPECT_EQ(b, gem::vector3<float>(0.5f, 1.0f, 0.05f));
}

TEST(vector3_test, length) {
    auto a = gem::vector3<int>(1, 1, 1);
    EXPECT_EQ(a.length(), 1);

    auto b = gem::vector3<int>(5, 5, 5);
    EXPECT_EQ(b.length(), 8);

    auto c = gem::vector3<int>();
    EXPECT_EQ(c.length(), 0);
}

TEST(vector3_test, normalise) {
    auto a = gem::vector3<float>(3.0f, 2.0f, 1.0f);
    auto an = a.normalise();
    auto expected = gem::vector3<float>(0.801f, 0.534f, 0.267f);

    EXPECT_NEAR(an.x, expected.x, 0.001f);
    EXPECT_NEAR(an.y, expected.y, 0.001f);
    EXPECT_NEAR(an.z, expected.z, 0.001f);

    EXPECT_FLOAT_EQ(an.length(), 1.0f);

    auto b = gem::vector3<int>(1, 1, 1);
    auto bn = b.normalise();

    EXPECT_EQ(b, bn);
    EXPECT_EQ(b.length(), 1);
}

TEST(vector3_test, cross) {
    auto a = gem::vector3<int>(2, 3, 4);
    auto b = gem::vector3<int>(5, 6, 7);
    auto cross = a.cross(b);

    EXPECT_EQ(cross.x, -3);
    EXPECT_EQ(cross.y, 6);
    EXPECT_EQ(cross.z, -3);
}

TEST(vector3_test, dot) {
    auto a = gem::vector3<int>(2, 4, 6);
    auto b = gem::vector3<int>(1, 3, 5);

    auto dot = a.dot(b);

    EXPECT_EQ(dot, 44);
}
