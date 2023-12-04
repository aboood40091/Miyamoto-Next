#pragma once

#include <misc/rio_Types.h>

class IAction
{
public:
    IAction(void* context)
    {
    }

    virtual bool apply() = 0;
    virtual void unapply() = 0;
};
