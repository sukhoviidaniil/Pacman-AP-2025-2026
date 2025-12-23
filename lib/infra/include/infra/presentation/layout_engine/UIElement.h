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

#include "infra/presentation/layout_engine/LayoutResult.h"

#include "infra/presentation/RenderFrame.h"
#include "infra/presentation/base/Size.h"

namespace infra::ui {
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
        virtual math::Vector2 measure(const math::Vector2& available) {
            return resolve_size(available);
        }

        /**
         * @brief Assigns the final layout rectangle to the element.
         *
         * Stores the computed rectangle and propagates the same layout
         * to all child elements by default.
         *
         * @param r Final rectangle assigned by the layout engine.
         */
        virtual void layout(const Rect r) {
            result.rect = r;
            for (auto& c : children)
                c->layout(r);
        }

        virtual void append_render_items(std::vector<RenderItem>& out, Space space) const {
            if (!visible) return;

            RenderItem item;
            item.space = space;
            item.rect = result.rect;
            item.sprite = ""; // empty for normal UI, or you can store Label/Button id
            item.status = "";
            item.direction = math::Direction::None;

            out.push_back({space, result.rect, "", math::Direction::None, ""});

            for (const auto& child : children)
                child->append_render_items(out, space);
        }


        // ===== Configuration =====
        Size width  = Size::auto_(); ///< Width specification
        Size height = Size::auto_(); ///< Height specification

        math::Vector2 min_size {0, 0};         ///< Minimum allowed size
        math::Vector2 max_size {1e9f, 1e9f};   ///< Maximum allowed size

        math::Vector2 margin  {0, 0}; ///< External spacing
        math::Vector2 padding {0, 0}; ///< Internal spacing

        float flex = 0.f; ///< Flex grow factor (0 = fixed, >0 = expandable)

        bool visible = true; ///< Visibility flag

        LayoutResult result; ///< Result of the layout pass

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
        math::Vector2 resolve_size(const math::Vector2 &available) const {
            math::Vector2 out;

            auto resolve = [&](Size s, float avail) {
                if (s.type == Size::Type::Pixel)   return s.value;
                if (s.type == Size::Type::Percent) return avail * s.value;
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