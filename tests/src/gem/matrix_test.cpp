//
// Created by simon on 10/05/2020.
//
#include <gtest/gtest.h>

#include <gem/matrix.h>

TEST(matrix_test, default_initialisation) {
    auto m = gem::matrix<int, 2, 2>();

    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], 0);
    EXPECT_EQ(m[1][0], 0);
    EXPECT_EQ(m[1][1], 0);
}

TEST(matrix_test, initializer_list_initilisation) {
    auto m = gem::matrix<int, 2, 3>{ { 1, 2, 3 }, { 4, 5, 6 } };

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 4);
    EXPECT_EQ(m[1][1], 5);
    EXPECT_EQ(m[1][2], 6);
}

TEST(matrix_test, fill) {
    auto m = gem::matrix<int, 2, 2>();

    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], 0);
    EXPECT_EQ(m[1][0], 0);
    EXPECT_EQ(m[1][1], 0);

    m.fill(101);

    EXPECT_EQ(m[0][0], 101);
    EXPECT_EQ(m[0][1], 101);
    EXPECT_EQ(m[1][0], 101);
    EXPECT_EQ(m[1][1], 101);
}

TEST(matrix_test, iteration) {
    auto m = gem::matrix<int, 2, 2>{ { 1, 2 }, { 3, 4 } };

    int expected = 1;

    for (auto row : m) {
        for (auto e : row) {
            EXPECT_EQ(e, expected);
            expected++;
        }
    }
}

TEST(matrix_test, square_brackets_operator) {
    auto a = gem::matrix<int, 2, 2>{ { 1, 2 }, { 3, 4 } };
    auto first_row = a[0];
    auto second_row = a[1];

    auto expected = gem::vector<int, 2>{ 1, 2 };
    EXPECT_EQ(first_row, expected);

    expected = gem::vector<int, 2>{ 3, 4 };
    EXPECT_EQ(second_row, expected);

    a[0] = gem::vector<int, 2>{ 101, 102 };
    auto c = gem::matrix<int, 2, 2>{ { 101, 102 }, { 3, 4 } };
    EXPECT_EQ(a, c);
}

TEST(matrix_test, equality_operator) {
    auto a = gem::matrix<int, 2, 1>{ { 10 }, { 99 } };
    auto b = gem::matrix<int, 2, 1>{ { 10 }, { 99 } };

    EXPECT_TRUE(a == b);

    a[0][0]++;
    EXPECT_FALSE(a == b);
}

TEST(matrix_test, inequality_operator) {
    auto a = gem::matrix<int, 2, 2>{ { 1, 2 }, { 3, 4 } };
    auto b = gem::matrix<int, 2, 2>{ { 5, 6 }, { 7, 8 } };

    EXPECT_TRUE(a != b);

    a = b;
    EXPECT_FALSE(a != b);
}

TEST(matrix_test, matrix_addition_operators) {
    auto a = gem::matrix<int, 2, 2>{ { 1, 1 }, { 1, 1 } };
    auto b = gem::matrix<int, 2, 2>{ { 4, 4 }, { 4, 4 } };

    auto c = a + b;
    auto expected = gem::matrix<int, 2, 2>({ { 5, 5 }, { 5, 5 } });
    EXPECT_EQ(c, expected);

    c += gem::matrix<int, 2, 2>({ { 1, 2 }, { 2, 1 } });
    expected = gem::matrix<int, 2, 2>({ { 6, 7 }, { 7, 6 } });
    EXPECT_EQ(c, expected);
}

TEST(matrix_test, matrix_substraction_operators) {
    auto a = gem::matrix<int, 2, 2>{ { 1, 2 }, { 3, 4 } };
    auto b = gem::matrix<int, 2, 2>{ { 1, 1 }, { 1, 1 } };

    auto c = a - b;
    auto expected = gem::matrix<int, 2, 2>{ { 0, 1 }, { 2, 3 } };
    EXPECT_EQ(c, expected);

    c -= b;
    expected = gem::matrix<int, 2, 2>{ { -1, 0 }, { 1, 2 } };
    EXPECT_EQ(c, expected);
}

TEST(matrix_test, matrix_multiplication_operator) {
    auto a = gem::matrix<int, 2, 3>{ { 1, 2, 3 }, { 4, 5, 6 } };
    auto b = gem::matrix<int, 3, 2>{ { 7, 8 }, { 9, 10 }, { 11, 12 } };

    auto c = a * b;
    auto expected = gem::matrix<int, 2, 2>{ { 58, 64 }, { 139, 154 } };
    EXPECT_EQ(c, expected);
}

TEST(matrix_test, scalar_addition_operators) {
    auto a = gem::matrix<int, 2, 2>();
    auto b = a + 5;
    auto expected = gem::matrix<int, 2, 2>{ { 5, 5 }, { 5, 5 } };
    EXPECT_EQ(b, expected);

    a += 10;
    expected = gem::matrix<int, 2, 2>{ { 10, 10 }, { 10, 10 } };
    EXPECT_EQ(a, expected);
}

TEST(matrix_test, scalar_subtraction_operators) {
    auto a = gem::matrix<int, 2, 2>();
    auto b = a - 5;
    auto expected = gem::matrix<int, 2, 2>{ { -5, -5 }, { -5, -5 } };
    EXPECT_EQ(b, expected);

    a -= 10;
    expected = gem::matrix<int, 2, 2>{ { -10, -10 }, { -10, -10 } };
    EXPECT_EQ(a, expected);
}

TEST(matrix_test, scalar_multiplication_operators) {
    auto a = gem::matrix<int, 2, 2>{ { 2, 4 }, { 8, 16 } };
    auto b = a * 2;
    auto expected = gem::matrix<int, 2, 2>{ { 4, 8 }, { 16, 32 } };
    EXPECT_EQ(b, expected);

    a *= 10;
    expected = gem::matrix<int, 2, 2>{ { 20, 40 }, { 80, 160 } };
    EXPECT_EQ(a, expected);
}

TEST(matrix_test, scalar_division_operators) {
    auto a = gem::matrix<int, 2, 2>{ { 2, 4 }, { 8, 16 } };
    auto b = a / 2;
    auto expected = gem::matrix<int, 2, 2>{ { 1, 2 }, { 4, 8 } };
    EXPECT_EQ(b, expected);

    a /= 4;
    expected = gem::matrix<int, 2, 2>{ { 0, 1 }, { 2, 4 } };
    EXPECT_EQ(a, expected);
}

TEST(matrix_test, identity) {
    auto a = gem::matrix<int, 3, 3>::identity();
    auto b = gem::matrix<int, 3, 3>{ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
    EXPECT_EQ(a, b);
}

TEST(matrix_test, row) {
    auto a = gem::matrix<int, 2, 3>{ { 1, 2, 3 }, { 4, 5, 6 } };
    auto first_row = a.row(0);
    auto second_row = a.row(1);

    auto expected = gem::vector<int, 3>{ 1, 2, 3 };
    EXPECT_EQ(first_row, expected);

    expected = gem::vector<int, 3>{ 4, 5, 6 };
    EXPECT_EQ(second_row, expected);
}

TEST(matrix_test, column) {
    auto a = gem::matrix<int, 3, 2>{{1, 2}, {3, 4}, {5, 6}};
    auto first_column = a.column(0);
    auto second_column = a.column(1);

    auto expected = gem::vector<int, 3>{1, 3, 5};
    EXPECT_EQ(first_column, expected);

    expected = gem::vector<int, 3>{ 2, 4, 6 };
    EXPECT_EQ(second_column, expected);
}