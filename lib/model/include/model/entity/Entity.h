/***************************************************************
 * Project:       Pacman
 * File:          Entity.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-10-23
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
#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

#include <memory>

#include "model/collision/HitBox.h"
#include "infra/presentation/external/Rect.h"

namespace model {

    /**
     * @brief Base class for all game entities.
     *
     * Each entity has a name, a size, a position, and a collision hitbox.
     * Provides accessors for these properties and a method to get a bounding rectangle.
     */
    class Entity {
    public:
        virtual ~Entity();

        /**
         * @brief Constructs an entity.
         *
         * @param name Name identifier
         * @param size Visual or logical size of the entity
         * @param position Initial position in world coordinates
         * @param hitbox Collision hitbox for the entity
         */
        Entity(
            std::string name, float size, const infra::math::Point2 &position, std::unique_ptr<collision::HitBox> hitbox
        );

        // ===== Getters =====

        /**
         * @brief Returns the entity's name.
         */
        [[nodiscard]] std::string name() const;

        /**
         * @brief Returns the entity's size.
         */
        [[nodiscard]] float size() const;

        /**
         * @brief Returns the entity's position in world coordinates.
         */
        [[nodiscard]] infra::math::Point2 position() const;

        /**
         * @brief Returns a const reference to the entity's hitbox.
         */
        [[nodiscard]] const collision::HitBox& hitboxe() const;

        /**
         * @brief Returns the rectangular bounding box of the entity.
         */
        [[nodiscard]] infra::ui::Rect rect() const;

    protected:
        ///< Position in world coordinates
        infra::math::Point2 position_;
        ///< Collision hitbox
        std::unique_ptr<collision::HitBox> hitbox_;
        ///< Size of the entity
        float sprite_size_;
        ///< Entity name
        std::string name_;
    };
}


#endif //PACMAN_ENTITY_H