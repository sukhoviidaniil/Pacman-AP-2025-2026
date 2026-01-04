/***************************************************************
 * Project:       Pacman
 * File:          Actor.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-13
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
#ifndef PACMAN_ACTOR_H
#define PACMAN_ACTOR_H

#include "infra/math/Direction.h"
#include "infra/internal/Status.h"
#include "model/entity/Entity.h"
#include "model/grid/TileGrid.h"


namespace model::entity {

    /**
     * @brief Base class for movable game entities (actors).
     *
     * Extends Entity to include movement, direction, speed, and status.
     */
    class Actor : public Entity {
    public:
        /**
         * @brief Destructor.
         */
        ~Actor() override;

        /**
         * @brief Constructs an actor with initial direction and speed.
         *
         * @param name Name of the actor
         * @param size Visual or logical size
         * @param position Initial position in world coordinates
         * @param hitbox Collision hitbox
         * @param current_direction Initial movement direction
         * @param speed Movement speed (m/s)
         */
        Actor(const std::string &name, float size, const infra::math::Point2 &position,
              std::unique_ptr<collision::HitBox> hitbox, const infra::math::Direction &current_direction, float speed);

        /**
         * @brief Sets the actor's current movement direction.
         */
        void set_direction(const infra::math::Direction &direction);

        /**
         * @brief Convenience methods to set movement direction.
         */
        void to_left();
        void to_right();
        void to_up();
        void to_down();


        /**
         * @brief Returns the actor's current movement direction.
         */
        [[nodiscard]] infra::math::Direction get_direction() const;

        /**
         * @brief Moves the actor according to speed, direction, delta time, and the tile grid.
         *
         * @param deltaTime Time elapsed since last movement
         * @param grid Tile grid for collision/constraints
         */
        void move(float deltaTime, const model::TileGrid &grid);

        infra::Status status_ = infra::Status::Alive; ///< Current status of the actor
    protected:
        ///< Current movement direction
        infra::math::Direction current_direction_;
        ///< Direction intended after current movement
        infra::math::Direction next_direction_;
        ///< Movement speed in m/s
        float speed_;
        ///< Movement permission level
        Permission permission_ = Permission::Low;

        /**
         * @brief Returns the actor's current speed.
         */
        [[nodiscard]] virtual float speed() const;

        /**
         * @brief Returns the actor's movement permission level.
         */
        [[nodiscard]] virtual Permission permission() const;
    };
}

#endif //PACMAN_ACTOR_H