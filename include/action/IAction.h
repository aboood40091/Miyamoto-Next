#pragma once

#include <misc/rio_Types.h>

#include <memory>

class IAction
{
public:
    IAction(const void* context)
    {
    }

    virtual bool apply() const = 0;
    virtual void unapply() const = 0;
};

#define ACTION_CREATE(CLASS)                                        \
    public:                                                         \
        static std::unique_ptr<IAction> create(const void* context) \
        {                                                           \
            return std::make_unique<CLASS>(context);                \
        }
