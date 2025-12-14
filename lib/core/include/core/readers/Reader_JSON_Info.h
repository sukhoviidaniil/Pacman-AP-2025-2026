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

#include "core/info/File_Reader_Additional_Structures.h"
#include <json.hpp>

namespace core {
    class File_Reader;

    struct Reader_Base_Info_JSON : Reader_Base_Info {
        nlohmann::json data_;
        Reader_Base_Info_JSON(
            const std::shared_ptr<const File_Reader> & fr,
            nlohmann::json::const_reference json
            ):
        Reader_Base_Info(fr), data_(json)  {
        }
    };

    struct Stage_Info_JSON : Reader_Stage_Info {
        nlohmann::json data_;

        Stage_Info_JSON(
            const std::shared_ptr<const File_Reader> & fr,
            const std::shared_ptr<Stage> & stage,
            nlohmann::json::const_reference json
        ) : Reader_Stage_Info(fr, stage), data_(json){}
    };
}

#endif //PACMAN_READER_JSON_INFO_H