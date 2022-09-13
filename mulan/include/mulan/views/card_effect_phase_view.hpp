#pragma once

#include <mulan/game_state.hpp>
#include <mulan/object.hpp>

#include <cstddef>

struct card_effect_phase_view : public object
{
    virtual ~card_effect_phase_view() {}

    virtual bool is_finished() const = 0;
    virtual void draw_card(bool top, size_t index, bool preview, card const &) = 0;
};
