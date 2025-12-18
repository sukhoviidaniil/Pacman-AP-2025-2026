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

#include "SFML_Complex_Sprite.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "view/View.h"

namespace view {
    class SFML_View : public View {
    public:
        SFML_View(const infra::ast::View &info, const std::string & texture_dir_path);
        void render(const infra::ast::Scene_Graph& graph) const;
        void track(const std::shared_ptr<core::Stage>& stage);

    protected:

        std::optional<sf::Texture> get_Texture(const std::string& using_texture);

        void visit(const infra::ast::Sprite&) override;

        void visit(const infra::ast::Complex_Sprite&) override;
    private:

        sf::RenderWindow window_;
        // key - name of file
        std::map<
            std::string,
            sf::Texture
        > textures_;

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
    };
}

#endif //PACMAN_VIEW_SFML_H