/***************************************************************
 * Project:       Pacman
 * File:          Reader_JSON.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-26
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

#ifndef PACMAN_READER_JSON_H
#define PACMAN_READER_JSON_H

#include "json.hpp"
#include "infra/Reader.h"

namespace infra {

    class Reader_JSON  : public Reader {
    public:
        Reader_JSON();
        ~Reader_JSON() override;


    protected:
        template<class T>
        static T get_checked(
            const T &default_value,
            const nlohmann::json &j,
            const std::string &key,
            const std::string &path,
            const std::string &object = "ROOT"
            );

        template<class T>
        static T get_checked(
            const nlohmann::json &j,
            const std::string &key,
            const std::string &path,
            const std::string &object = "ROOT"
            );

        static void invalid_parameter(const std::string &path, const std::string &name, const std::string &object);
        static nlohmann::json get_json_data(
            const std::string &filename
            );
    };
}

#endif //PACMAN_READER_JSON_H