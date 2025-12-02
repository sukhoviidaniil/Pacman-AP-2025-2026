/***************************************************************
 * Project:       Pacman
 * File:          world.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-02
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

#include "logic/collision/Separating_Axis_Theorem.h"
#include "logic/collision/World_Collision_Manager.h"

struct Test_Config {
    unsigned rows;
    unsigned cols;
    float tile_size;
};

struct Info_NTC{
    Test_Config test_config;
    Math::Vector2 pos;
    Math::Vector2 dir;
    Math::Vector2 expect;
};

class Next_Tile_Center : public testing::TestWithParam<Info_NTC> {
    protected:
    std::shared_ptr<Logic::Collision::World_Collision_Manager> WCM_;
    std::shared_ptr<Logic::Collision::Separating_Axis_Theorem> CM_;
    std::shared_ptr<Logic::Tile_Grid> grid_;
    public:
    void SetUp() override {
        const auto& params = GetParam();
        unsigned int rows = params.test_config.rows;
        unsigned int cols = params.test_config.cols;
        float tile_size = params.test_config.tile_size;
        CM_ = std::make_shared<Logic::Collision::Separating_Axis_Theorem>();
        grid_ = std::make_shared<Logic::Tile_Grid>(rows, cols, tile_size);
        WCM_ = std::make_shared<Logic::Collision::World_Collision_Manager>(CM_, grid_);
    }
    void TearDown() override {

    }
};

TEST_P(Next_Tile_Center, Test) {
    const Math::Vector2 tile_center = grid_->get_next_tile_center(GetParam().pos, GetParam().dir);
    EXPECT_TRUE(tile_center == GetParam().expect) << tile_center << " =/= " << GetParam().expect;
}
INSTANTIATE_TEST_SUITE_P(
    Test_Tests, // Test group name
    Next_Tile_Center, // Test Class
    ::testing::Values(
        Info_NTC({15, 15, 1}, Math::Vector2(0, 0), Math::Vector2(1,0), Math::Vector2(1,0)),
        Info_NTC({15, 15, 1}, Math::Vector2(0, 0), Math::Vector2(0.5,0.5), Math::Vector2(1,1)),
        Info_NTC({15, 15, 1}, Math::Vector2(0, 0), Math::Vector2(0,1), Math::Vector2(0,1)),
        Info_NTC({15, 15, 1}, Math::Vector2(0, 0), Math::Vector2(0,0), Math::Vector2(0,0)),
        Info_NTC({15, 15, 1}, Math::Vector2(1, 0), Math::Vector2(-1,0), Math::Vector2(0,0)),

        Info_NTC({14, 14, 1}, Math::Vector2(0.5f, 0.5f), Math::Vector2(1,0), Math::Vector2(1.5,0.5)),
        Info_NTC({14, 14, 1}, Math::Vector2(0.5f, 0.5f), Math::Vector2(0.5,0.5), Math::Vector2(1.5,1.5)),
        Info_NTC({14, 14, 1}, Math::Vector2(0, 0), Math::Vector2(0.5,0.5), Math::Vector2(0.5,0.5)),
        Info_NTC({14, 14, 1}, Math::Vector2(0.5f, 0.5f), Math::Vector2(0,1), Math::Vector2(0.5,1.5))
    )
);
