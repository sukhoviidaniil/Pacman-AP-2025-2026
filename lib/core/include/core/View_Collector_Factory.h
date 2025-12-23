/***************************************************************
 * Project:       Pacman
 * File:          View_Collector_Factory.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-20
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
#ifndef PACMAN_VIEW_COLLECTOR_FACTORY_H
#define PACMAN_VIEW_COLLECTOR_FACTORY_H

#include "core/event_collector/Event_Collector.h"
#include "view/View.h"
#include "infra/ast/Event_Collector.h"

namespace core {
    class View_Collector_Factory{
    public:
        View_Collector_Factory();
        std::shared_ptr<view::View> make_View(const infra::ast::View &info, const std::string &path);

        std::unique_ptr<Event_Collector> make_Event_Collector(const infra::ast::Event_Collector &info);
    private:

        std::unique_ptr<Event_Collector> event_collector_;

        static void Register(
            std::unordered_map<
                std::string,
                std::shared_ptr<view::View> (View_Collector_Factory::*)(const infra::ast::View&, const std::string&)
            > &outMap
        );

        std::shared_ptr<view::View> SFML_View(const infra::ast::View& info, const std::string& path);
    };
}


#endif //PACMAN_VIEW_COLLECTOR_FACTORY_H