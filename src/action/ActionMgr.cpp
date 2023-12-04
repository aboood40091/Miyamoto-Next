#include <action/ActionMgr.h>

ActionMgr* ActionMgr::sInstance = nullptr;

bool ActionMgr::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new ActionMgr();
    return true;
}

void ActionMgr::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

ActionMgr::ActionMgr()
    : mNonDirtyLength(0)
    , mCurrentLength(0)
{
}

ActionMgr::~ActionMgr()
{
}

bool ActionMgr::pushAction(ActionFactory factory, const void* context)
{
    mAction.resize(mCurrentLength);
    if (mNonDirtyLength != u32(-1) && mNonDirtyLength > mCurrentLength)
        mNonDirtyLength = u32(-1);

    std::unique_ptr action = (*factory)(context);
    if (!action->apply())
        return false;

    mAction.emplace_back(std::move(action));
    mCurrentLength++;
    return true;
}

void ActionMgr::undo()
{
    if (!canUndo())
        return;

    mAction[--mCurrentLength]->unapply();
}

void ActionMgr::redo()
{
    if (!canRedo())
        return;

    [[maybe_unused]] bool success = mAction[mCurrentLength]->apply();
    RIO_ASSERT(success);
    mCurrentLength++;
}

void ActionMgr::onSave()
{
    mNonDirtyLength = mCurrentLength;
}

void ActionMgr::discard(bool invalidate)
{
    mAction.clear();
    mNonDirtyLength = invalidate ? u32(-1) : 0;
    mCurrentLength = 0;
}
