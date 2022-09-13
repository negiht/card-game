#pragma once

struct exitor
{
	virtual ~exitor(){}
	virtual void exit() = 0;
};
