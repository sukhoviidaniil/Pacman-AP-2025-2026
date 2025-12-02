/***************************************************************
 * Project:       Pacman
 * File:          collision.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-18
 * Modified:      []
 *
 * Description:   []
 *
 * Contact:
 *   Email:       sukhovii.daniil@gmail.com
 *
 * Disclaimer:
 *   This file is part of Pacman.
 *   Unauthorized use, reproduction, or distribution is prohibited.
***************************************************************/

#include <gtest/gtest.h>
#include "logic/collision/World_CC.h"

class First_Test : public testing::TestWithParam<std::vector<std::string>> {

    public:
    First_Test() = default;
    void SetUp() override {

    }
    void TearDown() override {

    }
    ~First_Test() override = default;
};

TEST_P(First_Test, CompareFilesTest) {
    EXPECT_TRUE(true) << "True";
}
INSTANTIATE_TEST_SUITE_P(
    Test_Tests, // Test group name
    First_Test, // Test Class
    ::testing::Values(
        std::vector<std::string>{"", "", ""}
    )
);


