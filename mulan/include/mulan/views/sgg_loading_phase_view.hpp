#pragma once

#include <mulan/views/loading_phase_view.hpp>
#include <mulan/square_collider.hpp>
#include <mulan/sgg_selection_helper.hpp>
#include <mulan/resource_registry.hpp>

#include <string>

class sgg_loading_phase_view : public loading_phase_view
{
public:
    sgg_loading_phase_view(resource_registry const & registry);

    void draw() override;
    void update(float ms) override;

    auto start_new_game_pressed() const -> bool override;

private:
    square_collider collider_;
    sgg_selection_helper selection_helper_;
    resource_registry const & registry_;
    bool is_targeted_{};
    bool new_game_pressed_{};
};
