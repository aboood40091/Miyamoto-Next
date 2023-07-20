#include <MainWindow.h>

#include <controller/rio_ControllerMgr.h>
#include <filedevice/rio_FileDevice.h>
#include <gfx/rio_PrimitiveRenderer.h>
#include <gfx/rio_Window.h>
#include <gfx/lyr/rio_Renderer.h>
#include <gpu/rio_RenderState.h>
#include <misc/rio_MemUtil.h>

#if RIO_IS_WIN
#include <graphics/win/ShaderUtil.h>
#endif // RIO_IS_WIN

#if RIO_IS_CAFE
#include <detail/aglGX2.h>
#endif // RIO_IS_CAFE

#include <detail/aglShaderHolder.h>
#include <resource/SZSDecompressor.h>
#include <utility/aglPrimitiveShape.h>
#include <utility/aglPrimitiveTexture.h>
#include <utility/aglVertexAttributeHolder.h>

#include <distant_view/DistantViewMgr.h>
#include <graphics/ShaderHolder.h>

static const char* level_fname = "1-1.szs";
static const std::string nsmbu_content_path = "game/nsmbu";

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

    if (!rio::ControllerMgr::instance()->getMainPointer()->isPointerOn())
        return;

    mCursorPos = rio::ControllerMgr::instance()->getMainPointer()->getPointer();

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

    if (rio::ControllerMgr::instance()->getMainPointer()->isPointerOnNow())
        mLastCursorPos = mCursorPos;
}

void MainWindow::processInputs_()
{
    if (rio::ControllerMgr::instance()->getMainPointer()->isHold(1 << rio::Controller::PAD_IDX_TOUCH))
    {
        static_cast<rio::Vector2f&>(mCamera.pos()) +=
            viewToWorldPos(mLastCursorPos) - viewToWorldPos(mCursorPos);
    }
}

