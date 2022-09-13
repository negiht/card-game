#pragma once

#include <mulan/views/card_effect_phase_view.hpp>
#include <mulan/game_state.hpp>
#include <mulan/resource_registry.hpp>

class sgg_card_effect_phase_view : public card_effect_phase_view
{
public:
    sgg_card_effect_phase_view(resource_registry const & registry);

    void draw_card(bool top, size_t index, bool preview, card const &) override;
    void update(float ms) override;
    void draw() override;

    auto is_finished() const -> bool override;

private:
    resource_registry const & registry_;
    bool is_finished_{};
};
