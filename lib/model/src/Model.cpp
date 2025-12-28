/***************************************************************
 * Project:       Pacman
 * File:          Model.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-18
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

#include "model/Model.h"


namespace model {

    bool Model::all_coins_eaten() const {
        return coins_.empty();
    }


    void Model::run(const float delta) const {
        pacman_->act(delta, wcm_);
    }

    std::shared_ptr<entity::Pacman> Model::get_pacman() const {
        return pacman_;
    }
}
