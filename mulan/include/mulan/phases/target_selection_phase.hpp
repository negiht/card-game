#pragma once

#include <mulan/object.hpp>
#include <mulan/views/selection_phase_view.hpp>
#include <mulan/phase_switcher.hpp>

class target_selection_phase : public object
{
public:
    target_selection_phase(
        bool player, 
        size_t selected, 
        game_state const & state,
        std::unique_ptr<selection_phase_view> view, 
        std::unique_ptr<target_selection_phase_switcher> switcher 
    );

    void draw() override;
    void update(float ms) override;

private:
    bool player_;
    size_t selected_card_;
    game_state const & state_;
    std::unique_ptr<selection_phase_view> view_;
    std::unique_ptr<target_selection_phase_switcher> switcher_;
};
