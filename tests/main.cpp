//
// Created by simon on 29/05/2020.
//

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::GTEST_FLAG(output) = "xml:coverage/report.xml";
    std::cout << "Second: " << ::testing::GTEST_FLAG(output).c_str() << std::endl;
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}