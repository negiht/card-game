#include <mulan/phases/end_phase.hpp>

#include <sgg/graphics.h>

#include <memory>

end_phase::end_phase ( 
    std::unique_ptr<end_phase_view> view,
    std::unique_ptr<end_phase_switcher> switcher
) 
    : view_{std::move(view)}
    , switcher_{std::move(switcher)}
{
}

void end_phase::draw()
{
    view_->draw();
}

void end_phase::update(float ms)
{
    view_->update(ms);
    if (view_->new_game_pressed())
        switcher_->next_retry();
    if (view_->exit_pressed())
        switcher_->next_exit();
}
