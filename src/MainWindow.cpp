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

#include <actor/ActorCreateMgr.h>
#include <course/BgTexMgr.h>
#include <course/CoinOrigin.h>
#include <distant_view/DistantViewMgr.h>
#include <graphics/Renderer.h>
#include <graphics/ShaderHolder.h>

#if RIO_IS_CAFE
#include <gx2/event.h>
#endif // RIO_IS_CAFE

static const char* level_fname = "1-1.szs";
static const std::string nsmbu_content_path = "game/nsmbu";

MainWindow::MainWindow()
    : rio::ITask("Miyamoto! Next")
    , m3DDrawCallback(*this)
{
    rio::MemUtil::set(mLayer, 0, sizeof(mLayer));
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

    mLayer[SCENE_LAYER_GATHER].it = rio::lyr::Renderer::instance()->addLayer("Gather", SCENE_LAYER_GATHER);
    mLayer[SCENE_LAYER_GATHER].ptr = rio::lyr::Layer::peelIterator(mLayer[SCENE_LAYER_GATHER].it);
    mLayer[SCENE_LAYER_GATHER].ptr->addRenderStep("Gather");
    mLayer[SCENE_LAYER_GATHER].ptr->addDrawMethod(0, rio::lyr::DrawMethod(this, &MainWindow::gather_));

    mLayer[SCENE_LAYER_GATHER].ptr->setClearColor({
        119 / 255.f,
        136 / 255.f,
        153 / 255.f
    });
    mLayer[SCENE_LAYER_GATHER].ptr->setClearDepthStencil();

    mLayer[SCENE_LAYER_DISPOSE].it = rio::lyr::Renderer::instance()->addLayer("Dispose", SCENE_LAYER_DISPOSE);
    mLayer[SCENE_LAYER_DISPOSE].ptr = rio::lyr::Layer::peelIterator(mLayer[SCENE_LAYER_DISPOSE].it);
    mLayer[SCENE_LAYER_DISPOSE].ptr->addRenderStep("Dispose");
    mLayer[SCENE_LAYER_DISPOSE].ptr->addDrawMethod(0, rio::lyr::DrawMethod(this, &MainWindow::dispose_));

    mLayer[SCENE_LAYER_DISTANT_VIEW].it = rio::lyr::Renderer::instance()->addLayer<RenderObjLayer>("DistantView", SCENE_LAYER_DISTANT_VIEW);
    mLayer[SCENE_LAYER_DISTANT_VIEW].ptr = rio::lyr::Layer::peelIterator(mLayer[SCENE_LAYER_DISTANT_VIEW].it);
    getDistantViewLayer()->initialize();
    getDistantViewLayer()->setRenderMgr(&mDVRenderMgr);
    getDistantViewLayer()->addDrawMethod(RenderObjLayer::cRenderStep_PostFx, rio::lyr::DrawMethod(this, &MainWindow::dv_PostFx_));

    mLayer[SCENE_LAYER_3D].it = rio::lyr::Renderer::instance()->addLayer<RenderObjLayer>("3D", SCENE_LAYER_3D);
    mLayer[SCENE_LAYER_3D].ptr = rio::lyr::Layer::peelIterator(mLayer[SCENE_LAYER_3D].it);
    get3DLayer()->initialize();
    get3DLayer()->setRenderMgr(&m3DRenderMgr);
    m3DRenderMgr.setDrawCallback(&m3DDrawCallback);

    mLayer[SCENE_LAYER_BG_PREPARE].it = rio::lyr::Renderer::instance()->addLayer<RenderObjLayer>("BgPrepare", SCENE_LAYER_BG_PREPARE);
    mLayer[SCENE_LAYER_BG_PREPARE].ptr = rio::lyr::Layer::peelIterator(mLayer[SCENE_LAYER_BG_PREPARE].it);
    getBgPrepareLayer()->setRenderMgr(&mBgPrepareRenderMgr);

    BgTexMgr::createSingleton();

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

    Renderer::createSingleton();

  //RIO_LOG("Initialized Renderer\n");

    DistantViewMgr::createSingleton();
    DistantViewMgr::instance()->setFlickerEnable(false);

  //RIO_LOG("Created DistantViewMgr\n");

    mBlendEnable = true;
    mRenderNormal = false;
    mLayerShown[LAYER_0] = true;
    mLayerShown[LAYER_1] = true;
    mLayerShown[LAYER_2] = true;

  //setZoomTileSize(24);
  //RIO_LOG("Zoom: %f\n", mBgZoom);

    mProjection.set(
         1.0f,                                      // Near
         20000.0f,                                  // Far
         0.0f,                                      // Top
        -s32(rio::Window::instance()->getHeight()), // Bottom
         0.0f,                                      // Left
         s32(rio::Window::instance()->getWidth())   // Right
    );

    mBgRenderer.setCamera(&mCamera);
    mBgRenderer.setProjection(&mProjection);

    get3DLayer()->setCamera(&mCamera);
    get3DLayer()->setProjection(&mProjection);

    updateCursorPos_();
    mLastCursorPos = mCursorPos;

    CoinOrigin::createSingleton();
    ActorCreateMgr::createSingleton();

    const std::string& pack_arc_path = nsmbu_content_path + "/Common/actor/jyotyuActorPack.szs";
    CoinOrigin::instance()->initialize(pack_arc_path);

    const std::string& level_path = nsmbu_content_path + "/Common/course_res_pack/" + level_fname;
    mCourseData.loadFromPack(level_path);
    setCurrentCourseDataFile(0);
}

