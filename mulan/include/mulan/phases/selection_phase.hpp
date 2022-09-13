#pragma once

#include <mulan/object.hpp>
#include <mulan/game_state.hpp>
#include <mulan/phase_switcher.hpp>
#include <mulan/square_collider.hpp>
#include <mulan/views/selection_phase_view.hpp>
#include <array>

class selection_phase : public object
{
public:
    selection_phase(
        bool player,
        game_state const & state,
        std::unique_ptr<selection_phase_view> view,
        std::unique_ptr<selection_phase_switcher> switcher
    );

    void draw() override;
    void update(float ms) override;

private:
    void draw_card(bool player, size_t index);

    bool player_{};

    game_state const & state_;
    std::unique_ptr<selection_phase_view> view_;
    std::unique_ptr<selection_phase_switcher> switcher_;
};
