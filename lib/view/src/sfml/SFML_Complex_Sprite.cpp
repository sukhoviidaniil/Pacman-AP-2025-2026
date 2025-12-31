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
        std::unordered_map<infra::Status, std::unordered_map<infra::math::Direction, std::unique_ptr<ISFML_Sprite>>>
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
        return sprites_.at(status).at(dir)->sprite();
    }
}
