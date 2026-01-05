/***************************************************************
 * Project:       Pacman
 * File:          Reader_JSON.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-11-26
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


#include "infra/io/File_Reader.h"
#include "infra/io/readers/from_JSON.h"
#include "infra/io/readers/Reader_JSON.h"


namespace infra::io {
    Reader_JSON::Reader_JSON() = default;

    Reader_JSON::~Reader_JSON() = default;

    ast::Sprite Reader_JSON::read_Sprite(const std::string &filename) const {
        nlohmann::json data = get_json_data(filename);
        auto sprite = get_checked<ast::Sprite>(data);
        return sprite;
    }

    ast::SpriteList Reader_JSON::read_SpriteList(const std::string &filename) const {
        nlohmann::json data = get_json_data(filename);
        auto sg = get_checked<ast::SpriteList>(data);
        return sg;
    }

    ast::ComplexSprite Reader_JSON::read_Sprits_Group(const std::string &filename) const {
        nlohmann::json data = get_json_data(filename);
        auto sg = get_checked<ast::ComplexSprite>(data);
        return sg;
    }

    ast::View Reader_JSON::read_View(
        const std::string &filename,
        const std::shared_ptr<const File_Reader> &fr) const {
        const nlohmann::json data = get_json_data(filename);
        return read_View(data, fr);
    }

    ast::Model Reader_JSON::read_Model(const std::string& path) const {
        const nlohmann::json data = get_json_data(path);
        return get_checked<ast::Model>(data);
    }

    ast::ScoreSetup Reader_JSON::read_ScoreSetup(const std::string &filename) const {
        nlohmann::json j = get_json_data(filename);
        return get_checked<ast::ScoreSetup>(j);
    }

    ast::ScoreBord Reader_JSON::read_ScoreBord(const std::string &filename, const std::string formal_path) const {
        nlohmann::json j = get_json_data(filename);
        auto bord = io::get_checked<ast::ScoreBord>(j);
        bord.file = formal_path;
        return bord;
    }

    ast::Game Reader_JSON::read_Game(
        const std::string &path,
        const std::shared_ptr<const File_Reader> &fr
        ) const {
        nlohmann::json data = get_json_data(path);
        ast::Game app;
        const std::string view_name = "View";
        if (data.contains(view_name)) {
            if (data[view_name].is_string()) {
                const auto view = get_checked<std::string>(data, view_name);
                app.view = fr->read_View(view);
            }else if (data[view_name].is_structured()) {
                app.view = read_View(data[view_name], fr);
            }else {
                std::string err = "The view is neither a string nor an structured, configuration reading error.";
                LOG(err);
                throw std::invalid_argument(err);
            }
        }

        std::string m = "Models";
        if (data.contains(m) && data[m].is_array()) {
            for (const auto& model_data: data[m]) {
                if (model_data.is_object()) {
                    auto model = get_checked<ast::Model>(model_data);
                    app.models.push_back(model);
                    continue;
                }
                if (model_data.is_string()) {
                    auto model_file = get_checked<std::string>(model_data);
                    ast::Model model = fr->read_Model(model_file);
                    app.models.push_back(model);
                    continue;
                }
                throw std::invalid_argument("The model is neither a string nor an object, configuration reading error");
            }
        }

        std::string bors = "ScoreBord";
        if (data.contains(bors)) {
            if (data[bors].is_string()) {
                auto file = get_checked<std::string>(data[bors]);
                app.score_bord = fr->read_ScoreBord(file);

            }
            if (data[bors].is_structured()) {
                app.score_bord = get_checked<ast::ScoreBord>(data[bors]);
            }
        }

        return app;
    }

    void Reader_JSON::save_ScoreBord(const ast::ScoreBord& bord, const std::string formal_path) const {
        nlohmann::json j;

        // --- Meta ---
        j["file"] = bord.file;
        j["bord_size"] = bord.bord_size;

        // --- Score setup ---
        j["score_setup"] = {
            // Base
            {"lives_remaining", bord.score_setup.lives_remaining},
            {"level", bord.score_setup.level},
            {"points_score", bord.score_setup.points_score},

            // Coins
            {"time_since_the_last_coin_collection",
                bord.score_setup.time_since_the_last_coin_collection},
            {"coin_award_amount", bord.score_setup.coin_award_amount},
            {"coin_max_award_level", bord.score_setup.coin_max_award_level},
            {"coin_award_level", bord.score_setup.coin_award_level},
            {"coin_RR_Time_until_reduction",
                bord.score_setup.coin_RR_Time_until_reduction},
            {"coin_RR_Time_between_reductions",
                bord.score_setup.coin_RR_Time_between_reductions},

            // Ghosts
            {"time_since_the_last_ghost_collection",
                bord.score_setup.time_since_the_last_ghost_collection},
            {"ghost_award_amount", bord.score_setup.ghost_award_amount},
            {"ghost_max_award_level", bord.score_setup.ghost_max_award_level},
            {"ghost_award_level", bord.score_setup.ghost_award_level},
            {"ghost_RR_Time_until_reset",
                bord.score_setup.ghost_RR_Time_until_reset}
        };

        // --- Scores ---
        j["scores"] = nlohmann::json::array();
        for (const auto& s : bord.scores) {
            j["scores"].push_back({
                {"id", s.id},
                {"lives_remaining", s.lives_remaining},
                {"level", s.level},
                {"points_score", s.points_score}
            });
        }

        std::ofstream out(formal_path);
        out << j.dump(4);
    }
}
