#include <MainWindow.h>

#include <controller/rio_ControllerMgr.h>
#include <gfx/rio_PrimitiveRenderer.h>
#include <gfx/rio_Window.h>
#include <gpu/rio_RenderState.h>
#include <misc/rio_MemUtil.h>

#include <resource/SZSDecompressor.h>

#if RIO_IS_WIN
static const char* level_path = "native://D:/New Super Mario Bros. U (USA, Physical)/New Super Mario Bros. U (USA, Physical)/data/content/Common/course_res_pack/1-1.szs";
#else
static const char* level_path = "1-1.szs";
#endif // RIO_IS_WIN

MainWindow::MainWindow()
    : rio::ITask("Miyamoto! Next")
{
}

rio::Vector2f MainWindow::viewToWorldPos(const rio::Vector2f& pos) const
{
    rio::Matrix34f view;
    mCamera.getMatrix(&view);

    rio::Matrix34f viewInv;
    bool ret = viewInv.setInverse(view);

    if (ret)
    {
        return {
            viewInv.m[0][0] * pos.x + viewInv.m[0][1] * pos.y + viewInv.m[0][3],
            viewInv.m[1][0] * pos.x + viewInv.m[1][1] * pos.y + viewInv.m[1][3]
        };
    }
    else
    {
        return pos;
    }
}

rio::Vector3f MainWindow::viewToWorldPos(const rio::Vector3f& pos) const
{
    rio::Matrix34f view;
    mCamera.getMatrix(&view);

    rio::Matrix34f viewInv;
    bool ret = viewInv.setInverse(view);

    if (ret)
    {
        return {
            viewInv.m[0][0] * pos.x + viewInv.m[0][1] * pos.y + viewInv.m[0][2] * pos.z + viewInv.m[0][3],
            viewInv.m[1][0] * pos.x + viewInv.m[1][1] * pos.y + viewInv.m[1][2] * pos.z + viewInv.m[1][3],
            viewInv.m[2][0] * pos.x + viewInv.m[2][1] * pos.y + viewInv.m[2][2] * pos.z + viewInv.m[2][3]
        };
    }
    else
    {
        return pos;
    }
}

void MainWindow::updateCursorPos_()
{
    mLastCursorPos = mCursorPos;

#if !RIO_IS_WIN
    if (!rio::ControllerMgr::instance()->getMainPointer()->isPointerOn())
        return;
#endif

#if RIO_IS_WIN
    mCursorPos = mpKeyboardMouseDevice->getCursorPos();
#else
    mCursorPos = rio::ControllerMgr::instance()->getMainPointer()->getPointer();
#endif

    const f32 min_x =  0.0f;
    const f32 max_x =  s32(rio::Window::instance()->getWidth());

    const f32 min_y = -s32(rio::Window::instance()->getHeight());
    const f32 max_y =  0.0f;

    mCursorPos.x = mCursorPos.x;
    mCursorPos.y = -mCursorPos.y;

    if (mCursorPos.x < min_x)
        mCursorPos.x = min_x;
    else if (mCursorPos.x > max_x)
        mCursorPos.x = max_x;

    if (mCursorPos.y < min_y)
        mCursorPos.y = min_y;
    else if (mCursorPos.y > max_y)
        mCursorPos.y = max_y;

#if !RIO_IS_WIN
    if (rio::ControllerMgr::instance()->getMainPointer()->isPointerOnNow())
        mLastCursorPos = mCursorPos;
#endif
}

void MainWindow::processInputs_()
{
#if RIO_IS_WIN
    const u8* state = mpKeyboardMouseDevice->getKeyState();
    if (!state)
        return;

    if (state[0x04] & 0x80) // Mouse middle-click
#else
    if (rio::ControllerMgr::instance()->getMainPointer()->isHold(1 << rio::Controller::PAD_IDX_TOUCH))
#endif
    {
        static_cast<rio::Vector2f&>(mCamera.pos()) +=
            viewToWorldPos(mLastCursorPos) - viewToWorldPos(mCursorPos);
    }
}

