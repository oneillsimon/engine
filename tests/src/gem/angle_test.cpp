//
// Created by simon on 06/06/2020.
//

#include <gtest/gtest.h>

#include <gem/angle.h>

TEST(angle_test, constructor) {
    auto a = gem::angle(12);

    EXPECT_NEAR(a.radians, 12, 0.001);
    EXPECT_NEAR(a.degrees, 687.549, 0.001);
}

TEST(angle_test, from_radians) {
    auto a = gem::angle::from_radians(4);

    EXPECT_NEAR(a.radians, 4, 0.001);
    EXPECT_NEAR(a.degrees, 229.183, 0.001);
}

TEST(angle_test, from_degrees) {
    auto a = gem::angle::from_degrees(360);

    EXPECT_NEAR(a.radians, 6.283, 0.001);
    EXPECT_NEAR(a.degrees, 360, 0.001);
}
