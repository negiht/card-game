#include <mulan/views/sgg_loading_phase_view.hpp>

#include <sgg/graphics.h>
#include <sgg/audio.h>

#include <mulan/defines.hpp>
#include <mulan/sgg_draw_utils.hpp>

sgg_loading_phase_view::sgg_loading_phase_view(
    resource_registry const & registry
)
    : registry_{registry}
    , collider_{CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10}
    , selection_helper_{collider_}
{
    playMusic(registry_.get_background_music(), 128);
   // playMusic("C:\\Users\\negi_\\OneDrive\\Υπολογιστής\\tmp\\mulan\\assets\\background_music.wav", 128);
}

void sgg_loading_phase_view::draw()
{
    sgg_draw_utils::draw_background(registry_.get_loading_background());    

    graphics::Brush br;
    br.outline_opacity = 1.0f;

    float text_x_offset = - CANVAS_WIDTH / 32;
    float text_y_offset = + CANVAS_WIDTH / 100;

    graphics::setFont(registry_.get_loading_button_font());

    if (is_targeted_)
    {
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2,  CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10, br);
        SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
        graphics::drawText(CANVAS_WIDTH / 2 + text_x_offset, CANVAS_HEIGHT / 2 + text_y_offset, 1, "play", br);
    }
    else
    {
        SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2,  CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10, br);
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        graphics::drawText(CANVAS_WIDTH / 2 + text_x_offset, CANVAS_HEIGHT / 2 + text_y_offset, 1, "play", br);
    }
}

void sgg_loading_phase_view::update(float ms)
{
    selection_helper_.update();
    is_targeted_ = selection_helper_.get_state() == sgg_selection_helper::state::TARGETED  ||
                   selection_helper_.get_state() == sgg_selection_helper::state::PRESSED;


    bool clicked = selection_helper_.get_state() == sgg_selection_helper::state::SELECTED;

    if (clicked)
    {
        playSound(registry_.get_battle_start_sound(), 128);
        new_game_pressed_ = true;
    }
}

auto sgg_loading_phase_view::start_new_game_pressed() const -> bool
{
    return new_game_pressed_;
}
