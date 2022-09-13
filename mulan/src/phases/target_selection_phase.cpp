#include <mulan/phases/target_selection_phase.hpp>

target_selection_phase::target_selection_phase(
    bool player, 
    size_t selected, 
    game_state const & state,
    std::unique_ptr<selection_phase_view> view, 
    std::unique_ptr<target_selection_phase_switcher> switcher
) 
    : player_{player}
    , selected_card_{selected}
    , state_{state}
    , view_{std::move(view)}
    , switcher_{std::move(switcher)}
{
}

void target_selection_phase::update(float ms)
{
    view_->update(ms);

    for (size_t i = 0; i != 6; ++i)
    {
        if (view_->is_card_selected(!player_, i))
        {
            switcher_->next(i);
            break;
        }
    }
}

void target_selection_phase::draw()
{
    view_->draw();

    for (size_t i = 0; i != 6; ++i)
    {
        auto card = state_.players[player_].cards[i];

        if (card.is_alive())
        {
            view_->draw_card(player_, i, true, i == selected_card_, false, card);
        }
    }

    for (size_t i = 0; i != 6; ++i)
    {
        auto card = state_.players[!player_].cards[i];

        if (card.is_alive())
        { 
            bool is_targeted = view_->is_card_targeted(!player_, i);
            view_->draw_card(!player_, i, false, is_targeted, is_targeted, card);
        }
    }
}
