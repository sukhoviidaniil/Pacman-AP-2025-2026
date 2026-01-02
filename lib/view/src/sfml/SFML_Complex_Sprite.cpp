/***************************************************************
 * Project:       Pacman
 * File:          SFML_Complex_Sprite.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-17
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

#include "view/sfml/SFML_Complex_Sprite.h"

namespace view {

    SFML_Complex_Sprite::SFML_Complex_Sprite(
        std::unordered_map<infra::Status, std::unordered_map<infra::math::Direction, std::unique_ptr<ISFML_Sprite>, infra::math::DirectionHash>>
        data) : sprites_(std::move(data)){
    }

    void SFML_Complex_Sprite::elapsed(const float delta) const {
        for (const auto& m_status : sprites_) {
            for (auto& m_direction : m_status.second) {
                m_direction.second->elapsed(delta);
            }
        }
    }


    sf::Sprite SFML_Complex_Sprite::sprite(
        infra::Status status,
        infra::math::Direction dir
    ) {
        auto& dir_map = sprites_.at(status);

        // 1. If Any is requested, we take the first direction.
        if (dir == infra::math::Direction::Any) {
            if (!dir_map.empty())
                return dir_map.begin()->second->sprite();
            else
                throw std::out_of_range("No directions available for this Complex_Sprite");
        }

        // 2. If there is an exact direction, return it.
        auto it = dir_map.find(dir);
        if (it != dir_map.end())
            return it->second->sprite();

        // 3. If the Any key is present, use it as a fallback option.
        it = dir_map.find(infra::math::Direction::Any);
        if (it != dir_map.end())
            return it->second->sprite();

        // 4. Otherwise, throw an exception
        throw std::out_of_range("Direction not found for this Complex_Sprite");
    }
}
