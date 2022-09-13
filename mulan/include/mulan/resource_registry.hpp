#pragma once

#include <string>
#include <vector>
#include <cstddef>

class resource_registry
{
public:
    void set_loading_background(std::string const & x);
    void set_loading_button_font(std::string const & x );
    void set_arena_background(std::string const & x);
    void set_card_font(std::string const & x);
    void set_card_target(std::string const & x);

    void set_background_music(char const * x);
    void set_battle_start_sound(char const * x);
    void set_hit_sound(char const * x);
    void set_battle_end_sound(char const * x);

    auto get_loading_background() const -> std::string const &;
    auto get_loading_button_font() const -> std::string const &;
    auto get_arena_background() const -> std::string const &;
    auto get_card_font() const -> std::string const &;
    auto get_card_target() const -> std::string const &;

    auto get_background_music() const -> char const *;
    auto get_battle_start_sound() const -> char const *;
    auto get_hit_sound() const -> char const *;
    auto get_battle_end_sound() const -> char const *;

    using card_image_handle = size_t;
    auto register_card_image(std::string const & x) -> card_image_handle;
    auto get_card_image(card_image_handle handle) const -> std::string const &;

private:
    std::string loading_background_;
    std::string loading_button_font_;
    std::string arena_background_;
    std::string card_font_;
    std::string card_target_;

    char const * background_music_ = "";
    char const * battle_start_sound_ = "";
    char const * hit_sound_ = "";
    char const * battle_end_sound_ = "";

    std::vector<std::string> card_images_;
};
