/***************************************************************
 * Project:       Pacman
 * File:          SFML_Render.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-09
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
#ifndef PACMAN_SFML_RENDER_H
#define PACMAN_SFML_RENDER_H


#include "Sprite_Group.h"

#include "SFML/Graphics.hpp"
#include <string>

namespace Graphics{

    class SFML_Render {
        std::string texture_folder_;
        std::string configuration_folder_;
        //
        std::map<
            // key - name of file
            std::string,
            sf::Texture
        > textures_;

        // key - construct name
        std::map<
            std::string,
            sf::Sprite
        > sprites_; // TODO CODE FOR

        // key - entity name
        std::map<
            std::string,
            std::shared_ptr<Sprite_Group>
        > grouped_sprites_;

        // for speedup of render
        std::map<
            std::string,
            sf::RenderTexture
        > rendered_textures_; // TODO CODE FOR

        protected:
        sf::Texture& find_texture(const std::string& name);

        public:

        /** TODO DOC
         *
         * @param texture_folder
         * @param configuration_folder
         */
        SFML_Render(std::string texture_folder, std::string configuration_folder);

        /** TODO DOC
         *
         * @param filename
         * @return
         */
        sf::Texture& load_texture(const std::string& filename);

        /** TODO DOC
         * TODO CODE
         *
         * @param filename
         */
        void load_Sprite(const std::string& filename);

        /** TODO DOC
         *
         * @param filename
         */
        void load_Sprite_Group(const std::string& filename);

        /** TODO DOC
         *
         * @param name
         * @return
         */
        std::shared_ptr<Sprite_Group> get_Sprite_Group(const std::string& name);
    };
}

#endif //PACMAN_SFML_RENDER_H