void MainWindow::exit_()
{
    ActorCreateMgr::destroySingleton();
    CoinOrigin::destroySingleton();

    DistantViewMgr::destroySingleton();

    Renderer::destroySingleton();

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

    BgTexMgr::destroySingleton();
}

namespace {

static f32 GetZoomMult(u32 zoom_type, u8 zoom_id)
{
    static const f32 FLOAT_ARRAY_1022ced0[12] = {
        1.0000000f,
        1.0000000f,
        1.0000000f,
        1.4285715f,
        1.3571428f,
        1.2142857f,
        1.2142857f,
        1.2142857f,
        0.5000000f,
        1.2142857f,
        1.2142857f,
        1.4285715f
    };

    static const f32 FLOAT_ARRAY_1022d020[9] = {
        1.0f,
        1.0f,
        1.0f,
        1.3571428f,
        1.3571428f,
        1.3571428f,
        1.2142857f,
        1.2142857f,
        1.2142857f
    };

    static const f32 FLOAT_ARRAY_1022cea8[10] = {
        1.0000000f,
        1.3571428f,
        1.7142857f,
        2.0000000f,
        1.2142857f,
        1.4285715f,
        1.1428572f,
        2.0000000f,
        0.5000000f,
        0.7500000f
    };

    switch (zoom_type)
    {
    case 0:
    case 1:
    case 6:
    case 7:
        return FLOAT_ARRAY_1022ced0[zoom_id >= 12 ? 0 : zoom_id];
    case 2:
        return FLOAT_ARRAY_1022d020[zoom_id >= 9 ? 0 : zoom_id];
    case 3:
    case 4:
    case 5:
    default:
        return FLOAT_ARRAY_1022cea8[zoom_id >= 10 ? 0 : zoom_id];
    }
}

}

