#include <Preferences.h>
#include <action/ActionMgr.h>

ActionMgr* ActionMgr::sInstance = nullptr;

namespace {

const std::string cNoDescription;

}

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
    , mCompoundDepth(0)
    , mCompoundFailed(false)
{
    mMaxHistory = Preferences::instance()->getMaxUndoHistory();
}

ActionMgr::~ActionMgr()
{
}

bool ActionMgr::pushAction(ActionFactory factory, const void* context)
{
    if (mCompoundDepth > 0)
    {
        if (mCompoundFailed)
            return false;

        RIO_ASSERT(mCompound);

        std::unique_ptr<IAction> action = (*factory)(context);

        if (!action->apply())
        {
            abandonCompound_();
            return false;
        }

        mCompound->addAction(std::move(action));
        return true;
    }

    std::unique_ptr<IAction> action = (*factory)(context);

    if (!action->apply())
        return false;

    pushApplied_(std::move(action));
    return true;
}

void ActionMgr::pushApplied_(std::unique_ptr<IAction> action)
{
    RIO_ASSERT(action);

    mAction.resize(mCurrentLength);
    if (mNonDirtyLength != cInvalidLength && mNonDirtyLength > mCurrentLength)
        mNonDirtyLength = cInvalidLength;

    mAction.emplace_back(std::move(action));
    mCurrentLength++;

    trimHistory_();
}

void ActionMgr::trimHistory_()
{
    if (mMaxHistory == 0 || mAction.size() <= mMaxHistory)
        return;

    u32 trim_num = std::min<u32>(u32(mAction.size()) - mMaxHistory, mCurrentLength);
    if (trim_num == 0)
        return;

    mAction.erase(mAction.begin(), mAction.begin() + trim_num);
    mCurrentLength -= trim_num;

    if (mNonDirtyLength != cInvalidLength)
    {
        if (mNonDirtyLength >= trim_num)
            mNonDirtyLength -= trim_num;
        else
            mNonDirtyLength = cInvalidLength;
    }
}

void ActionMgr::beginCompound(const std::string& description)
{
    if (mCompoundDepth++ > 0)
        return;

    RIO_ASSERT(!mCompound);
    mCompoundFailed = false;
    mCompound = std::make_unique<ActionCompound>(description);
}

bool ActionMgr::endCompound()
{
    if (mCompoundDepth == 0)
        return false;

    if (--mCompoundDepth > 0)
        return false;

    const bool failed = mCompoundFailed;

    std::unique_ptr<ActionCompound> compound = std::move(mCompound);
    mCompound = nullptr;
    mCompoundFailed = false;

    if (failed || !compound || compound->isEmpty())
        return false;

    compound->resolveDescription();

    pushApplied_(std::move(compound));
    return true;
}

void ActionMgr::cancelCompound()
{
    if (mCompoundDepth == 0)
        return;

    abandonCompound_();
}

void ActionMgr::abandonCompound_()
{
    mCompoundFailed = true;

    if (!mCompound)
        return;

    std::unique_ptr<ActionCompound> compound = std::move(mCompound);
    mCompound = nullptr;

    compound->unapply();
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

    if (!mAction[mCurrentLength]->apply())
        return;

    mCurrentLength++;
}

void ActionMgr::onSave()
{
    mNonDirtyLength = mCurrentLength;
}

void ActionMgr::discard(bool invalidate)
{
    mCompound = nullptr;
    mCompoundDepth = 0;
    mCompoundFailed = false;

    mAction.clear();
    mNonDirtyLength = invalidate ? cInvalidLength : 0;
    mCurrentLength = 0;
}

const std::string& ActionMgr::getActionDescription(u32 index) const
{
    if (index >= mAction.size())
        return cNoDescription;

    return mAction[index]->getDescription();
}

const std::string& ActionMgr::getUndoDescription() const
{
    if (!canUndo())
        return cNoDescription;

    return mAction[mCurrentLength - 1]->getDescription();
}

const std::string& ActionMgr::getRedoDescription() const
{
    if (!canRedo())
        return cNoDescription;

    return mAction[mCurrentLength]->getDescription();
}

void ActionMgr::setMaxHistory(u32 max_history)
{
    mMaxHistory = max_history;
}
