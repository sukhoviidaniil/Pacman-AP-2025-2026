//
// Created by Kaede on 2025-10-23.
//

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    const int all_test = RUN_ALL_TESTS();
    std::cin.get();
    return all_test;
}