void MainWindow::setCurrentCourseDataFile(u32 id)
{
#if RIO_IS_CAFE
    GX2DrawDone();
#elif RIO_IS_WIN
    RIO_GL_CALL(glFinish());
#endif

    // Clear items
    mMapActorItemPtr.clear();
    mNextGotoItem.clear();
    mLocationItem.clear();
    mAreaItem.clear();

    BgTexMgr::instance()->destroy(getBgPrepareLayer());

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

    BgTexMgr::instance()->initialize(bg, cd_file, getBgPrepareLayer());
    CoinOrigin::instance()->pushBackDrawMethod(getBgPrepareLayer());

    for (MapActorData& map_actor_data : cd_file.getMapActorData())
        mMapActorItemPtr.emplace_back(ActorCreateMgr::instance()->create(map_actor_data));

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

    u8 area;

    if (cd_file.getAreaData().size() > 0)
    {
        if (start_next_goto)
        {
          //RIO_ASSERT(start_next_goto->area >= 0 && start_next_goto->area < cd_file.getAreaData().size());
            area =
                (start_next_goto->area >= 0 && start_next_goto->area < cd_file.getAreaData().size())
                    ? start_next_goto->area
                    : 0;
        }
        else
        {
            area = 0;
        }

        const AreaData& area_data = cd_file.getAreaData()[area];

      //RIO_ASSERT(area_data.bg2 >= 0 && area_data.bg2 < cd_file.getDistantViewData().size());
        if (area_data.bg2 >= 0 && area_data.bg2 < cd_file.getDistantViewData().size())
        {
            const DistantViewData& dv_data = cd_file.getDistantViewData()[area_data.bg2];
            dv_name = dv_data.name;
            mDVControlArea = area;

            const f32 w = s32(area_data.size.x);
            const f32 h = s32(area_data.size.y);

            setZoom(
                std::min<f32>(
                    std::min<f32>(
                        std::min<f32>(
                            w / 398.22222222222222f,
                            h / 224.0f
                        ),
                        2.0f
                    ),
                    GetZoomMult(area_data.zoom_type, area_data.zoom_id)
                )
            );
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
        bg_pos.y = (y - h) + 0.5f * mBgZoom * 224.0f;

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

    if (rio::ControllerMgr::instance()->getMainController()->isTrig(1 << /* 5, */ rio::Controller::PAD_IDX_SELECT))
        mRenderNormal = !mRenderNormal;

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
        getDistantViewLayer(),
        static_cast<const rio::Vector2f&>(camera_pos) + rio::Vector2f{ screen_world_w * 0.5f, -screen_world_h * 0.5f },
        bg_offset_area_bottom_to_screen_bottom,
        mBgZoom
    );

    calcDistantViewScissor_();

    BgTexMgr::instance()->update();
    CoinOrigin::instance()->update();
}

rio::BaseVec2f MainWindow::worldToScreenPos(const rio::BaseVec2f& pos) const
{
    const rio::Vector2f& pos_vec = static_cast<const rio::Vector2f&>(pos);
    const rio::Vector2f& camera_pos = static_cast<const rio::Vector2f&>(mCamera.pos());

    const f32 screen_world_h = 224 * mBgZoom;
    const f32 screen_world_w = screen_world_h * 16 / 9;

    return (pos_vec - camera_pos) * (rio::Vector2f{ /* s32(rio::Window::instance()->getWidth()) */ 1280.0f, /* s32(rio::Window::instance()->getHeight()) */ 720.0f } / rio::Vector2f{ screen_world_w, -screen_world_h });
}

void MainWindow::calcDistantViewScissor_()
{
    getDistantViewLayer()->resetScissor();

    mDrawDV = true;

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

            getDistantViewLayer()->setScissor(visible_area_min.x, visible_area_max.y, visible_area_max.x - visible_area_min.x, visible_area_min.y - visible_area_max.y);

            mDrawDV = true;
        }
    }
}

void MainWindow::gather_(const rio::lyr::DrawInfo&)
{
    if (mDrawDV)
        DistantViewMgr::instance()->draw(getDistantViewLayer());

    CoinOrigin::instance()->draw(getBgPrepareLayer());

    Renderer::instance()->setLayer(get3DLayer());
    {
        for (std::unique_ptr<MapActorItem>& p_item : mMapActorItemPtr)
            p_item->scheduleDraw();
    }
    Renderer::instance()->resetLayer();

    mDVRenderMgr.calc();
    mBgPrepareRenderMgr.calc();
    m3DRenderMgr.calc();
}

