#pragma once

#include <mulan/sgg_selection_helper.hpp>

class sgg_multi_selection_helper
{
public:
    sgg_multi_selection_helper();

    void update();
    auto is_card_targeted(bool top, size_t index) const -> bool;
    auto is_card_selected(bool top, size_t index) const -> bool;

private:
    std::array<std::array<square_collider, 6>,2> colliders_;
    std::array<std::array<sgg_selection_helper, 6>,2> helpers_;
};
