/***************************************************************
 * Project:       Pacman
 * File:          View.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-06
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
#ifndef PACMAN_VIEW_H
#define PACMAN_VIEW_H

#include <memory>
#include <string>

#include "core/Stage.h"
#include "infra/event/Observer.h"
#include "infra/ast/Visitor.h"

namespace view {
    class View : public infra::event::Observer, public infra::ast::View_Visitor{
    public:
        explicit View(const std::string& name);
        ~View() override;
        virtual void render(const infra::ast::Scene_Graph& graph) const = 0;
        virtual void track_local(infra::event::Event_Bus& stage) = 0;
        virtual void track_global(infra::event::Event_Bus& stage) = 0;
    protected:
        std::string name_ = "None";
    };
}

#endif //PACMAN_VIEW_H