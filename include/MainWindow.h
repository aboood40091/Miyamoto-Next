#pragma once

#include <controller/win/rio_KeyboardMouseDeviceWin.h>
#include <gfx/rio_Camera.h>
#include <gfx/rio_Projection.h>
#include <task/rio_Task.h>

class MainWindow : public rio::ITask
{
public:
    MainWindow();

    void prepare_() override;
    void calc_()    override;
    void exit_()    override;

private:
    rio::LookAtCamera           mCamera;
    rio::OrthoProjection        mProjection;
    rio::KeyboardMouseDevice*   mpKeyboardMouseDevice;
};