void MainWindow::prepare_()
{
  //RIO_LOG("MainWindow::prepare_(): start\n");

    mLayer[SCENE_LAYER_DISTANT_VIEW].it = rio::lyr::Renderer::instance()->addLayer("DistantView", SCENE_LAYER_DISTANT_VIEW);
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr = rio::lyr::Layer::peelIterator(mLayer[SCENE_LAYER_DISTANT_VIEW].it);
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->setClearColor({
        119 / 255.f,
        136 / 255.f,
        153 / 255.f
    });
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->setClearDepthStencil();
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addRenderStep("Calc");
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addRenderStep("CalcGPU");
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addRenderStep("Opa");
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addRenderStep("Xlu");
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addRenderStep("PostFx");
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addDrawMethod(0, rio::lyr::DrawMethod(this, &MainWindow::dv_CalcMdl_));
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addDrawMethod(1, rio::lyr::DrawMethod(this, &MainWindow::dv_CalcGPU_));
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addDrawMethod(2, rio::lyr::DrawMethod(this, &MainWindow::dv_DrawOpa_));
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addDrawMethod(3, rio::lyr::DrawMethod(this, &MainWindow::dv_DrawXlu_));
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr->addDrawMethod(4, rio::lyr::DrawMethod(this, &MainWindow::dv_PostFx_));

    mLayer[SCENE_LAYER_BG].it = rio::lyr::Renderer::instance()->addLayer("BG", SCENE_LAYER_BG);
    mLayer[SCENE_LAYER_BG].ptr = rio::lyr::Layer::peelIterator(mLayer[SCENE_LAYER_BG].it);
    mLayer[SCENE_LAYER_BG].ptr->addRenderStep("Render");
    mLayer[SCENE_LAYER_BG].ptr->addDrawMethod(0, rio::lyr::DrawMethod(this, &MainWindow::bg_Render_));

  //RIO_LOG("MainWindow::prepare_(): layer initialized\n");

#if RIO_IS_WIN
    ShaderUtil::sTempPath                   = rio::FileDeviceMgr::instance()->getNativeFileDevice()->getCWD() + "/fs/content/shaders/cache";
    ShaderUtil::sGx2ShaderDecompilerPath    = rio::FileDeviceMgr::instance()->getNativeFileDevice()->getCWD() + "/fs/content/gx2shader-decompiler.exe";
    ShaderUtil::sSpirvCrossPath             = rio::FileDeviceMgr::instance()->getNativeFileDevice()->getCWD() + "/fs/content/spirv-cross.exe";

  //RIO_LOG("MainWindow::prepare_(): ShaderUtil parameters set\n");
#endif // RIO_IS_WIN

#if RIO_IS_CAFE
    agl::driver::GX2Resource::createSingleton();
  //RIO_LOG("MainWindow::prepare_(): agl::driver::GX2Resource::createSingleton() done\n");
    agl::driver::GX2Resource::instance()->initialize();
  //RIO_LOG("MainWindow::prepare_(): agl::driver::GX2Resource::instance()->initialize() done\n");
#endif // RIO_IS_CAFE

    agl::detail::ShaderHolder::createSingleton();
  //RIO_LOG("MainWindow::prepare_(): agl::detail::ShaderHolder::createSingleton() done\n");
#if RIO_IS_CAFE
    agl::detail::ShaderHolder::instance()->setCreateDisplayLists(true);
#endif // RIO_IS_CAFE

    agl::utl::PrimitiveShape::createSingleton();
  //RIO_LOG("MainWindow::prepare_(): agl::utl::PrimitiveShape::createSingleton() done\n");
    agl::utl::PrimitiveShape::instance()->initialize();
  //RIO_LOG("MainWindow::prepare_(): agl::utl::PrimitiveShape::instance()->initialize() done\n");

    agl::utl::PrimitiveTexture::createSingleton();
    agl::utl::PrimitiveTexture::instance()->initialize();
  //agl::utl::PrimitiveVertex::createSingleton();
  //agl::utl::PrimitiveVertex::instance()->initialize();

    rio::FileDevice::LoadArg arg;
    arg.path =
#if RIO_IS_CAFE
        nsmbu_content_path + "/CAFE/agl_resource_cafe.sarc";
#else
        "agl_resource_cafe_dev.sarc";
#endif
    arg.alignment = 0x2000;

    mpArchive = rio::FileDeviceMgr::instance()->load(arg);
    RIO_ASSERT(mpArchive);

    mArchiveRes.prepareArchive(mpArchive);
  //RIO_LOG("MainWindow::prepare_(): mArchiveRes.prepareArchive() done\n");

    agl::detail::ShaderHolder::instance()->initialize(&mArchiveRes);

  //RIO_LOG("Initialized shader holder\n");

    agl::utl::VertexAttributeHolder::createSingleton();
    agl::utl::VertexAttributeHolder::instance()->initialize();

  //RIO_LOG("Initialized agl!\n");

    ShaderHolder::createSingleton();
    ShaderHolder::instance()->initialize(nsmbu_content_path + "/Common/shader/shaderfb");

  //RIO_LOG("Initialized ShaderHolder\n");

    DistantViewMgr::createSingleton();
    DistantViewMgr::instance()->setFlickerEnable(false);

  //RIO_LOG("Created DistantViewMgr\n");

    mBlendEnable = true;
    mLayerShown[LAYER_0] = true;
    mLayerShown[LAYER_1] = true;
    mLayerShown[LAYER_2] = true;

    setZoomTileSize(24);
  //RIO_LOG("Zoom: %f\n", mBgZoom);

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

    updateCursorPos_();
    mLastCursorPos = mCursorPos;


    const std::string& level_path = nsmbu_content_path + "/Common/course_res_pack/" + level_fname;
    mCourseData.loadFromPack(level_path);
    setCurrentCourseDataFile(0);
}

void MainWindow::exit_()
{
    DistantViewMgr::destroySingleton();

    ShaderHolder::destroySingleton();

    agl::utl::VertexAttributeHolder::destroySingleton();

    agl::utl::PrimitiveTexture::destroySingleton();
  //agl::utl::PrimitiveVertex::destroySingleton();

    agl::utl::PrimitiveShape::destroySingleton();

    agl::detail::ShaderHolder::destroySingleton();

    mArchiveRes.destroy();

    rio::MemUtil::free(mpArchive);
    mpArchive = nullptr;

#if RIO_IS_CAFE
    agl::driver::GX2Resource::destroySingleton();
#endif // RIO_IS_CAFE
}

