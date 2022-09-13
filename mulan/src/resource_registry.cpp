#include <mulan/resource_registry.hpp>

void resource_registry::set_loading_background(std::string const & x) { loading_background_ = x; }
void resource_registry::set_loading_button_font(std::string const & x ) { loading_button_font_ = x; }
void resource_registry::set_arena_background(std::string const & x) { arena_background_ = x; }
void resource_registry::set_card_font(std::string const & x) { card_font_ = x; }
void resource_registry::set_card_target(std::string const & x) { card_target_ = x; }

void resource_registry::set_background_music(char const * x) { background_music_ = x; }
void resource_registry::set_battle_start_sound(char const * x) { battle_start_sound_ = x; }
void resource_registry::set_hit_sound(char const * x) { hit_sound_ = x; }
void resource_registry::set_battle_end_sound(char const * x) { battle_end_sound_ = x; }


auto resource_registry::get_loading_background() const -> std::string const & { return loading_background_; }
auto resource_registry::get_loading_button_font() const -> std::string const & { return loading_button_font_; }
auto resource_registry::get_arena_background() const -> std::string const & { return arena_background_; }
auto resource_registry::get_card_font() const -> std::string const & { return card_font_; }
auto resource_registry::get_card_target() const -> std::string const & { return card_target_; }

auto resource_registry::get_background_music() const -> char const * { return background_music_; }
auto resource_registry::get_battle_start_sound() const -> char const * { return battle_start_sound_; }
auto resource_registry::get_hit_sound() const -> char const * { return hit_sound_; }
auto resource_registry::get_battle_end_sound() const -> char const * { return battle_end_sound_; }

auto resource_registry::register_card_image(std::string const & x) -> card_image_handle 
{ 
    card_images_.push_back(x);
    return card_images_.size() - 1;
}

auto resource_registry::get_card_image(card_image_handle handle) const -> std::string const & 
{ 
    return card_images_.at(handle); 
}
