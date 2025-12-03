/***************************************************************
 * Project:       Pacman
 * File:          Actor.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-20
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
#ifndef PACMAN_ACTOR_VIEW_H
#define PACMAN_ACTOR_VIEW_H

#include "graphics/view/Entity_View.h"
#include "graphics/Sprite_Group.h"
#include "logic/model/Actor.h"
#include <memory>

namespace Graphics::View {


    struct Actor_View_Info {
        std::string sprite_group_name;
    };

    class Actor_View: public Entity_View {
        std::shared_ptr<Sprite_Group> sprite_;
        std::shared_ptr<Logic::Model::Actor> actor_model_ = nullptr;

        public:

        [[nodiscard]] Math::Vector2 get_position() const override;

        explicit Actor_View(const std::shared_ptr<Sprite_Group>& sprite);
        void set_actor_model(const std::shared_ptr<Logic::Model::Actor>& actor_model);

        void render(sf::RenderWindow& window, const Math::Vector2& pixel_pos) const override;
    };
}

#endif //PACMAN_ACTOR_VIEW_H