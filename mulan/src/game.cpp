#include <mulan/defines.hpp>
#include <mulan/game.hpp>
#include <mulan/phases/loading_phase.hpp>
#include <mulan/phases/selection_phase.hpp>
#include <mulan/phases/target_selection_phase.hpp>
#include <mulan/phases/card_effect_phase.hpp>
#include <mulan/phases/end_phase.hpp>
#include <mulan/views/sgg_loading_phase_view.hpp>
#include <mulan/views/sgg_selection_phase_view.hpp>
#include <mulan/views/sgg_card_effect_phase_view.hpp>
#include <mulan/views/sgg_end_phase_view.hpp>
#include <memory>
#include <random>
#include <algorithm>

auto game::create_state() -> game_state
{
    std::random_device rd;
    std::mt19937 g{ rd() };
    std::shuffle(card_pool_.begin(), card_pool_.end(), g);

    return game_state{
        player_state{ card_pool_[0], card_pool_[1], card_pool_[2], card_pool_[3], card_pool_[4], card_pool_[5] },
        player_state{ card_pool_[6], card_pool_[7], card_pool_[8], card_pool_[9], card_pool_[10], card_pool_[11] }
    };
}

game::game(std::unique_ptr<exitor> exitor)
    : exitor_{std::move(exitor)}
    , card_pool_ {{
        {14,  6, registry_.register_card_image(ASSETS_PATH "yoda.png")} ,
        {10,  2, registry_.register_card_image(ASSETS_PATH "r2d2.png")} ,
        {13,  6, registry_.register_card_image(ASSETS_PATH "luke.png")} ,
        {17, 7, registry_.register_card_image(ASSETS_PATH "darth_vader.png")} ,
        {11, 3, registry_.register_card_image(ASSETS_PATH "palpatine.png")} ,
        {12, 5, registry_.register_card_image(ASSETS_PATH "obi_wan.png")} ,
        {12, 3, registry_.register_card_image(ASSETS_PATH "han_solo.png")} ,
        {13, 4, registry_.register_card_image(ASSETS_PATH "princess_lea.png")} ,
        {11, 3, registry_.register_card_image(ASSETS_PATH "wookie.png")} ,
        {12, 5, registry_.register_card_image(ASSETS_PATH "3cpo.png")},
        {13, 6, registry_.register_card_image(ASSETS_PATH "rey.png")},
        {15, 4, registry_.register_card_image(ASSETS_PATH "trooper.png")},
    }}
    , state_(create_state())
{
    registry_.set_loading_background(ASSETS_PATH "background.png");
    registry_.set_arena_background(ASSETS_PATH "background.png");
    registry_.set_loading_button_font(ASSETS_PATH "FreeSans.otf");
    registry_.set_card_font(ASSETS_PATH "FreeSans.otf");
    registry_.set_card_target(ASSETS_PATH "target.png");
    registry_.set_background_music(ASSETS_PATH "background_music.wav");
    registry_.set_battle_start_sound(ASSETS_PATH "battle_start_sound.wav");
    registry_.set_hit_sound(ASSETS_PATH "hit_sound.wav");
    registry_.set_battle_end_sound(ASSETS_PATH "the_end.wav");

    create_loading_phase();
}

struct game::loading_phase_switcher_wrapper : public loading_phase_switcher
{
    loading_phase_switcher_wrapper(game * self)
        : self{self}
    {
    }

    game * self;

    void next() override
    {
        self->create_selection_phase(false);
    }
};

struct game::selection_phase_switcher_wrapper : public selection_phase_switcher
{
    selection_phase_switcher_wrapper(game * self, bool player)
        : self{self}
        , player{player}
    {
    }

    game * self;
    bool player;

    void next(size_t selected) override
    {
        self->create_target_selection_phase(player, selected);
    }
};

struct game::target_selection_phase_switcher_wrapper : public target_selection_phase_switcher
{
    target_selection_phase_switcher_wrapper(game * self, bool player, size_t selected)
        : self{self}
        , player{player}
        , selected{selected}
    {
    }

    game * self;
    bool player;
    size_t selected;

    void next(size_t target) override
    {
        self->create_card_effect_phase(player, selected, target);
    }
};

struct game::card_effect_phase_switcher_wrapper : public card_effect_phase_switcher
{
    card_effect_phase_switcher_wrapper(game * self, bool player)
        : self{self}
        , player{player}
    {
    }

    game * self;
    bool player;

    void next() override
    {
        if (self->state_.players[!player].is_alive()) 
            self->create_selection_phase(!player);
        else
            self->create_end_phase(player);
    }
};

struct game::end_phase_switcher_wrapper : public end_phase_switcher
{
    end_phase_switcher_wrapper(game * self, bool winner)
        : self{self}
        , winner{winner}
    {
    }

    game * self;
    bool winner;

    void next_retry() override
    {
        self->state_ = self->create_state();
        self->create_selection_phase(!winner); 
    }

    void next_exit() override
    {
        self->exitor_->exit();
    }
};

void game::create_loading_phase()
{
    next_phase_ = std::make_unique<loading_phase>(
        std::make_unique<sgg_loading_phase_view>(registry_),
        std::make_unique<loading_phase_switcher_wrapper>(this)
    );
}

void game::create_selection_phase(bool player)
{
    next_phase_ = std::make_unique<selection_phase>(
        player,
        state_,
        std::make_unique<sgg_selection_phase_view>(registry_),
        std::make_unique<selection_phase_switcher_wrapper>(this, player)
    );
}

void game::create_target_selection_phase(bool player, size_t selected)
{
    next_phase_ = std::make_unique<target_selection_phase>(
        player,
        selected,
        state_,
        std::make_unique<sgg_selection_phase_view>(registry_),
        std::make_unique<target_selection_phase_switcher_wrapper>(this, player, selected)
    );
}

void game::create_card_effect_phase(bool player, size_t selected, size_t target)
{
    next_phase_ = std::make_unique<card_effect_phase>(
        player,
        selected,
        target,
        state_,
        std::make_unique<sgg_card_effect_phase_view>(registry_),
        std::make_unique<card_effect_phase_switcher_wrapper>(this, player)
    );
}

void game::create_end_phase(bool winner)
{
    next_phase_ = std::make_unique<end_phase>(
        std::make_unique<sgg_end_phase_view>(winner, registry_),
        std::make_unique<end_phase_switcher_wrapper>(this, winner)
    );
}


void game::update(float ms)
{
    if (phase_)
        phase_->update(ms);

    if (next_phase_)
    {
        phase_ = std::move(next_phase_);
        next_phase_ = nullptr;
    }
}

void game::draw()
{
    if (phase_)
        phase_->draw();
}
