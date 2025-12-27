/***************************************************************
 * Project:       Pacman
 * File:          ScoreBord.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-26
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
#ifndef PACMAN_RI_SCOREBORD_H
#define PACMAN_RI_SCOREBORD_H

#include "Text.h"
#include "view/presentation/render/RI_Label.h"

namespace view::ui {
    class ScoreBord : public Text {
        public:
        ScoreBord() = default;

        explicit ScoreBord(const int fontSize) : Text(fontSize) {

        }

        void append_render_items(RenderFrame& frame, const ViewContext& ctx) const override {
            if (!visible) return;
            if (!ctx.score_bord) return;

            const auto& bord = ctx.score_bord->get();
            const auto& scores = bord.all_scores();

            float line_height = static_cast<float>(fontSize) * 1.2f;
            float max_height = result.rect.height;
            auto max_lines = static_cast<std::size_t>(max_height / line_height);

            infra::ui::Rect line_rect = result.rect;
            line_rect.height = line_height;

            std::size_t lines = std::min(scores.size(), max_lines);

            for (std::size_t i = 0; i < lines; ++i) {
                const auto& s = scores[i];

                std::unique_ptr<RI_Label> item = std::make_unique<RI_Label>();
                item->text =
                    std::to_string(i + 1) + ". " +
                    std::to_string(s.points_score) +
                    "  Level:" + std::to_string(s.level);
                item->font  = font;
                item->color = color;
                item->size  = static_cast<int>(fontSize);
                item->rect  = line_rect;

                frame.constant_items.push_back(std::move(item));

                line_rect.y += line_height;
            }
        }
    };
}


#endif //PACMAN_RI_SCOREBORD_H