//
// Created by simon on 10/05/2020.
//
#include <gtest/gtest.h>

#include <gem/vector.h>
#include <gem/vector2.h>

TEST(vector2_test, default_initialisation) {
    auto v = gem::vector2<int>();

    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
}

TEST(vector2_test, initialisation) {
    auto v = gem::vector2<int>(1, 2);

    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
}

TEST(vector2_test, scalar_initialisation) {
    auto v = gem::vector2<float>(10.6f);

    EXPECT_EQ(v.x, 10.6f);
    EXPECT_EQ(v.y, 10.6f);
}

TEST(vector2_test, array_initialisation) {
    auto values = std::array<int, 2>{ 4, 5 };
    auto v = gem::vector2<int>(values);

    EXPECT_EQ(v.x, 4);
    EXPECT_EQ(v.y, 5);
}

TEST(vector2_test, square_brackets_operator) {
    auto v = gem::vector2<int>(1, 2);

    EXPECT_TRUE(v[0] == v.x && v[0] == 1);
    EXPECT_TRUE(v[1] == v.y && v[1] == 2);

    v[0] = 10;
    EXPECT_EQ(v.x, 10);

    v[0] -= 10;
    EXPECT_EQ(v.x, 0);
}

TEST(vector2_test, equality_operator) {
    auto a = gem::vector2<int>(1, 2);
    auto b = gem::vector2<int>(1, 2);

    EXPECT_TRUE(a == b);

    a.x++;
    EXPECT_FALSE(a == b);
}

TEST(vector2_test, inequality_operator) {
    auto a = gem::vector2<int>(1, 2);
    auto b = gem::vector2<int>(4, 5);

    EXPECT_TRUE(a != b);

    a = b;
    EXPECT_FALSE(a != b);
}

TEST(vector2_test, vector_addition_operators) {
    auto a = gem::vector2<int>(1, 9);
    auto b = gem::vector2<int>(9, 1);

    auto c = a + b;
    EXPECT_EQ(c, gem::vector2<int>(10, 10));

    c += c;
    EXPECT_EQ(c, gem::vector2<int>(20, 20));

    auto e = gem::vector2<int>(1, 1);
    auto f = gem::vector<int, 4>{ 1, 2, 3, 4 };
    EXPECT_EQ(e + f, gem::vector2<int>(2, 3));

    auto g = gem::vector<int, 1>{ 2 };
    EXPECT_EQ(e + g, gem::vector2<int>(3, 1));
}

TEST(vector2_test, vector_subtraction_operators) {
    auto a = gem::vector2<int>(5, 5);
    auto b = gem::vector2<int>(3, 3);

    auto c = a - b;
    EXPECT_EQ(c, gem::vector2<int>(2, 2));

    c -= c;
    EXPECT_EQ(c, gem::vector2<int>(0, 0));

    auto e = gem::vector2<int>(10, 10);
    auto f = gem::vector<int, 4>{ 1, 0, 9, 13 };
    EXPECT_EQ(e - f, gem::vector2<int>(9, 10));

    auto g = gem::vector<int, 1>{ 15 };
    EXPECT_EQ(e - g, gem::vector2<int>(-5, 10));
}

TEST(vector2_test, scalar_addition_operators) {
    auto a = gem::vector2<float>();
    auto b = a + 5.0f;

    EXPECT_EQ(b, gem::vector2<float>(5.0f, 5.0f));

    b += 1.0f;
    EXPECT_EQ(b, gem::vector2<float>(6.0f, 6.0f));
}

TEST(vector2_test, scalar_subtraction_operators) {
    auto a = gem::vector2<float>();
    auto b = a - 1.0f;

    EXPECT_EQ(b, gem::vector2<float>(-1.0f, -1.0f));

    b -= 9.0f;
    EXPECT_EQ(b, gem::vector2<float>(-10.0f, -10.0f));
}

TEST(vector2_test, scalar_multiplication_operators) {
    auto a = gem::vector2<int>(1, 2);
    auto b = a * 2;

    EXPECT_EQ(b, gem::vector2<int>(2, 4));

    b *= 2;
    EXPECT_EQ(b, gem::vector2<int>(4, 8));
}

TEST(vector2_test, scalar_division_operators) {
    auto a = gem::vector2<float>(10.0f, 20.0f);
    auto b = a / 2.0f;

    EXPECT_EQ(b, gem::vector2<float>(5.0f, 10.0f));

    b /= 10.0f;
    EXPECT_EQ(b, gem::vector2<float>(0.5f, 1.0f));
}

TEST(vector2_test, length) {
    auto a = gem::vector2<int>(1, 1);
    EXPECT_EQ(a.length(), 1);

    auto b = gem::vector2<int>(5, 5);
    EXPECT_EQ(b.length(), 7);

    auto c = gem::vector2<int>();
    EXPECT_EQ(c.length(), 0);
}

TEST(vector2_test, normalise) {
    auto a = gem::vector2<float>(5.0f, 2.0f);
    auto an = a.normalise();
    auto expected = gem::vector2<float>(0.928f, 0.371f);

    EXPECT_NEAR(an.x, expected.x, 0.001f);
    EXPECT_NEAR(an.y, expected.y, 0.001f);

    EXPECT_FLOAT_EQ(an.length(), 1.0f);

    auto b = gem::vector2<int>(1, 1);
    auto bn = b.normalise();

    EXPECT_EQ(b, bn);
    EXPECT_EQ(b.length(), 1);
}

TEST(vector2_test, dot) {
    auto a = gem::vector2<int>(2, 4);
    auto b = gem::vector2<int>(1, 3);

    auto dot = a.dot(b);

    EXPECT_EQ(dot, 14);
}