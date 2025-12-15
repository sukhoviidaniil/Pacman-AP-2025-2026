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


namespace infra {

    class File_Reader;

    struct Reader_Info {
        const std::shared_ptr<const File_Reader>& fr;
        const std::string& path;
    };

    class Reader {
        public:
        virtual ~Reader() = default;
        [[nodiscard]] virtual ast::Sprite read_Sprite(const std::string& filename) const = 0;
        [[nodiscard]] virtual ast::Sprits_Group read_Sprits_Group(const std::string& filename) const = 0;
        [[nodiscard]] virtual ast::View_Sprites read_View(const std::string &filename) const = 0;
    };
}

#endif //PACMAN_READER_H