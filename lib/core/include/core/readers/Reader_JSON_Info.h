/***************************************************************
 * Project:       Pacman
 * File:          Reader_JSON_Info.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-03
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
#ifndef PACMAN_READER_JSON_INFO_H
#define PACMAN_READER_JSON_INFO_H
#include "json.hpp"
#include "core/World.h"
#include "math/Vector2.h"

namespace Core {
    class File_Reader;
    static Math::Vector2 from_json(const nlohmann::json& j) {
        Math::Vector2 v;
        v.x = j.at("x").get<float>();
        v.y = j.at("y").get<float>();
        return v;
    }

    struct Reader_JSON_Base_Info {
        std::shared_ptr<const File_Reader> fr;
        nlohmann::json info;
    };

    struct Entity_JSON_Info : Reader_JSON_Base_Info {
        std::shared_ptr<World> world;

        Entity_JSON_Info(
            const std::shared_ptr<const File_Reader> & fr,
            const nlohmann::json &entity,
            const std::shared_ptr<World> & world) : Reader_JSON_Base_Info(fr, entity), world(world){}
    };
}

#endif //PACMAN_READER_JSON_INFO_H