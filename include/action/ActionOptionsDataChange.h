#pragma once

#include <action/IAction.h>
#include <course/CourseDataFile.h>

class ActionOptionsDataChange : public IAction
{
    ACTION_CREATE(ActionOptionsDataChange)

public:
    struct Context
    {
        Options before;
        Options after;

        ~Context();
    };

public:
    ActionOptionsDataChange(const void* context);

    bool apply() const override;
    void unapply() const override;

private:
    Options mBefore;
    Options mAfter;
};