void MainWindow::prepare_()
{
    /*
    for (s32 i = 0; i < cButtonMaxNum; i++)
    {
        mHoldCounter[i] = 0;
        mWaitForRelease[i] = false;
    }
    */

    mBlendEnable = true;
    mLayerShown[LAYER_0] = true;
    mLayerShown[LAYER_1] = true;
    mLayerShown[LAYER_2] = true;

    mCamera.setZoomScale(24.f / 16.f);

    mProjection.set(
        -10000.0f,                                   // Near
         20000.0f,                                   // Far
         0.0f,                                       // Top
        -s32(rio::Window::instance()->getHeight()),  // Bottom
         0.0f,                                       // Left
         s32(rio::Window::instance()->getWidth())    // Right
    );

    rio::PrimitiveRenderer::instance()->setProjection(mProjection);
    rio::PrimitiveRenderer::instance()->setModelMatrix(rio::Matrix34f::ident);

    mBgRenderer.setCamera(&mCamera);
    mBgRenderer.setProjection(&mProjection);

#if RIO_IS_WIN
    mpKeyboardMouseDevice = static_cast<rio::KeyboardMouseDevice*>(rio::ControllerMgr::instance()->getControlDevice(rio::ControllerDefine::DEVICE_KEYBOARD_MOUSE));
    RIO_ASSERT(mpKeyboardMouseDevice);
#endif // RIO_IS_WIN

    updateCursorPos_();
    mLastCursorPos = mCursorPos;

    mCourseData.loadFromPack(level_path);
    if (mCourseData.getFile(0))
        setCurrentCourseDataFile(0);
}

void MainWindow::setCurrentCourseDataFile(u32 id)
{
    // Clear items
    mSpriteItem.clear();
    mNextGotoItem.clear();
    mLocationItem.clear();
    mAreaItem.clear();

    Bg& bg = mCourseData.getBg();

    if (!mCourseData.getFile(id))
    {
        mCurrentFile = -1;

        // Clear BG
        bg.clearBgCourseData();
        mBgRenderer.createVertexBuffer(bg);

        return;
    }

    mCurrentFile = id;
    CourseDataFile& cd_file = *mCourseData.getFile(id);

    bg.processBgCourseData(cd_file);
    mBgRenderer.createVertexBuffer(bg);

    for (Sprite& sprite : cd_file.getSprite())
        mSpriteItem.emplace_back(sprite);

    for (NextGoto& next_goto : cd_file.getNextGoto())
        mNextGotoItem.emplace_back(next_goto);

    for (Location& location : cd_file.getLocation())
        mLocationItem.emplace_back(location);

    for (AreaData& area : cd_file.getAreaData())
        mAreaItem.emplace_back(area);

    const NextGoto* start_next_goto = nullptr;
  //if (!start_next_goto)
    {
        u8 start = cd_file.getOptions().start_next_goto;
        for (const NextGoto& next_goto : cd_file.getNextGoto())
        {
            if (next_goto.id == start)
            {
                start_next_goto = &next_goto;
                break;
            }
        }
    }

    if (!start_next_goto)
    {
        u8 start = cd_file.getOptions().start_next_goto_coin_boost;
        for (const NextGoto& next_goto : cd_file.getNextGoto())
        {
            if (next_goto.id == start)
            {
                start_next_goto = &next_goto;
                break;
            }
        }
    }

    rio::BaseVec2f& camera_pos = mCamera.pos();

    if (start_next_goto)
    {
        const f32 window_w = s32(rio::Window::instance()->getWidth());
        const f32 window_h = s32(rio::Window::instance()->getHeight());

        const f32 window_w_2 = window_w / (2 * mCamera.getZoomScale());
        const f32 window_h_2 = window_h / (2 * mCamera.getZoomScale());

        camera_pos.x =  (f32(start_next_goto->offset.x + 8 + start_next_goto->camera_offset.x) - window_w_2);
        camera_pos.y = -(f32(start_next_goto->offset.y + 8 + start_next_goto->camera_offset.y) - window_h_2);
    }
    else
    {
        camera_pos.x = 0.0f;
        camera_pos.y = 0.0f;
    }
}

