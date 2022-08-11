#pragma once

#include <controller/win/rio_KeyboardMouseDeviceWin.h>
#include <gfx/rio_Camera.h>
#include <gfx/rio_Projection.h>
#include <task/rio_Task.h>

class MainWindow : public rio::ITask
{
public:
    MainWindow();

    const rio::Vector2f& getCursorPos() const
    {
        return mCursorPos;
    }

private:
    void prepare_() override;
    void calc_()    override;
    void exit_()    override;

    void updateCursorPos_();

private:
    rio::LookAtCamera           mCamera;
    rio::OrthoProjection        mProjection;
    rio::KeyboardMouseDevice*   mpKeyboardMouseDevice;
    rio::Vector2f               mCursorPos;
};