void MainWindow::setCurrentCourseDataFile(u32 id)
{
    // Clear items
    mSpriteItem.clear();
    mNextGotoItem.clear();
    mLocationItem.clear();
    mAreaItem.clear();

    Bg& bg = mCourseData.getBg();

    mDVControlArea = -1;

    if (!mCourseData.getFile(id))
    {
        mCurrentFile = -1;

        // Clear BG
        bg.clearBgCourseData();
        mBgRenderer.createVertexBuffer(bg);

        const char* dv_name = "Nohara";

        const std::string& dv_path = nsmbu_content_path + "/Common/distant_view";
        RIO_LOG("DV Path: \"%s\", DV Name: \"%s\"\n", dv_path.c_str(), dv_name);

        DistantViewMgr::instance()->initialize(dv_name, dv_path);

      //RIO_LOG("Initialized DistantViewMgr\n");

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

    const char* dv_name = nullptr;

    if (start_next_goto)
    {
        const f32 window_w = s32(rio::Window::instance()->getWidth());
        const f32 window_h = s32(rio::Window::instance()->getHeight());

        const f32 window_w_2 = window_w / (2 * mCamera.getZoomScale());
        const f32 window_h_2 = window_h / (2 * mCamera.getZoomScale());

        camera_pos.x =  (f32(start_next_goto->offset.x + 8 + start_next_goto->camera_offset.x) - window_w_2);
        camera_pos.y = -(f32(start_next_goto->offset.y + 8 + start_next_goto->camera_offset.y) - window_h_2);

        if (cd_file.getAreaData().size() > 0)
        {
          //RIO_ASSERT(start_next_goto->area >= 0 && start_next_goto->area < cd_file.getAreaData().size());
            u8 area =
                (start_next_goto->area >= 0 && start_next_goto->area < cd_file.getAreaData().size())
                    ? start_next_goto->area
                    : 0;

            const AreaData& area_data = cd_file.getAreaData()[area];

          //RIO_ASSERT(area_data.bg2 >= 0 && area_data.bg2 < cd_file.getDistantViewData().size());
            if (area_data.bg2 >= 0 && area_data.bg2 < cd_file.getDistantViewData().size())
            {
                const DistantViewData& dv_data = cd_file.getDistantViewData()[area_data.bg2];
                dv_name = dv_data.name;
                mDVControlArea = area;
            }
            else
            {
                dv_name = "Nohara";
            }
        }
        else
        {
            dv_name = "Nohara";
        }
    }
    else
    {
        camera_pos.x = 0.0f;
        camera_pos.y = 0.0f;

        if (cd_file.getAreaData().size() > 0)
        {
            const AreaData& area_data = cd_file.getAreaData()[0];

            RIO_ASSERT(area_data.bg2 >= 0 && area_data.bg2 < cd_file.getDistantViewData().size());
            const DistantViewData& dv_data = cd_file.getDistantViewData()[area_data.bg2];

            dv_name = dv_data.name;
            mDVControlArea = 0;
        }
        else
        {
            dv_name = "Nohara";
        }
    }

    RIO_ASSERT(dv_name != nullptr);

    const std::string& dv_path = nsmbu_content_path + "/Common/distant_view";
    RIO_LOG("DV Path: \"%s\", DV Name: \"%s\"\n", dv_path.c_str(), dv_name);

    const f32 screen_world_h = 224 * mBgZoom;
    const f32 screen_world_w = screen_world_h * 16 / 9;

    rio::BaseVec2f bg_pos;
    f32 bg_offset_area_bottom_to_screen_bottom;
    if (mDVControlArea != -1)
    {
        const AreaData& area_data = cd_file.getAreaData()[mDVControlArea];

        const f32 x =  s32(area_data.offset.x);
        const f32 y = -s32(area_data.offset.y);
        const f32 w =  s32(area_data.  size.x);
        const f32 h =  s32(area_data.  size.y);

        bg_pos.x = x + w * 0.5f;
        bg_pos.y = y - h * 0.5f;

        const f32 screen_world_bottom = camera_pos.y - screen_world_h;

        bg_offset_area_bottom_to_screen_bottom = screen_world_bottom - (y - h);
    }
    else
    {
        bg_pos.x = 0.0f;
        bg_pos.y = 0.0f;
        bg_offset_area_bottom_to_screen_bottom = 0;
    }

    DistantViewMgr::instance()->initialize(
        dv_name, dv_path,
        bg_pos,
        static_cast<const rio::Vector2f&>(camera_pos) + rio::Vector2f{ screen_world_w * 0.5f, -screen_world_h * 0.5f },
        bg_offset_area_bottom_to_screen_bottom,
        mBgZoom
    );

  //RIO_LOG("Initialized DistantViewMgr\n");
}

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

    const rio::BaseVec2f& camera_pos = mCamera.pos();

    const f32 screen_world_h = 224 * mBgZoom;
    const f32 screen_world_w = screen_world_h * 16 / 9;

    f32 bg_offset_area_bottom_to_screen_bottom = 0.0f;
    if (/* mCurrentFile != -1 && */ mDVControlArea != -1)
    {
        RIO_ASSERT(mCurrentFile != -1);
        const CourseDataFile& cd_file = *mCourseData.getFile(mCurrentFile);
        const AreaData& area_data = cd_file.getAreaData()[mDVControlArea];

        const f32 y = -s32(area_data.offset.y);
        const f32 h =  s32(area_data.  size.y);

        const f32 screen_world_bottom = camera_pos.y - screen_world_h;

        bg_offset_area_bottom_to_screen_bottom = screen_world_bottom - (y - h);
    }

    DistantViewMgr::instance()->update(
        static_cast<const rio::Vector2f&>(camera_pos) + rio::Vector2f{ screen_world_w * 0.5f, -screen_world_h * 0.5f },
        bg_offset_area_bottom_to_screen_bottom,
        mBgZoom
    );
}

