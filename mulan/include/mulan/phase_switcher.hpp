#pragma once

#include <cstddef>

struct card_effect_phase_switcher
{
    virtual ~card_effect_phase_switcher() {}
    virtual void next() = 0;
};

struct end_phase_switcher
{
    virtual ~end_phase_switcher() {}
    virtual void next_retry() = 0;
    virtual void next_exit() = 0;
};

struct loading_phase_switcher
{
    virtual ~loading_phase_switcher() {}
    virtual void next() = 0;
};

struct selection_phase_switcher
{
    virtual ~selection_phase_switcher() {}
    virtual void next(size_t selected) = 0;
};

struct target_selection_phase_switcher
{
    virtual ~target_selection_phase_switcher() {}
    virtual void next(size_t selected) = 0;
};
