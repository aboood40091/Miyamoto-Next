#pragma once

#include <misc/rio_Types.h>

#include <memory>
#include <string>
#include <utility>

class IAction
{
public:
    IAction(const void* context)
    {
    }

    virtual ~IAction()
    {
    }

    // Performs the change. Returning false means it could not be done *and
    // that the document is unchanged*: an action that gives up half way must
    // undo its own partial work before returning false, because unapply() will
    // not be called for it.
    //
    // The same applies on redo, so apply() must be repeatable.
    virtual bool apply() const = 0;

    // Reverses a successful apply(). Cannot fail.
    virtual void unapply() const = 0;

    // Short human-readable name for this action, e.g. "Move 12 Actors".
    // Shown after "Undo"/"Redo" and in the history. May be empty, in which
    // case callers would fall back to a bare "Undo"/"Redo".
    const std::string& getDescription() const
    {
        return mDescription;
    }

protected:
    std::string mDescription;
};

#define ACTION_CREATE(CLASS)                                        \
    public:                                                         \
        static std::unique_ptr<IAction> create(const void* context) \
        {                                                           \
            return std::make_unique<CLASS>(context);                \
        }
