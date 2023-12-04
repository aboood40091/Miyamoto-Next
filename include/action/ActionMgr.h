#pragma once

#include <action/IAction.h>

#include <vector>

using ActionFactory = std::unique_ptr<IAction> (*)(const void*);

class ActionMgr
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static ActionMgr* instance() { return sInstance; }

private:
    static ActionMgr* sInstance;

    ActionMgr();
    ~ActionMgr();

    ActionMgr(const ActionMgr&);
    ActionMgr& operator=(const ActionMgr&);

public:
    bool pushAction(ActionFactory factory, const void* context);

    template <typename T>
    bool pushAction(const void* context)
    {
        return pushAction(&T::create, context);
    }

    bool canUndo() const
    {
        return mCurrentLength > 0;
    }

    bool canRedo() const
    {
        return mAction.size() > mCurrentLength;
    }

    void undo();
    void redo();

    bool isDirty() const
    {
        return mCurrentLength != mNonDirtyLength;
    }

    void onSave();

    void discard(bool invalidate);

private:
    std::vector< std::unique_ptr<IAction> > mAction;
    u32                                     mNonDirtyLength;
    u32                                     mCurrentLength;

};
