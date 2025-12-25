/***************************************************************
 * Project:       Pacman
 * File:          Reader.h
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
#ifndef PACMAN_READER_H
#define PACMAN_READER_H
#include <memory>

#include "infra/ast/view/View.h"
#include "infra/ast/Application.h"

namespace infra::io {

    class File_Reader;

    class Reader {
        public:
        virtual ~Reader() = default;
        [[nodiscard]] virtual ast::Sprite read_Sprite(const std::string& path) const = 0;
        [[nodiscard]] virtual ast::ComplexSprite read_Sprits_Group(const std::string& path) const = 0;
        [[nodiscard]] virtual ast::View read_View(const std::string& path, const std::shared_ptr<const File_Reader>& fr) const = 0;
        [[nodiscard]] virtual ast::Model read_Model(const std::string& path) const = 0;
        [[nodiscard]] virtual ast::Application read_Application(const std::string& path, const std::shared_ptr<const File_Reader>& fr) const = 0;
    };
}

#endif //PACMAN_READER_H