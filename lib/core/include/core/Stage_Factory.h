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
#include "Controller.h"
#include "model/Model.h"
#include "view/View.h"

namespace core {
    class Stage_Factory {
        public:
        explicit Stage_Factory(const std::vector<infra::ast::Model> &models);

        void add_Score(const std::shared_ptr<Score> &score);

        void add_View(const std::shared_ptr<view::View>& view);
        void add_Controller(const std::shared_ptr<Controller>& controller);

        protected:

        [[nodiscard]] std::shared_ptr<model::Model> get_model() const;
        void make_new_model();

        private:
        std::shared_ptr<model::Model> current_model_ = nullptr;
        std::vector<infra::ast::Model> models_;
        std::shared_ptr<Score> score_ = nullptr;
        std::shared_ptr<view::View> view_ = nullptr;
        std::shared_ptr<core::Controller> controller_ = nullptr;
    };
}

#endif //PACMAN_STAGE_FACTORY_H