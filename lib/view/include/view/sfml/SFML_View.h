/***************************************************************
 * Project:       Pacman
 * File:          SFML_View.h
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
#ifndef PACMAN_VIEW_SFML_H
#define PACMAN_VIEW_SFML_H
#include <map>
#include <memory>
#include <string>
#include "SFML/Graphics.hpp"
#include "infra/ast/view/View.h"
#include "view/View.h"
#include "view/sfml/SFML_Complex_Sprite.h"
#include "view/sfml/ISFML_Event_Source.h"

namespace view {
    class SFML_View : public View, public ISFML_Event_Source{
    public:
        SFML_View(const infra::ast::View &info, const std::string & dir_path);

        void track_local(const std::shared_ptr<infra::event::Event_Bus>& bus) override;
        void track_global(const std::shared_ptr<infra::event::Event_Bus>& bus) override;
        bool poll_event(sf::Event& e) override;

        [[nodiscard]] infra::math::Vector2 screen_size() const override;
        void render(const view::ui::RenderFrame & graph) override;

        using infra::ast::SpriteVisitor::visit;
        void visit(const infra::ast::Sprite&) override;
        void visit(const infra::ast::ComplexSprite&) override;

        void render_warning(const infra::ui::Rect &rect);

        using view::ui::RenderVisitor::visit;
        void visit(const ui::RI_Label&) override;
        void visit(const ui::RI_Rectangle&) override;
        void visit(const ui::RI_Sprite&) override;
        void visit(const ui::RI_ComplexSprite&) override;

    protected:

        const sf::Texture &get_Texture(const std::string &using_texture, const std::string &by_who);

    private:

        // key - name
        std::map<
            std::string,
            sf::Texture
        > textures_;

        // key - name
        std::map<
            std::string,
            sf::Font
        > fonts_;

        // key - construct name
        std::map<
            std::string,
            sf::Sprite
        > sprites_;

        // key - entity name
        std::map<
            std::string,
            std::unique_ptr<SFML_Complex_Sprite>
        > complex_sprites_;

        sf::RenderWindow window_;
    };
}

#endif //PACMAN_VIEW_SFML_H