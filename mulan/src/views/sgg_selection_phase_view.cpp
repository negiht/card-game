#include <mulan/views/sgg_selection_phase_view.hpp>
#include <sgg/graphics.h>
#include <sgg/audio.h>
#include <mulan/defines.hpp>
#include <mulan/sgg_draw_utils.hpp>

sgg_selection_phase_view::sgg_selection_phase_view(resource_registry const & registry)
    : registry_{registry}
{
}

void sgg_selection_phase_view::draw()
{
    sgg_draw_utils::draw_background(registry_.get_arena_background());
}

void sgg_selection_phase_view::update(float ms) 
{
    selection_helper_.update();
}

auto sgg_selection_phase_view::is_card_targeted(bool top, size_t index) const -> bool 
{
    return selection_helper_.is_card_targeted(top, index);
}

auto sgg_selection_phase_view::is_card_selected(bool top, size_t index) const -> bool
{
    return selection_helper_.is_card_selected(top, index);
}

void sgg_selection_phase_view::draw_card(
    bool top, size_t index, 
    bool active_turn, bool preview, bool cross, 
    card const & card) 
{
    sgg_draw_utils::draw_card(top, index, active_turn, preview, cross, registry_, card);
}
