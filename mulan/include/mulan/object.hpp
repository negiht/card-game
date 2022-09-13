#pragma once

class object
{
public:
    virtual ~object() {}

    virtual void draw() = 0;
    virtual void update(float ms) = 0;
};
