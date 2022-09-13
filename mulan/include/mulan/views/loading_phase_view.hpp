#pragma once

#include <mulan/object.hpp>

struct loading_phase_view : public object
{
    virtual ~loading_phase_view() {}

    virtual auto start_new_game_pressed() const -> bool = 0;
};
