#include <mulan/sgg_selection_helper.hpp>
#include <mulan/defines.hpp>
#include <mulan/sgg_draw_utils.hpp>

#include <sgg/graphics.h>

sgg_selection_helper::sgg_selection_helper(square_collider const & collider)
    : collider_{collider}
{
    
}

void sgg_selection_helper::update()
{
    graphics::MouseState state;
    graphics::getMouseState(state);

    if (collider_.in_bounds(
            graphics::windowToCanvasX(state.cur_pos_x),
            graphics::windowToCanvasY(state.cur_pos_y)))
    {
        switch (state_)
        {
        case state::UNSELECTED:
            if (!state.button_left_down)
                state_ = state::TARGETED;
            break;
        case state::TARGETED:
            if (state.button_left_down)
                state_ = state::PRESSED;
            break;
        case state::PRESSED:
            if (!state.button_left_down)
                state_ = state::SELECTED;
            break;
        case state::SELECTED:
            if (!state.button_left_down)
            break;
        }
    }
    else
    {
        state_ = state::UNSELECTED;
    }
}
