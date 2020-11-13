//
// Created by simon on 10/05/2020.
//
#include <gtest/gtest.h>

#include <gem/vector4.h>

TEST(vector4_test, default_initialisation) {
    auto v = gem::vector4<int>();

    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
    EXPECT_EQ(v.z, 0);
    EXPECT_EQ(v.w, 0);
}

TEST(vector4_test, list_initialisation) {
    auto v = gem::vector4<int>{ 0, 2, 1, 3 };

    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 1);
    EXPECT_EQ(v.w, 3);
}

TEST(vector4_test, initialisation) {
    auto v = gem::vector4<int>(1, 2, 3, 4);

    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
    EXPECT_EQ(v.w, 4);
}

TEST(vector4_test, scalar_initialisation) {
    auto v = gem::vector4<float>(10.6f);

    EXPECT_EQ(v.x, 10.6f);
    EXPECT_EQ(v.y, 10.6f);
    EXPECT_EQ(v.z, 10.6f);
    EXPECT_EQ(v.w, 10.6f);
}

TEST(vector4_test, array_initialisation) {
    auto values = std::array<int, 4>{ 4, 5, 6, 7 };
    auto v = gem::vector4<int>(values);

    EXPECT_EQ(v.x, 4);
    EXPECT_EQ(v.y, 5);
    EXPECT_EQ(v.z, 6);
    EXPECT_EQ(v.w, 7);
}

TEST(vector4_test, square_brackets_operator) {
    auto v = gem::vector4<int>(1, 2, 3, 4);

    EXPECT_TRUE(v[0] == v.x && v[0] == 1);
    EXPECT_TRUE(v[1] == v.y && v[1] == 2);
    EXPECT_TRUE(v[2] == v.z && v[2] == 3);
    EXPECT_TRUE(v[3] == v.w && v[3] == 4);

    v[0] = 10;
    EXPECT_EQ(v.x, 10);

    v[0] -= 10;
    EXPECT_EQ(v.x, 0);
}

TEST(vector4_test, square_brackets_out_of_range) {
    auto v = gem::vector4<int>();

    EXPECT_THROW(auto _ = v[4], std::out_of_range);
    EXPECT_THROW(v[4] = 0, std::out_of_range);

}

TEST(vector4_test, equality_operator) {
    auto a = gem::vector4<int>(1, 2, 3, 4);
    auto b = gem::vector4<int>(1, 2, 3, 4);

    EXPECT_TRUE(a == b);

    a.x++;
    EXPECT_FALSE(a == b);
}

TEST(vector4_test, inequality_operator) {
    auto a = gem::vector4<int>(1, 2, 3, 4);
    auto b = gem::vector4<int>(5, 6, 7, 8);

    EXPECT_TRUE(a != b);

    a = b;
    EXPECT_FALSE(a != b);
}

TEST(vector4_test, vector_addition_operators) {
    auto a = gem::vector4<int>(1, 9, 1, 9);
    auto b = gem::vector4<int>(9, 1, 9, 1);

    auto c = a + b;
    EXPECT_EQ(c, gem::vector4<int>(10, 10, 10, 10));

    c += c;
    EXPECT_EQ(c, gem::vector4<int>(20, 20, 20, 20));
}

TEST(vector4_test, vector_subtraction_operators) {
    auto a = gem::vector4<int>(5, 5, 5, 5);
    auto b = gem::vector4<int>(3, 3, -3, -3);

    auto c = a - b;
    EXPECT_EQ(c, gem::vector4<int>(2, 2, 8, 8));

    c -= c;
    EXPECT_EQ(c, gem::vector4<int>(0, 0, 0, 0));
}

TEST(vector4_test, scalar_addition_operators) {
    auto a = gem::vector4<float>();
    auto b = a + 5.0f;

    EXPECT_EQ(b, gem::vector4<float>(5.0f, 5.0f, 5.0f, 5.0f));

    b += 1.0f;
    EXPECT_EQ(b, gem::vector4<float>(6.0f, 6.0f, 6.0f, 6.0f));
}

TEST(vector4_test, scalar_subtraction_operators) {
    auto a = gem::vector4<float>();
    auto b = a - 1.0f;

    EXPECT_EQ(b, gem::vector4<float>(-1.0f, -1.0f, -1.0f, -1.0f));

    b -= 9.0f;
    EXPECT_EQ(b, gem::vector4<float>(-10.0f, -10.0f, -10.0f, -10.0f));
}

TEST(vector4_test, scalar_multiplication_operators) {
    auto a = gem::vector4<int>(1, 2, 10, 50);
    auto b = a * 2;

    EXPECT_EQ(b, gem::vector4<int>(2, 4, 20, 100));

    b *= 2;
    EXPECT_EQ(b, gem::vector4<int>(4, 8, 40, 200));
}

TEST(vector4_test, scalar_division_operators) {
    auto a = gem::vector4<float>(10.0f, 20.0f, 1.0f, 3.0f);
    auto b = a / 2.0f;

    EXPECT_EQ(b, gem::vector4<float>(5.0f, 10.0f, 0.5f, 1.5f));

    b /= 10.0f;
    EXPECT_EQ(b, gem::vector4<float>(0.5f, 1.0f, 0.05f, 0.15f));
}

TEST(vector4_test, length) {
    auto a = gem::vector4<int>(1, 1, 1, 1);
    EXPECT_EQ(a.length(), 2);

    auto b = gem::vector4<int>(5, 5, 5, 5);
    EXPECT_EQ(b.length(), 10);

    auto c = gem::vector4<int>();
    EXPECT_EQ(c.length(), 0);
}

TEST(vector4_test, normalise) {
    auto a = gem::vector4<float>(3.0f, 2.0f, 1.0f, 1.0f);
    auto an = a.normalise();
    auto expected = gem::vector4<float>(0.774f, 0.516f, 0.258f, 0.258f);

    EXPECT_NEAR(an.x, expected.x, 0.001f);
    EXPECT_NEAR(an.y, expected.y, 0.001f);
    EXPECT_NEAR(an.z, expected.z, 0.001f);
    EXPECT_NEAR(an.z, expected.w, 0.001f);

    EXPECT_FLOAT_EQ(an.length(), 1.0f);
}

TEST(vector4_test, dot) {
    auto a = gem::vector4<int>(2, 4, 6, 8);
    auto b = gem::vector4<int>(1, 3, 5, 7);

    auto dot = a.dot(b);

    EXPECT_EQ(dot, 100);
}

TEST(vector4_test, to_string) {
    auto v = gem::vector4<int>(4, 5, 6, 0);
    EXPECT_EQ(v.to_string(), "{ 4i 5i 6i 0i }");
}

TEST(vector4_test, stringstream_operator) {
    auto v = gem::vector4<float>(10, 11, 7, 999);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), "{ 10f 11f 7f 999f }");
}
