#pragma once

#include <course/CourseData.h>
#include <course/BgRenderer.h>

#include <graphics/OrthoCamera.h>

#include <item/AreaItem.h>
#include <item/LocationItem.h>
#include <item/NextGotoItem.h>
#include <item/SpriteItem.h>

#if RIO_IS_WIN
#include <controller/win/rio_KeyboardMouseDeviceWin.h>
#endif // RIO_IS_WIN

#include <controller/rio_Controller.h>
#include <gfx/rio_Projection.h>
#include <task/rio_Task.h>

class MainWindow : public rio::ITask
{
public:
    MainWindow();

    rio::Vector2f viewToWorldPos(const rio::Vector2f& pos) const;
    rio::Vector3f viewToWorldPos(const rio::Vector3f& pos) const;

    const rio::Vector2f& getCursorPos() const
    {
        return mCursorPos;
    }

    rio::Vector2f getCursorWorldPos() const
    {
        return viewToWorldPos(mCursorPos);
    }

    void setCurrentCourseDataFile(u32 id);

  //bool checkButtonPress(u32 idx, rio::Controller::PadIdx button);

private:
    void prepare_() override;
    void calc_()    override;
    void exit_()    override;

    void processInputs_();
    void updateCursorPos_();
    void drawCursor_();

private:
    OrthoCamera                 mCamera;
    rio::OrthoProjection        mProjection;
#if RIO_IS_WIN
    rio::KeyboardMouseDevice*   mpKeyboardMouseDevice;
#endif // RIO_IS_WIN
    rio::Vector2f               mCursorPos;
    rio::Vector2f               mLastCursorPos;

    CourseData                  mCourseData;
    BgRenderer                  mBgRenderer;
    s32                         mCurrentFile;

    std::vector<NextGotoItem>   mNextGotoItem;
    std::vector<SpriteItem>     mSpriteItem;
    std::vector<AreaItem>       mAreaItem;
    std::vector<LocationItem>   mLocationItem;

  //static constexpr s32 cButtonMaxNum = CD_FILE_LAYER_MAX_NUM + 2;

  //u32     mHoldCounter   [cButtonMaxNum];
  //bool    mWaitForRelease[cButtonMaxNum];

    bool    mBlendEnable;
    bool    mLayerShown[CD_FILE_LAYER_MAX_NUM];
};
