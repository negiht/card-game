#include <mulan/views/sgg_card_effect_phase_view.hpp>
#include <mulan/sgg_draw_utils.hpp>
#include <sgg/audio.h>

sgg_card_effect_phase_view::sgg_card_effect_phase_view(resource_registry const & registry)
    : registry_{registry}
{
    playSound(registry_.get_hit_sound(), 128);
}

auto sgg_card_effect_phase_view::is_finished() const -> bool
{
    return is_finished_;
}

void sgg_card_effect_phase_view::draw_card(bool top, size_t index, bool preview, card const & card)
{
    sgg_draw_utils::draw_card(top, index, false, preview, false, registry_, card);
}

void sgg_card_effect_phase_view::update(float ms)
{
    /* TODO: effect & music */
    is_finished_ = true;
}

void sgg_card_effect_phase_view::draw()
{
    sgg_draw_utils::draw_background(registry_.get_arena_background());
}
