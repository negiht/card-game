#pragma once

#include <mulan/game_state.hpp>
#include <mulan/object.hpp>

#include <cstddef>

struct selection_phase_view : public object
{
    virtual ~selection_phase_view() {}
    virtual bool is_card_targeted(bool top, size_t index) const = 0;
    virtual bool is_card_selected(bool top, size_t index) const = 0;
    virtual void draw_card(bool top, size_t index, bool active_turn, bool preview, bool cross, card const &) = 0;
};
