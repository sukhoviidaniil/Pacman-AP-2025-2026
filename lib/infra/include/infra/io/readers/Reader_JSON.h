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

#include "infra/io/Reader.h"
#include "json.hpp"

namespace infra::io {
    class Reader_JSON  : public Reader {
    public:
        Reader_JSON();
        ~Reader_JSON() override;

        [[nodiscard]] ast::Sprite read_Sprite(const std::string& filename) const override;
        [[nodiscard]] ast::ComplexSprite read_Sprits_Group(const std::string& filename) const override;

        static ast::View read_View(
            nlohmann::json data,
            const std::shared_ptr<const File_Reader> &fr,
            const std::string &filename,
            const std::string &object
            );

        [[nodiscard]] ast::View read_View(const std::string &filename, const std::shared_ptr<const File_Reader>& fr) const override;
        [[nodiscard]] ast::Model read_Model(const std::string& path) const override;
        [[nodiscard]] ast::Application read_Application(const std::string& path, const std::shared_ptr<const File_Reader>& fr) const override;
    };
}

#endif //PACMAN_READER_JSON_H