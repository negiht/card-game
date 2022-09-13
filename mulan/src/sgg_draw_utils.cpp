#include <mulan/sgg_draw_utils.hpp>

#include <mulan/defines.hpp>
#include <sgg/graphics.h>

#include <sstream>

namespace sgg_draw_utils {

void draw_background(std::string const & background_path)
{
    graphics::Brush br;
    SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
    graphics::setWindowBackground(br);

    br.texture = background_path;
    br.outline_opacity = 0.0f;
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

void draw_card(
    bool top, size_t index, 
    bool active_turn, bool preview, bool cross, 
    resource_registry const & registry,
    card const & card)
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

    SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
    graphics::drawRect(x, y, width, height, br);
    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    br.texture = registry.get_card_image(card.image_handle());
    graphics::drawRect(x, y, width, height, br);

    br.texture = registry.get_card_font();;
    SETCOLOR(br.fill_color, 0.0f, 0.0f, 1.0f);
    graphics::drawText(x-width/3, y-height/4, 1.0f, std::to_string(card.damage()), br);
    SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f);
    graphics::drawText(x, y+height/3, 1.0f, std::to_string(card.health()), br);

    if (cross)
    {
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        br.texture = registry.get_card_target();
        graphics::drawRect(x, y, width/1.5, width/1.5, br);
    }

}

}
