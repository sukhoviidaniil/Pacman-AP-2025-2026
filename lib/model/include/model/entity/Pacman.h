/***************************************************************
 * Project:       Pacman
 * File:          Pacman.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-15
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
#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Actor.h"

namespace model::entity {

    /**
     * @brief Represents the Pacman character.
     *
     * Extends Actor with buff mechanics.
     */
    class Pacman : public Actor {
    public:
        /**
         * @brief Destructor.
         */
        ~Pacman() override;

        /**
         * @brief Constructs a Pacman with size, position, hitbox, and speed.
         *
         * @param size Visual or logical size
         * @param position Initial position in world coordinates
         * @param hitbox Collision hitbox
         * @param speed Movement speed
         */
        Pacman(float size, const infra::math::Point2 &position, std::unique_ptr<collision::HitBox> hitbox, float speed);

        /**
         * @brief Updates the Pacman state over elapsed time.
         *
         * @param deltaTime Time since last update
         */
        void elapsed(float deltaTime);

        /**
         * @brief Updates the remaining duration of active buffs.
         *
         * @param deltaTime Time elapsed since last update
         */
        void take_buff(float deltaTime);

        /**
         * @brief Checks if Pacman currently has an active buff.
         *
         * @return True if buff is active
         */
        [[nodiscard]] bool has_buff() const;

        /**
         * @brief Returns the remaining buff duration.
         *
         * @return Buff time in seconds
         */
        [[nodiscard]] float buff_time() const;
    private:
        ///< Remaining duration of active buff
        float buff_time_ = 0;
    };
}

#endif //PACMAN_PACMAN_H