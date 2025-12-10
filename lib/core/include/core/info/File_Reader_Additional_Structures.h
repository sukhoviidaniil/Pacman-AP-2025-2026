/***************************************************************
 * Project:       Pacman
 * File:          File_Reader_Additional_Structures .h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-10
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
#ifndef PACMAN_FILE_READER_ADDITIONAL_STRUCTURES_H
#define PACMAN_FILE_READER_ADDITIONAL_STRUCTURES_H
#include <memory>

namespace Core {

    class File_Reader;

    struct Reader_Base_Info {
        std::shared_ptr<const File_Reader> fr_;

        explicit Reader_Base_Info(const std::shared_ptr<const File_Reader> &fr)
            : fr_(fr) {
        }
    };

    struct Reader_Stage_Info : Reader_Base_Info {
        std::shared_ptr<Stage> stage_;

        Reader_Stage_Info(
            const std::shared_ptr<const File_Reader> &fr,
            const std::shared_ptr<Stage> &stage)
            : Reader_Base_Info(fr), stage_(stage) {
        }
    };
}

#endif //PACMAN_FILE_READER_ADDITIONAL_STRUCTURES_H