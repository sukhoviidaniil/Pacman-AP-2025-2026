/***************************************************************
 * Project:       Pacman
 * File:          Animation.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-22
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
#ifndef PACMAN_ANIMATION_H
#define PACMAN_ANIMATION_H
#include <string>
#include <vector>

namespace infra::ui {
    struct Animation {
        int frames_size_;
        std::vector<std::string> frames_;
        float frame_duration_ = 0.1f;
        float elapsed_ = 0.f;
        bool loop_ = true;

        Animation() = default;
        explicit Animation(const Animation& other, const float elapsed) :
            frames_size_(other.frames_size_),
            frames_(other.frames_),
            frame_duration_(other.frame_duration_),
            elapsed_(elapsed),
            loop_(other.loop_)
        {
        }

        explicit Animation(const int frames_size, const float frame_duration, const float elapsed
            ) : frames_size_(frames_size), frame_duration_(frame_duration), elapsed_(elapsed) {
        }

        [[nodiscard]] size_t index() const {
            return static_cast<size_t>(static_cast<int>(elapsed_ / frame_duration_) % frames_size_);
        }

        [[nodiscard]] std::string current_frame() const {
            return frames_[index()];
        }
    };
}

#endif //PACMAN_ANIMATION_H