/*
bool MainWindow::checkButtonPress(u32 idx, rio::Controller::PadIdx button)
{
    if (rio::ControllerMgr::instance()->getMainController()->isHold(1 << button))
        mHoldCounter[idx]++;

    else
    {
        mHoldCounter[idx] = 0;
        if (mWaitForRelease[idx])
            mWaitForRelease[idx] = false;
    }

    if (!mWaitForRelease[idx] && mHoldCounter[idx] >*//*= 60 * 3*//* 0)
    {
        mWaitForRelease[idx] = true;
        return true;
    }

    return false;
}
*/

void MainWindow::calc_()
{
    updateCursorPos_();
    processInputs_();

    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << /* LAYER_0, */ rio::Controller::PAD_IDX_X))
        mLayerShown[LAYER_0] = !mLayerShown[LAYER_0];

    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << /* LAYER_1, */ rio::Controller::PAD_IDX_Y))
        mLayerShown[LAYER_1] = !mLayerShown[LAYER_1];

    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << /* LAYER_2, */ rio::Controller::PAD_IDX_B))
        mLayerShown[LAYER_2] = !mLayerShown[LAYER_2];

    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << /* 3, */ rio::Controller::PAD_IDX_A))
    {
        if (mCurrentFile != -1)
        {
            s32 prev_file = mCurrentFile;

            while ((mCurrentFile = (mCurrentFile + 1) % CD_FILE_MAX_NUM), !mCourseData.getFile(mCurrentFile))
                continue;

            if (mCurrentFile != prev_file)
                setCurrentCourseDataFile(mCurrentFile);
        }
    }

    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << /* 4, */ rio::Controller::PAD_IDX_START))
        mBlendEnable = !mBlendEnable;

    rio::Window::instance()->clearColor(
        119 / 255.f,
        136 / 255.f,
        153 / 255.f
    );
    rio::Window::instance()->clearDepthStencil();

    rio::PrimitiveRenderer::instance()->setCamera(mCamera);

    if (mCurrentFile != -1)
    {
        const Bg& bg = mCourseData.getBg();
        const CourseDataFile& cd_file = *mCourseData.getFile(mCurrentFile);

        rio::RenderState render_state;
        render_state.setBlendEnable(mBlendEnable);
        render_state.apply();

        if (mLayerShown[LAYER_2])
            mBgRenderer.render(LAYER_2, bg, cd_file);

        if (mLayerShown[LAYER_1])
            mBgRenderer.render(LAYER_1, bg, cd_file);

        for (const auto& item : mSpriteItem)
            item.draw();

        for (const auto& item : mNextGotoItem)
            item.draw();

        for (const auto& item : mLocationItem)
            item.draw();

        if (mLayerShown[LAYER_0])
            mBgRenderer.render(LAYER_0, bg, cd_file);

        for (const auto& item : mAreaItem)
            item.draw();
    }

    drawCursor_();
}

void MainWindow::drawCursor_()
{
    const rio::Vector2f& cursor_pos = getCursorWorldPos();

    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::PrimitiveRenderer::instance()->drawQuad(
            rio::PrimitiveRenderer::QuadArg()
                .setColor(rio::Color4f::cRed, rio::Color4f::cBlue)
                .setCenter({ cursor_pos.x, cursor_pos.y, -mProjection.getNear() + 10000.0f })
                .setSize({ 16.0f, 16.0f })
        );
    }
    rio::PrimitiveRenderer::instance()->end();
}

void MainWindow::exit_()
{
#if RIO_IS_WIN
    mpKeyboardMouseDevice = nullptr;
#endif // RIO_IS_WIN
}
