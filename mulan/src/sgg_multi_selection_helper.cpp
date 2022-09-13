#include <mulan/sgg_multi_selection_helper.hpp>
#include <mulan/sgg_draw_utils.hpp>

sgg_multi_selection_helper::sgg_multi_selection_helper()
    : helpers_{{
        {{ colliders_[0][0], colliders_[0][1], colliders_[0][2], colliders_[0][3], colliders_[0][4], colliders_[0][5] }},
        {{ colliders_[1][0], colliders_[1][1], colliders_[1][2], colliders_[1][3], colliders_[1][4], colliders_[1][5] }},
    }}
{
    auto [width, height] = sgg_draw_utils::card_size();

    for (size_t i = 0; i != 2; ++i)
    {
        for (size_t j = 0; j != 6; ++j)
        {
            auto [x,y] = sgg_draw_utils::card_center(i, j);

            colliders_[i][j].setup(x, y, width, height);
        }
    }
}

void sgg_multi_selection_helper::update()
{
    for (size_t i = 0; i != 2; ++i)
    {
        for (size_t j = 0; j != 6; ++j)
        {
            auto [x,y] = sgg_draw_utils::card_center(i, j);

            helpers_[i][j].update();
        }
    }
}

auto sgg_multi_selection_helper::is_card_targeted(bool top, size_t index) const -> bool
{
    return helpers_[top][index].get_state() == sgg_selection_helper::state::TARGETED ||
           helpers_[top][index].get_state() == sgg_selection_helper::state::PRESSED;
}

auto sgg_multi_selection_helper::is_card_selected(bool top, size_t index) const -> bool
{
    return helpers_[top][index].get_state() == sgg_selection_helper::state::SELECTED;
}

