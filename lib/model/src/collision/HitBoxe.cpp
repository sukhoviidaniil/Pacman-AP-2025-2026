/***************************************************************
 * Project:       Pacman
 * File:          HitBox.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-16
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

#include "model/collision/HitBox.h"

namespace model::collision {
    HitBox::HitBox(const int strength):
    strength_(strength){
    }

    HitBox::HitBox(const HitBox &other) = default;

    HitBox::~HitBox() = default;

    int HitBox::get_strength() const {
        return strength_;
    }

    std::vector<math::Vector2> HitBox::get_vector_to(const HitBox &hit_boxe) const {
        const std::vector<math::Point2> m_centers = get_centers();
        const std::vector<math::Point2> f_centers = hit_boxe.get_centers();
        std::vector<math::Vector2> all_centers;
        for (const auto& f_center : f_centers) {
            for (const auto& m_center : m_centers) {
                math::Vector2 dir = math::Vector2(f_center) - math::Vector2(m_center);
                all_centers.push_back(dir);
            }
        }
        return all_centers;
    }
}
