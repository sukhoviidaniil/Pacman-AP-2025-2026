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

#include "logic/collision/Collision_Control.h"
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


struct World_CC_Collision_p {
    Math::Vector2 position;
    float height;
    float width;
    bool expected;
};

class World_CC_Collision : public testing::TestWithParam<World_CC_Collision_p> {
public:
    Logic::Collision::World_CC cc;
    World_CC_Collision() {
        const std::vector<std::vector<int> > vec = {
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1}
        };
        cc = Logic::Collision::World_CC(vec);
    }

    void SetUp() override {

    }
    void TearDown() override {

    }
    ~World_CC_Collision() override = default;


};

TEST_P(World_CC_Collision, CompareFilesTest) {
    const auto hit_box = Logic::Collision::HitBoxe_Shape(GetParam().position, GetParam().height, GetParam().width, 0, 0);

    bool a = cc.collision(hit_box);
    EXPECT_TRUE(a == GetParam().expected) << "True";
}
INSTANTIATE_TEST_SUITE_P(
    Collision, // Test group name
    World_CC_Collision, // Test Class
    ::testing::Values(
        World_CC_Collision_p{{2,2}, 1, 1, false},
        World_CC_Collision_p{{1,1}, 1, 1, false},
        World_CC_Collision_p{{2,2}, 2, 2, false},
        World_CC_Collision_p{{0.5,1}, 1, 1, true},
        World_CC_Collision_p{{1,0.5}, 1, 1, true},
        World_CC_Collision_p{{2,4.5}, 1, 1, true}
    )
);