void MainWindow::dispose_(const rio::lyr::DrawInfo&)
{
    mDVRenderMgr.clear();
    mBgPrepareRenderMgr.clear();
    m3DRenderMgr.clear();
}

void MainWindow::dv_PostFx_(const rio::lyr::DrawInfo& draw_info)
{
    if (mDrawDV)
        DistantViewMgr::instance()->applyDepthOfField();
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

void MainWindow::DrawCallback::preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void MainWindow::DrawCallback::preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void MainWindow::DrawCallback::postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    rio::PrimitiveRenderer::instance()->setCamera(mWindow.mCamera);
    rio::PrimitiveRenderer::instance()->setProjection(mWindow.mProjection);
    rio::PrimitiveRenderer::instance()->setModelMatrix(rio::Matrix34f::ident);

    rio::RenderState render_state;
    render_state.setBlendEnable(false);
    render_state.apply();

    if (mWindow.mCurrentFile != -1)
    {
        for (std::unique_ptr<MapActorItem>& p_item : mWindow.mMapActorItemPtr)
            if (p_item->getMapActorData().layer != LAYER_1)
                p_item->drawOpa(draw_info);

        for (std::unique_ptr<MapActorItem>& p_item : mWindow.mMapActorItemPtr)
            if (p_item->getMapActorData().layer == LAYER_1)
                p_item->drawOpa(draw_info);

        for (NextGotoItem& item : mWindow.mNextGotoItem)
            item.drawOpa();

        for (LocationItem& item : mWindow.mLocationItem)
            item.drawOpa();

        for (AreaItem& item : mWindow.mAreaItem)
            item.drawOpa();
    }

    mWindow.drawCursor_();
}

void MainWindow::DrawCallback::postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    s32 current_file = mWindow.mCurrentFile;
    if (current_file == -1)
        return;

    const CourseData& cd = mWindow.mCourseData;

    const Bg& bg = cd.getBg();
    const CourseDataFile& cd_file = *cd.getFile(current_file);

    rio::RenderState render_state;
    render_state.setBlendEnable(mWindow.mBlendEnable);
    render_state.apply();

    BgRenderer& bg_renderer = mWindow.mBgRenderer;
    bool render_normal = mWindow.mRenderNormal;
    const bool* layer_shown = mWindow.mLayerShown;

    bg_renderer.render(LAYER_2, bg, cd_file, layer_shown[LAYER_2], true, render_normal);

    rio::PrimitiveRenderer::instance()->setCamera(mWindow.mCamera);
    rio::PrimitiveRenderer::instance()->setProjection(mWindow.mProjection);
    rio::PrimitiveRenderer::instance()->setModelMatrix(rio::Matrix34f::ident);

    for (std::unique_ptr<MapActorItem>& p_item : mWindow.mMapActorItemPtr)
        if (p_item->getMapActorData().layer != LAYER_1)
            p_item->drawXlu(draw_info);

    bg_renderer.render(LAYER_1, bg, cd_file, layer_shown[LAYER_1], true, render_normal);

    for (std::unique_ptr<MapActorItem>& p_item : mWindow.mMapActorItemPtr)
        if (p_item->getMapActorData().layer == LAYER_1)
            p_item->drawXlu(draw_info);

    for (NextGotoItem& item : mWindow.mNextGotoItem)
        item.drawXlu();

    for (LocationItem& item : mWindow.mLocationItem)
        item.drawXlu();

    bg_renderer.render(LAYER_0, bg, cd_file, layer_shown[LAYER_0], true, render_normal);

    for (AreaItem& item : mWindow.mAreaItem)
        item.drawXlu();
}
