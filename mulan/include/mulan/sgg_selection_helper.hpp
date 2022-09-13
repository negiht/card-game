#pragma once

#include <cstddef>
#include <mulan/square_collider.hpp>
#include <array>

class sgg_selection_helper
{
public:
    sgg_selection_helper(square_collider const &);

    enum class state
    {
        UNSELECTED,
        TARGETED,
        PRESSED,
        SELECTED,
    };

    auto get_state() const -> state
    {
        return state_;
    }

    void update();

private:
    state state_{};
    square_collider const & collider_;
};

