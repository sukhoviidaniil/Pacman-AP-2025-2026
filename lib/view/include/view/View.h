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


#include "infra/event/Observer.h"
#include "infra/ast/view/ViewVisitor.h"
#include "infra/presentation/render/RenderFrame.h"

namespace view {
    class View : public infra::event::Observer, public infra::ast::SpriteVisitor, public infra::ui::RenderVisitor{
    public:
        explicit View(std::string name);
        ~View() override;
        virtual void render(const infra::ui::RenderFrame& graph) = 0;
        virtual void track_local(const std::shared_ptr<infra::event::Event_Bus>& bus) = 0;
        virtual void track_global(const std::shared_ptr<infra::event::Event_Bus>& bus) = 0;
    protected:
        std::string name_ = "None";
    };
}

#endif //PACMAN_VIEW_H