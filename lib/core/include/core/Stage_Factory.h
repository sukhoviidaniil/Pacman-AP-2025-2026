/***************************************************************
 * Project:       Pacman
 * File:          Stage_Factory.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-16
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
#ifndef PACMAN_STAGE_FACTORY_H
#define PACMAN_STAGE_FACTORY_H
#include "model/Game_Model.h"

namespace core {
    class Stage_Factory {
        public:
        Stage_Factory(const std::vector<infra::ast::Model>& models, const std::shared_ptr<Score>& score);

        protected:

        [[nodiscard]] std::shared_ptr<model::Game_Model> get_model() const;
        void make_new_model();

        private:
        std::shared_ptr<model::Game_Model> current_model_;
        std::vector<infra::ast::Model> models_;
        std::shared_ptr<Score> score_;
    };
}

#endif //PACMAN_STAGE_FACTORY_H