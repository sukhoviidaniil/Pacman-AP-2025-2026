/***************************************************************
 * Project:       Pacman
 * File:          View_Collector_Factory.cpp
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

#include "core/View_Collector_Factory.h"

#include "core/event_collector/SFML_Event_Collector.h"
#include "../../infra/include/infra/ast/view/View.h"
#include "view/sfml/SFML_View.h"

namespace core {
    View_Collector_Factory::View_Collector_Factory() = default;

    std::shared_ptr<view::View> View_Collector_Factory::make_View(const infra::ast::View &info, const std::string &path) {
        std::unordered_map<std::string, std::shared_ptr<view::View>(View_Collector_Factory::*)(const infra::ast::View&, const std::string&)> map;
        Register(map);
        const std::string type = info.type;
        auto it = map.find(type);
        if (it != map.end()) {
            return (this->*(it->second))(info, path);
        }
        throw std::runtime_error("Unknown View type: " + type);
    }

    std::unique_ptr<Event_Collector> View_Collector_Factory::make_Event_Collector(const infra::ast::Event_Collector &info) {
        if (event_collector_ != nullptr) {
            return std::move(event_collector_);
        }
        /* If there is no event_collector_ at this point, then you need to have a system that will create it.
         * Since the implementation assumes that SFML will be used, this means that the controller was already created when the View was created.
         * And since we cannot assume the data required to create another controller, all we can do is throw an error - it is not possible to create a controller.
         */
        throw std::runtime_error("Event collector not initialized");
    }

    void View_Collector_Factory::Register(
        std::unordered_map<std::string, std::shared_ptr<view::View>(View_Collector_Factory::*)(const infra::ast::View &, const std::string &)> &
        outMap) {
        outMap["SFML"] = &View_Collector_Factory::SFML_View;
    }

    std::shared_ptr<view::View> View_Collector_Factory::
    SFML_View(const infra::ast::View &info, const std::string &path) {
        auto view = std::make_shared<view::SFML_View>(info, path);
        event_collector_ = std::make_unique<SFML_Event_Collector>(*view);
        return view;
    }
}
