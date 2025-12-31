/***************************************************************
 * Project:       Pacman
 * File:          Stage.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-19
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

#include "core/Stage.h"

namespace core::stg {
    Stage::Stage(const std::shared_ptr<infra::event::Event_Bus> &globalBus) : g_eventbus(globalBus){
        l_eventbus = std::make_unique<infra::event::Event_Bus>();
    }

    void Stage::checkIn() {
    }

    void stg::Stage::dispatch( infra::event::Event_Store& event_store) {
        while (!event_store.empty()) {
            std::unique_ptr<infra::event::EventConcept> e_concept = event_store.pop_concept();
            if (
                has(e_concept->mask(), infra::event::EventMask::Window) ||
                has(e_concept->mask(), infra::event::EventMask::Game)
                ) {
                g_eventbus->emit(*e_concept);
            }


            /*
            if (
                has(e_concept->mask(), infra::event::EventMask::Game)
                ) {
                l_eventbus->emit(*e_concept);
            }
            */
        }
    }
}