rio::BaseVec2f MainWindow::worldToScreenPos(const rio::BaseVec2f& pos) const
{
    const rio::Vector2f& pos_vec = static_cast<const rio::Vector2f&>(pos);
    const rio::Vector2f& camera_pos = static_cast<const rio::Vector2f&>(mCamera.pos());

    const f32 screen_world_h = 224 * mBgZoom;
    const f32 screen_world_w = screen_world_h * 16 / 9;

    return (pos_vec - camera_pos) * (rio::Vector2f{ /* s32(rio::Window::instance()->getWidth()) */ 1280.0f, /* s32(rio::Window::instance()->getHeight()) */ 720.0f } / rio::Vector2f{ screen_world_w, -screen_world_h });
}

void MainWindow::dv_CalcMdl_(const rio::lyr::DrawInfo& draw_info)
{
    mDrawDV = true;
    mRestoreScissor = false;

    if (/* mCurrentFile != -1 && */ mDVControlArea != -1)
    {
        mDrawDV = false;

        RIO_ASSERT(mCurrentFile != -1);

        const CourseDataFile& cd_file = *mCourseData.getFile(mCurrentFile);
        const AreaData& area_data = cd_file.getAreaData()[mDVControlArea];

        const f32 x =  s32(area_data.offset.x);
        const f32 y = -s32(area_data.offset.y);
        const f32 w =  s32(area_data.  size.x);
        const f32 h =  s32(area_data.  size.y);

        const rio::BaseVec2f& camera_pos = mCamera.pos();

        const f32 screen_world_h = 224 * mBgZoom;
        const f32 screen_world_w = screen_world_h * 16 / 9;

        const rio::BaseVec2f screen_world_min {
            camera_pos.x,
            camera_pos.y - screen_world_h
        };

        const rio::BaseVec2f screen_world_max {
            camera_pos.x + screen_world_w,
            camera_pos.y
        };

        const rio::BaseVec2f area_world_min {
            x,
            y - h
        };

        const rio::BaseVec2f area_world_max {
            x + w,
            y
        };

        if (screen_world_min.x < area_world_max.x && area_world_min.x < screen_world_max.x &&
            screen_world_min.y < area_world_max.y && area_world_min.y < screen_world_max.y)
        {
            const rio::BaseVec2f visible_area_world_min {
                std::max<f32>(screen_world_min.x, area_world_min.x),
                std::max<f32>(screen_world_min.y, area_world_min.y)
            };

            const rio::BaseVec2f visible_area_world_max {
                std::min<f32>(screen_world_max.x, area_world_max.x),
                std::min<f32>(screen_world_max.y, area_world_max.y)
            };

            const rio::BaseVec2f& visible_area_min = worldToScreenPos(visible_area_world_min);
            const rio::BaseVec2f& visible_area_max = worldToScreenPos(visible_area_world_max);

            rio::Graphics::setScissor(visible_area_min.x, visible_area_max.y, visible_area_max.x - visible_area_min.x, visible_area_min.y - visible_area_max.y);

            mDrawDV = true;
            mRestoreScissor = true;
        }
    }

    if (mDrawDV)
        DistantViewMgr::instance()->calcMdl();
}

void MainWindow::dv_CalcGPU_(const rio::lyr::DrawInfo& draw_info)
{
    if (mDrawDV)
        DistantViewMgr::instance()->calcGPU();
}

void MainWindow::dv_DrawOpa_(const rio::lyr::DrawInfo& draw_info)
{
    if (mDrawDV)
        DistantViewMgr::instance()->drawOpa();
}

void MainWindow::dv_DrawXlu_(const rio::lyr::DrawInfo& draw_info)
{
    if (mDrawDV)
        DistantViewMgr::instance()->drawXlu();
}

void MainWindow::dv_PostFx_(const rio::lyr::DrawInfo& draw_info)
{
    if (mDrawDV)
    {
        if (mRestoreScissor)
            rio::Graphics::setScissor(0, 0, /* s32(rio::Window::instance()->getWidth()) */ 1280, /* s32(rio::Window::instance()->getHeight()) */ 720);

        DistantViewMgr::instance()->applyDepthOfField();
    }
}

void MainWindow::bg_Render_(const rio::lyr::DrawInfo&)
{
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
