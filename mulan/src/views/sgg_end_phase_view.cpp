#include <mulan/views/sgg_end_phase_view.hpp>

#include <sgg/graphics.h>
#include <sgg/audio.h>

#include <mulan/defines.hpp>
#include <mulan/sgg_draw_utils.hpp>

sgg_end_phase_view::sgg_end_phase_view(
    bool winner,
    resource_registry const & registry
)
    : winner_{winner}
    , registry_{registry}
    , start_collider_{CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10}
    , exit_collider_{CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 1.1 * CANVAS_HEIGHT / 10, CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10}
    , new_game_selection_helper_{start_collider_}
    , exit_selection_helper_{exit_collider_}
{
}

void sgg_end_phase_view::draw()
{
    sgg_draw_utils::draw_background(registry_.get_loading_background());

    graphics::Brush br;

    float msg_text_x_offset = - CANVAS_WIDTH / 4.5;
    float replay_text_x_offset = - CANVAS_WIDTH / 23;
    float exit_text_x_offset = - CANVAS_WIDTH / 32;
    float button_text_y_offset = + CANVAS_WIDTH / 100;

    graphics::setFont(registry_.get_loading_button_font());


    SETCOLOR(br.outline_color, 1.0f, 1.0f, 1.0f);
    br.outline_opacity = 1.0f;

    auto msg1 = "Congratulations!    Top     wins!";
    auto msg2 = "Congratulations!   Bottom   wins!";

    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    graphics::drawText(CANVAS_WIDTH / 2 + msg_text_x_offset, CANVAS_HEIGHT / 2 - 5 * button_text_y_offset, 1, winner_ ? msg1 : msg2, br);

    if (new_game_is_targeted_)
    {
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2,  CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10, br);
        SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
        graphics::drawText(CANVAS_WIDTH / 2 + replay_text_x_offset, CANVAS_HEIGHT / 2 + button_text_y_offset, 1, "replay", br);
    }
    else
    {
        SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2,  CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10, br);
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        graphics::drawText(CANVAS_WIDTH / 2 + replay_text_x_offset, CANVAS_HEIGHT / 2 + button_text_y_offset, 1, "replay", br);
    }

    if (exit_is_targeted_)
    {
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 0.11 * CANVAS_HEIGHT ,  CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10, br);
        SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
        graphics::drawText(CANVAS_WIDTH / 2 + exit_text_x_offset, CANVAS_HEIGHT / 2 + 0.11 * CANVAS_HEIGHT + button_text_y_offset, 1, "exit", br);
    }
    else
    {
        SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 0.11 * CANVAS_HEIGHT,  CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10, br);
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        graphics::drawText(CANVAS_WIDTH / 2 + exit_text_x_offset, CANVAS_HEIGHT / 2 + 0.11 * CANVAS_HEIGHT + button_text_y_offset, 1, "exit", br);
    }
}

void sgg_end_phase_view::update(float ms)
{
    new_game_selection_helper_.update();
    exit_selection_helper_.update();

    new_game_is_targeted_ = new_game_selection_helper_.get_state() == sgg_selection_helper::state::TARGETED  ||
                            new_game_selection_helper_.get_state() == sgg_selection_helper::state::PRESSED;

    exit_is_targeted_ = exit_selection_helper_.get_state() == sgg_selection_helper::state::TARGETED  ||
                        exit_selection_helper_.get_state() == sgg_selection_helper::state::PRESSED;

    bool new_game_clicked = new_game_selection_helper_.get_state() == sgg_selection_helper::state::SELECTED;
    bool exit_clicked = exit_selection_helper_.get_state() == sgg_selection_helper::state::SELECTED;

    if (new_game_clicked)
    {
        playSound(registry_.get_battle_start_sound(), 128);
        new_game_pressed_ = true;
    }

    if (exit_clicked)
    {
        exit_pressed_ = true;
    }
}

auto sgg_end_phase_view::new_game_pressed() const -> bool
{
    return new_game_pressed_;
}

auto sgg_end_phase_view::exit_pressed() const -> bool
{
    return exit_pressed_;
}
