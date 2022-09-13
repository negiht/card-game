#pragma once

#include <mulan/game_state.hpp>
#include <mulan/resource_registry.hpp>

#include <string>
#include <utility>

namespace sgg_draw_utils {

void draw_background(std::string const & background_path);

auto card_center(bool top, size_t index) -> std::pair<float, float>;

auto card_size() -> std::pair<float, float>;

void draw_card(
    bool top, size_t index, 
    bool active_turn, bool preview, bool cross, 
    resource_registry const & registry, card const & card);

}
