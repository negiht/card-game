#pragma once

#include <mulan/object.hpp>

struct end_phase_view : public object
{
    virtual ~end_phase_view() {}

    virtual auto new_game_pressed() const -> bool = 0;
    virtual auto exit_pressed() const -> bool = 0;
};
