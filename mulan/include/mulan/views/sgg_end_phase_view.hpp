#pragma once

#include <mulan/views/end_phase_view.hpp>
#include <mulan/square_collider.hpp>
#include <mulan/sgg_selection_helper.hpp>
#include <mulan/resource_registry.hpp>

#include <string>

class sgg_end_phase_view : public end_phase_view
{
public:
    sgg_end_phase_view(bool winner, resource_registry const & registry);

    void draw() override;
    void update(float ms) override;

    auto new_game_pressed() const -> bool override;
    auto exit_pressed() const -> bool override;

private:
    bool winner_;
    resource_registry const & registry_;

    square_collider start_collider_;
    square_collider exit_collider_;
    sgg_selection_helper new_game_selection_helper_;
    sgg_selection_helper exit_selection_helper_;
    bool new_game_is_targeted_{};
    bool new_game_pressed_{};
    bool exit_is_targeted_{};
    bool exit_pressed_{};
};
