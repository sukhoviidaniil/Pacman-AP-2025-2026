/***************************************************************
 * Project:       Pacman
 * File:          Reader_JSON_protected.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-02
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

#include "infra/io/File_Reader.h"
#include "infra/io/readers/from_JSON.h"
#include "infra/io/readers/Reader_JSON.h"

namespace infra::io {

    std::vector<ast::Sprite> sprite_list_to_sprites(const ast::SpriteList& list) {
        std::vector<ast::Sprite> result;
        result.reserve(list.names.size());

        unsigned int index = 0;
        for (const auto &name : list.names) {
            ast::Sprite s;
            s.using_texture = list.using_texture;
            s.sprits_width = list.sprits_width;
            s.sprits_height = list.sprits_height;
            s.name = name;
            s.recLeft = list.recLeft.base + static_cast<int>(index)*list.recLeft.increase;
            s.recTop = list.recTop.base + static_cast<int>(index)*list.recTop.increase;
            result.push_back(s);
            ++index;
        }
        return result;
    }


    ast::View Reader_JSON::read_View(
    nlohmann::json data,
    const std::shared_ptr<const File_Reader> &fr
    ){
        auto vs = get_checked<ast::View>(data);

        std::string block_name = "Sprites";
        if (data.contains(block_name) && data[block_name].is_array()) {
            for (const auto &sprite : data[block_name]) {
                if (sprite.is_string()) {
                    ast::Sprite s = fr->read_Sprite(vs.view_directory + sprite.get<std::string>());
                    vs.sprites.push_back(s);
                    continue;
                }
                if (sprite.is_structured()) {
                    auto s = get_checked<ast::Sprite>(sprite);
                    vs.sprites.push_back(s);
                    continue;
                }
                std::string err = "View, one of the parameters in the “" + block_name + "” list is neither a file name nor an object.";
                LOG(err);
                throw std::invalid_argument(err);
            }
        }

        block_name = "SpriteLists";
        if (data.contains(block_name) && data[block_name].is_array()) {
            for (const auto &spritelist : data[block_name]) {
                if (spritelist.is_string()) {
                    ast::SpriteList s = fr->read_SpriteList(vs.view_directory + spritelist.get<std::string>());
                    std::vector<ast::Sprite> sp = sprite_list_to_sprites(s);
                    vs.sprites.insert(vs.sprites.end(), sp.begin(), sp.end());
                    continue;
                }
                if (spritelist.is_structured()) {
                    auto s = get_checked<ast::SpriteList>(spritelist);
                    std::vector<ast::Sprite> sp = sprite_list_to_sprites(s);
                    vs.sprites.insert(vs.sprites.end(), sp.begin(), sp.end());
                    continue;
                }
                std::string err = "View, one of the parameters in the “" + block_name + "” list is neither a file name nor an object.";
                LOG(err);
                throw std::invalid_argument(err);
            }
        }

        block_name = "ComplexSprites";
        if (data.contains(block_name) && data[block_name].is_array()) {
            for (const auto &sprite : data[block_name]) {
                if (sprite.is_string()) {
                    ast::ComplexSprite c = fr->read_Sprits_Group(vs.view_directory + sprite.get<std::string>());
                    vs.complex_sprites.push_back(c);

                    continue;
                }
                if (sprite.is_structured()) {
                    auto c = get_checked<ast::ComplexSprite>(sprite);
                    vs.complex_sprites.push_back(c);
                    continue;
                }
                std::string err = "View, one of the parameters in the “" + block_name + "” list is neither a file name nor an object.";
                LOG(err);
                throw std::invalid_argument(err);
            }
        }
        return vs;
    }
}
