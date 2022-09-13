#pragma once
#include <array>
#include <memory>
#include <vector>
#include <string>
#include <optional>

class card 
{
public:
    card(int health, int damage, size_t image_handle)
        : health_{health}
        , damage_{damage}
        , image_handle_{image_handle}
    {
    }

    size_t image_handle() const { return image_handle_; }

    bool is_alive() const { return health_ > 0; }

    int health() const { return health_; }

    int damage() const { return damage_; }

    void reduce_health(int amount)
    {
        health_ -= amount;
    }

private:
    size_t image_handle_;
    int health_;
    int damage_;
};

struct player_state
{
    std::array<card, 6> cards;

    bool is_alive() const
    {
        bool alive = false;
        for (auto card : cards)
        {
            if (card.is_alive())
                alive = true;
        }
        return alive;
    }
};

struct game_state
{
    std::array<player_state, 2> players;
};
