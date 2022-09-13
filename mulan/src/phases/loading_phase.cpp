#include <mulan/phases/loading_phase.hpp>

#include <sgg/graphics.h>

#include <memory>

loading_phase::loading_phase ( 
    std::unique_ptr<loading_phase_view> view,
    std::unique_ptr<loading_phase_switcher> switcher
) 
        : view_{std::move(view)}
        , switcher_{std::move(switcher)}
{
}

void loading_phase::draw()
{
    view_->draw();
}

void loading_phase::update(float ms)
{
    view_->update(ms);
    if (view_->start_new_game_pressed())
        switcher_->next();
}
