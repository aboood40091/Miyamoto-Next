#pragma once

#include <gfx/rio_Camera.h>
#include <gfx/rio_Projection.h>
#include <task/rio_Task.h>

class MainWindow : public rio::ITask
{
public:
    MainWindow();

    void prepare_() override;
    void calc_()    override;

private:
    rio::LookAtCamera           mCamera;
    rio::OrthoProjection        mProjection;
};
