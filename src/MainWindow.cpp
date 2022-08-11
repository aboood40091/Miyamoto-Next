#include <MainWindow.h>

#include <controller/rio_ControllerMgr.h>
#include <gfx/rio_PrimitiveRenderer.h>
#include <gfx/rio_Window.h>

MainWindow::MainWindow()
    : rio::ITask("Miyamoto! Next")
{
}

void MainWindow::updateCursorPos_()
{
    mCursorPos = mpKeyboardMouseDevice->getCursorPos();

    const f32 window_w = rio::Window::instance()->getWidth();
    const f32 window_h = rio::Window::instance()->getHeight();

    const f32 window_w_2 = window_w / 2;
    const f32 window_h_2 = window_h / 2;

    mCursorPos.x = mCursorPos.x - window_w_2;
    mCursorPos.y = window_h_2 - mCursorPos.y;

    if (mCursorPos.x < -window_w_2)
        mCursorPos.x = -window_w_2;
    else if (mCursorPos.x > window_w_2)
        mCursorPos.x = window_w_2;

    if (mCursorPos.y < -window_h_2)
        mCursorPos.y = -window_h_2;
    else if (mCursorPos.y > window_h_2)
        mCursorPos.y = window_h_2;
}

void MainWindow::prepare_()
{
    mCamera.pos().set(  0.0f, 0.0f, 1.0f  );
    mCamera.at ().set(  0.0f, 0.0f, 0.0f  );
    mCamera.setUp    ({ 0.0f, 1.0f, 0.0f });

    const f32 window_w = rio::Window::instance()->getWidth();
    const f32 window_h = rio::Window::instance()->getHeight();

    const f32 window_w_2 = window_w / 2;
    const f32 window_h_2 = window_h / 2;

    mProjection.set(1000.0f, -1000.0f, window_h_2, -window_h_2, -window_w_2, window_w_2);

    rio::PrimitiveRenderer::instance()->setCamera(mCamera);
    rio::PrimitiveRenderer::instance()->setProjection(mProjection);
    rio::PrimitiveRenderer::instance()->setModelMatrix(rio::Matrix34f::ident);

    mpKeyboardMouseDevice = static_cast<rio::KeyboardMouseDevice*>(rio::ControllerMgr::instance()->getControlDevice(rio::ControllerDefine::DEVICE_KEYBOARD_MOUSE));
    RIO_ASSERT(mpKeyboardMouseDevice);

    updateCursorPos_();
}

void MainWindow::calc_()
{
    updateCursorPos_();

    rio::Window::instance()->clearColor(0.25f, 0.5f, 0.75f);
    rio::Window::instance()->clearDepthStencil();

    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::PrimitiveRenderer::instance()->drawQuad(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(rio::Color4f::cRed, rio::Color4f::cBlue)
                .setCenter({ mCursorPos.x, mCursorPos.y, 0.0f })
                .setSize({ 16.0f, 16.0f })
        );
    }
    rio::PrimitiveRenderer::instance()->end();
}

void MainWindow::exit_()
{
    mpKeyboardMouseDevice = nullptr;
}
