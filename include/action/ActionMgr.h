#pragma once

#include <action/ActionCompound.h>
#include <action/IAction.h>

#include <string>
#include <vector>

using ActionFactory = std::unique_ptr<IAction> (*)(const void*);

class ActionMgr
{
public:
    static const u32 cDefaultMaxHistory = 100;
    static const u32 cMaxUserMaxHistory = 10000;

    static const u32 cInvalidLength = u32(-1);

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

    void beginCompound(const std::string& description = std::string());
    bool endCompound();
    void cancelCompound();

    bool isCompoundOpen() const
    {
        return mCompoundDepth > 0;
    }

    bool isCompoundFailed() const
    {
        return isCompoundOpen() && mCompoundFailed;
    }

    class CompoundGuard
    {
    public:
        explicit CompoundGuard(const std::string& description = std::string())
        {
            ActionMgr::instance()->beginCompound(description);
        }

        ~CompoundGuard()
        {
            ActionMgr::instance()->endCompound();
        }

        void cancel()
        {
            ActionMgr::instance()->cancelCompound();
        }

        CompoundGuard(const CompoundGuard&) = delete;
        CompoundGuard& operator=(const CompoundGuard&) = delete;
    };

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

    u32 getActionNum() const
    {
        return u32(mAction.size());
    }

    u32 getCurrentLength() const
    {
        return mCurrentLength;
    }

    const std::string& getActionDescription(u32 index) const;

    const std::string& getUndoDescription() const;
    const std::string& getRedoDescription() const;

    u32 getMaxHistory() const
    {
        return mMaxHistory;
    }

    void setMaxHistory(u32 max_history);

private:
    void pushApplied_(std::unique_ptr<IAction> action);
    void trimHistory_();
    void abandonCompound_();

private:
    std::vector< std::unique_ptr<IAction> > mAction;
    u32                                     mNonDirtyLength;
    u32                                     mCurrentLength;
    u32                                     mMaxHistory;

    std::unique_ptr<ActionCompound>         mCompound;
    u32                                     mCompoundDepth;
    bool                                    mCompoundFailed;
};
