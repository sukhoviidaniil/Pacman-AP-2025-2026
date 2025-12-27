/***************************************************************
 * Project:       Pacman
 * File:          UIElement.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-19
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
#ifndef PACMAN_UIELEMENT_H
#define PACMAN_UIELEMENT_H

#include <memory>

#include "infra/math/Vector2.h"
#include "infra/presentation/external/Size.h"
#include "view/ViewContext.h"
#include "view/presentation/layout_engine/LayoutResult.h"
#include "view/presentation/render/RenderFrame.h"

namespace view::ui {
    /**
     * @brief Base class for all UI layout elements.
     *
     * Represents a node in the layout tree. Each UIElement participates
     * in the measure and layout passes and may contain child elements.
     * The class provides default size resolution and recursive layout
     * propagation.
     */
    class UIElement {
    public:
        /// @brief Virtual destructor.
        virtual ~UIElement() = default;

        /**
         * @brief Adds a child element to this node.
         *
         * Ownership is shared to allow flexible tree composition.
         */
        void add(std::shared_ptr<UIElement> child) {
            children.push_back(std::move(child));
        }

        // ===== Layout API =====

        /**
         * @brief Measures the desired size of the element.
         *
         * Called during the measure pass with the available space
         * provided by the parent. The default implementation resolves
         * the size from width/height constraints.
         *
         * @param available Available space for this element.
         * @return Desired size of the element.
         */
        virtual infra::math::Vector2 measure(const infra::math::Vector2& available) {
            infra::math::Vector2 total_size {0, 0};

            for (auto& child : children) {
                auto child_size = child->measure(available);
                total_size.y += child_size.y + child->margin.y;
                total_size.x = std::max(total_size.x, child_size.x + child->margin.x);
            }

            total_size.x += padding.x * 2;
            total_size.y += padding.y * 2;

            total_size.x = std::clamp(total_size.x, min_size.x, max_size.x);
            total_size.y = std::clamp(total_size.y, min_size.y, max_size.y);

            return total_size;
        }

        /**
         * @brief Assigns the final layout rectangle to the element.
         *
         * Stores the computed rectangle and propagates the same layout
         * to all child elements by default.
         *
         * @param r Final rectangle assigned by the layout engine.
         */
        virtual void layout(const infra::ui::Rect r) {
            result.rect = r;

            float y_offset = r.y + padding.y;

            for (auto& child : children) {
                infra::math::Vector2 child_size = child->resolve_size({r.width - padding.x*2, r.height - padding.y*2});

                infra::ui::Rect child_rect {
                    r.x + padding.x + child->margin.x,
                    y_offset + child->margin.y,
                    child_size.x,
                    child_size.y
                };

                child->layout(child_rect);

                y_offset += child_size.y + child->margin.y;
            }
        }

        virtual void append_render_items(RenderFrame& frame, const ViewContext& ctx) const {
            for (const auto& c : children) {
                c->append_render_items(frame, ctx);
            }
        }


        // ===== Configuration =====
        infra::ui::Size width  = infra::ui::Size::auto_(); ///< Width specification
        infra::ui::Size height = infra::ui::Size::auto_(); ///< Height specification

        infra::math::Vector2 min_size {0, 0};         ///< Minimum allowed size
        infra::math::Vector2 max_size {1e9f, 1e9f};   ///< Maximum allowed size

        infra::math::Vector2 margin  {0, 0}; ///< External spacing
        infra::math::Vector2 padding {0, 0}; ///< Internal spacing

        float flex = 0.f; ///< Flex grow factor (0 = fixed, >0 = expandable)

        bool visible = true; ///< Visibility flag

        LayoutResult result{}; ///< Result of the layout pass

        /// @brief Child elements in the layout tree.
        std::vector<std::shared_ptr<UIElement>> children;
    protected:

        /**
         * @brief Resolves the final size based on available space.
         *
         * Converts width and height Size specifications into concrete
         * values and clamps them to the configured min/max constraints.
         *
         * @param available Available space from the parent.
         * @return Resolved size.
         */
        [[nodiscard]] infra::math::Vector2 resolve_size(const infra::math::Vector2 &available) const {
            infra::math::Vector2 out;

            auto resolve = [&](infra::ui::Size s, float avail) {
                if (s.type == infra::ui::Size::Type::Pixel)   return s.value;
                if (s.type == infra::ui::Size::Type::Percent) return avail * s.value;
                return avail; // Auto
            };

            out.x = resolve(width,  available.x);
            out.y = resolve(height, available.y);

            out.x = std::clamp(out.x, min_size.x, max_size.x);
            out.y = std::clamp(out.y, min_size.y, max_size.y);

            return out;
        }
    };
}

#endif //PACMAN_UIELEMENT_H