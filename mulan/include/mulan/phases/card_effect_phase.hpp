#pragma once

#include <mulan/object.hpp>
#include <mulan/game_state.hpp>
#include <mulan/square_collider.hpp>
#include <mulan/views/card_effect_phase_view.hpp>
#include <mulan/phase_switcher.hpp>
#include <array>

class card_effect_phase : public object
{
public:
    card_effect_phase(
        bool player,
        size_t selected,
        size_t target,
        game_state & state,
        std::unique_ptr<card_effect_phase_view> view,
        std::unique_ptr<card_effect_phase_switcher> switcher
    );

    void draw() override;
    void update(float ms) override;

private:
    bool player_;
    size_t selected_;
    size_t target_;
    game_state & state_;
    std::unique_ptr<card_effect_phase_view> view_;
    std::unique_ptr<card_effect_phase_switcher> switcher_;
};
