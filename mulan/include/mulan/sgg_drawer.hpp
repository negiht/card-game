#pragma once

#include <string>

#include <mulan/game_state.hpp>

class sgg_drawer
{
    sgg_drawer(
        std::string const & button_font,
        std::string const & background,
        std::string const & card_font,
        std::string const & card_target);

    void draw_background();

    void draw_card(bool top, size_t index, bool active_turn, bool preview, bool cross, card const & card);

private:
    std::string button_font_;
    std::string background_;
    std::string card_font_;
    std::string card_target_;

};
