#pragma once

#include <mulan/object.hpp>
#include <mulan/game_state.hpp>
#include <mulan/resource_registry.hpp>
#include <mulan/phase_switcher.hpp>
#include <memory>
#include <exitor.hpp>

class game
{
public:
    game(std::unique_ptr<exitor>); 
    void update(float ms);
    void draw();

private:
    struct loading_phase_switcher_wrapper;
    struct selection_phase_switcher_wrapper;
    struct target_selection_phase_switcher_wrapper;
    struct card_effect_phase_switcher_wrapper;
    struct end_phase_switcher_wrapper;

    void create_loading_phase();
    void create_selection_phase(bool player);
    void create_target_selection_phase(bool player, size_t selected);
    void create_card_effect_phase(bool player, size_t selected, size_t target);
    void create_end_phase(bool winner);

    auto random_card() const -> card;
    auto create_state() -> game_state;

    std::unique_ptr<exitor> exitor_;

    resource_registry registry_;
    std::array<card, 12> card_pool_;
    game_state state_;
    std::unique_ptr<object> phase_;
    std::unique_ptr<object> next_phase_;
};
