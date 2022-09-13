#pragma once

#include <cmath>

class square_collider
{
public:
    square_collider() = default;
    square_collider(float x, float y, float width, float height)
        : x_{x}
        , y_{y}
        , width_{width}
        , height_{height}
    {
    }

    void setup(float x, float y, float width, float height)
    {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
    }

    auto in_bounds(float x, float y) const -> bool
    {
        return std::abs(x_ - x) <= width_ / 2 &&
               std::abs(y_ - y) <= height_ / 2;
    }

private:
    float width_{};
    float height_{};
    float x_{};
    float y_{};
};
