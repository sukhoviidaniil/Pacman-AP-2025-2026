//
// Created by Kaede on 2025-10-23.
//


#include <string>
#include "core/File_Reader.h"
#include "core/readers/Reader_JSON.h"

int main() {
    const std::string assets_dir = ASSETS_DIR;
    const std::string texture_dir = assets_dir + "/graphics/";
    const std::string conf_dir = assets_dir + "/config/";
    Core::File_Reader fr(texture_dir, conf_dir);
    const auto reader_json = std::make_shared<Core::Reader_JSON>();
    fr.add_Reader(".json", reader_json);

    return 0;
}
