#pragma once

#include <mulan/views/selection_phase_view.hpp>
#include <mulan/square_collider.hpp>
#include <mulan/sgg_multi_selection_helper.hpp>
#include <mulan/resource_registry.hpp>

#include <string>

class sgg_selection_phase_view : public selection_phase_view
{
public:
    sgg_selection_phase_view(resource_registry const & registry);

    void draw() override;
    void update(float ms) override;
    auto is_card_targeted(bool top, size_t index) const -> bool override;
    auto is_card_selected(bool top, size_t index) const -> bool override;
    void draw_card(bool top, size_t index, bool active_turn, bool preview, bool cross, card const &) override;

private:
    resource_registry const & registry_;
    sgg_multi_selection_helper selection_helper_{};
};
