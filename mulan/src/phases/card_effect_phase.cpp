#include <mulan/phases/card_effect_phase.hpp>

card_effect_phase::card_effect_phase(
    bool player,
    size_t selected,
    size_t target,
    game_state & state,
    std::unique_ptr<card_effect_phase_view> view,
    std::unique_ptr<card_effect_phase_switcher> switcher
)
    : player_{player}
    , selected_{selected}
    , target_{target}
    , state_{state}
    , view_{std::move(view)}
    , switcher_{std::move(switcher)}
{
}

void card_effect_phase::update(float ms)
{
    view_->update(ms);

    if (view_->is_finished())
    {
        auto const & selected = state_.players[player_].cards[selected_];
        auto & target = state_.players[!player_].cards[target_];

        target.reduce_health(selected.damage());

        switcher_->next();
    }
}

void card_effect_phase::draw()
{
    view_->draw();
    for (size_t i = 0; i != 6; ++i)
    {
        auto const & card = state_.players[player_].cards[i];
        if (card.is_alive())
            view_->draw_card(player_, i, i == selected_, card);
    }
    for (size_t i = 0; i != 6; ++i)
    {
        auto const & card = state_.players[!player_].cards[i];
        if (card.is_alive())
            view_->draw_card(!player_, i, i == target_, card);
    }
}
