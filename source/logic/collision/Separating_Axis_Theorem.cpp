/***************************************************************
 * Project:       Pacman
 * File:          Separating_Axis_Theorem.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-15
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

#include "logic/collision/Separating_Axis_Theorem.h"

#include <limits>
#include <stdexcept>

namespace Logic::Collision {

    Separating_Axis_Theorem::Separating_Axis_Theorem() = default;

    bool Separating_Axis_Theorem::collision(const std::shared_ptr<HitBoxe> &first, const std::shared_ptr<HitBoxe> &second) {

        std::vector<Math::Vector2> axes;
        {
            std::vector<Math::Vector2> temp = first->get_normals();
            axes.insert(axes.end(), temp.begin(), temp.end());
            temp = second->get_normals();
            axes.insert(axes.end(), temp.begin(), temp.end());
        }
        if (axes.empty()) {
            std::vector<Math::Vector2> temp = first->get_vector_to(second);
        }
        if (axes.empty()) {
            throw std::runtime_error("No axis");
        }

        for (const auto &axis_raw : axes) {
            Math::Vector2 axis = axis_raw;
            axis.normalize(); // required for correct depth

            std::vector<float> f = first->project(axis);
            std::vector<float> s = second->project(axis);

            const float first_min  = f.front();
            const float first_max  = f.back();


            const float second_min = s.front();
            const float second_max = s.back();

            // === CONDITION FOR DIVISION ===
            if (first_max <= second_min || second_max <= first_min) {
                // Found the dividing axis → no collision
                return false;
            }
        }
        return true;
    }

    bool Separating_Axis_Theorem::collision(const HitBoxe_Shape &first, const HitBoxe_Shape &second) {
        std::vector<Math::Vector2> axes;
        {
            std::vector<Math::Vector2> temp = first.get_normals();
            axes.insert(axes.end(), temp.begin(), temp.end());
            temp = second.get_normals();
            axes.insert(axes.end(), temp.begin(), temp.end());
        }

        for (const auto &axis_raw : axes) {
            Math::Vector2 axis = axis_raw;
            axis.normalize(); // required for correct depth

            std::vector<float> f = first.project(axis);
            std::vector<float> s = second.project(axis);

            const float first_min  = f.front();
            const float first_max  = f.back();


            const float second_min = s.front();
            const float second_max = s.back();

            // === CONDITION FOR DIVISION ===
            if (first_max <= second_min || second_max <= first_min) {
                // Found the dividing axis → no collision
                return false;
            }
        }
        return true;
    }

    std::optional<Math::Vector2> Separating_Axis_Theorem::collision_mtv(const HitBoxe_Shape &first,
    const HitBoxe_Shape &second) {
        std::vector<Math::Vector2> axes;
        {
            auto temp = first.get_normals();
            axes.insert(axes.end(), temp.begin(), temp.end());
            temp = second.get_normals();
            axes.insert(axes.end(), temp.begin(), temp.end());
        }

        float min_overlap = std::numeric_limits<float>::max();
        Math::Vector2 mtv_axis;

        for (const auto &axis_raw : axes) {
            Math::Vector2 axis = axis_raw;
            axis.normalize(); // required for correct depth

            auto f = first.project(axis);
            auto s = second.project(axis);

            const float first_min  = f.front();
            const float first_max  = f.back();
            const float second_min = s.front();
            const float second_max = s.back();

            // Checking the dividing axis
            if (first_max < second_min || second_max < first_min) {
                // The figures do not intersect
                return std::nullopt;
            }

            // Calculate the overlap depth on this axis
            float overlap1 = first_max - second_min; // depth in one direction
            float overlap2 = second_max - first_min; // depth in another
            float overlap = (overlap1 < overlap2) ? overlap1 : overlap2;

            if (overlap < min_overlap) {
                min_overlap = overlap;
                // Choosing the right direction for MTV
                mtv_axis = axis;
                if (overlap == overlap2) mtv_axis = mtv_axis * -1; // направление
            }
        }

        // Minimum displacement vector
        return mtv_axis * min_overlap;
    }

}
