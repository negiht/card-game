#include <mulan/sgg_drawer.hpp>

#include <mulan/defines.hpp>
#include <sgg/graphics.h>

sgg_drawer::sgg_drawer(
    std::string const & button_font,
    std::string const & background,
    std::string const & card_font,
    std::string const & card_target)
    : button_font_{button_font}
    , background_{background}
    , card_font_{card_font}
    , card_target_{card_target}
{
}

void sgg_drawer::draw_background()
{
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    br.texture = background_;
    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}


auto card_center(bool top, size_t index) -> std::pair<float, float> 
{
    return  {(index * 1/6.f + 1/12.f) * CANVAS_WIDTH, (!top * 1/2.f + 1/4.f) * CANVAS_HEIGHT};
}

auto card_size() -> std::pair<float, float> {
    return {1/8.f * CANVAS_WIDTH, 1/3.f * CANVAS_HEIGHT};
}

void sgg_drawer::draw_card(bool top, size_t index, bool active_turn, bool preview, bool cross, card const & card)
{
    graphics::Brush br;
    br.outline_opacity = active_turn ? 1.f : 0.f;
    br.outline_width = active_turn ? 2.f : 0.f;

    auto [width, height] = sgg_draw_utils::card_size();
    auto [x, y] = sgg_draw_utils::card_center(top, index);

    if (preview)
    {
        width *= 1.2;
        height *= 1.2;
    }

    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    br.texture = card.image_path();
    graphics::drawRect(x, y, width, height, br);

    br.texture = font;
    SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f);
    graphics::drawText(x-width/3, y-height/4, 1.0f, std::to_string(card.health()), br);
    SETCOLOR(br.fill_color, 0.0f, 0.0f, 1.0f);
    graphics::drawText(x, y+height/3, 1.0f, std::to_string(card.damage()), br);

    if (cross)
    {
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        br.texture = target_path;
        graphics::drawRect(x, y, width/2, height/2, br);
    }
}
