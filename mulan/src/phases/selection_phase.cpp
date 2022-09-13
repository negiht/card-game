#include <phases/selection_phase.hpp>

selection_phase::selection_phase(
    bool player,
    game_state const & state,
    std::unique_ptr<selection_phase_view> view,
    std::unique_ptr<selection_phase_switcher> switcher
) 
    : player_{player}
    , state_{state}
    , view_{std::move(view)}
    , switcher_{std::move(switcher)}
{
}

void selection_phase::draw_card(bool player, size_t index)
{
    auto card = state_.players[player].cards[index];

    if (card.is_alive())
    {
        if (player_ == player)
        {
            view_->draw_card(player, index,
                true,
                view_->is_card_targeted(player, index),
                false,
                card);
        }
        else
        {
            view_->draw_card(player, index,
                false,
                false,
                false,
                card);
        }
    }
}

void selection_phase::draw()
{
    view_->draw();

    for (size_t player = 0; player != 2; ++player)
    {
        for (size_t i = 0; i != 6; ++i)
        {
            draw_card(player, i);
        }
    }
}

void selection_phase::update(float ms)
{
    view_->update(ms);

    for (size_t i = 0; i != 6; ++i)
    {
        if (view_->is_card_selected(player_, i))
        {
            switcher_->next(i);
            break;
        }
    }
}
