#pragma once

#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>
#include <resource/SharcArchiveRes.h>

#include <task/rio_Task.h>

#include <string>

#if RIO_IS_CAFE
#include <imgui_impl_gx2.h>
#endif // RIO_IS_CAFE

class CourseView;

class MainWindow : public rio::ITask, public rio::lyr::IDrawable
{
public:
    static const std::string& getContentPath();
    static bool forceSharcfb() { return true; }
    static f32 getBigItemScale() { return 16; }
    static bool useRealZoom() { return true; }
    static bool preserveTileSize() { return false; }    // Ignored if real zoom
    static bool applyDistantViewScissor() { return true; }

public:
    MainWindow();

    RenderObjLayer* getBgPrepareLayer() const
    {
        return static_cast<RenderObjLayer*>(mLayerBgPrepare.ptr);
    }

    void setCurrentCourseDataFile(u32 id);

private:
    void prepare_() override;
    void calc_()    override;
    void exit_()    override;

#if RIO_IS_WIN
    void resize_(s32 width, s32 height);
    static void onResizeCallback_(s32 width, s32 height);
#endif // RIO_IS_WIN

    void processMouseInput_();
    void processKeyboardInput_();

    void drawCourseViewUI_();
#if RIO_IS_WIN
    void drawMetricsUI_();
#endif // RIO_IS_WIN

    void gather_ (const rio::lyr::DrawInfo&);
    void dispose_(const rio::lyr::DrawInfo&);

private:
    struct Layer
    {
        Layer()
            : ptr(nullptr)
        {
        }

        rio::lyr::Layer::iterator it;
        rio::lyr::Layer* ptr;
    } mLayerGather, mLayerDispose, mLayerBgPrepare;

    struct Sharc
    {
        Sharc()
            : p_archive(nullptr)
        {
        }

        void* p_archive;
        SharcArchiveRes archive_res;
    } mAglRes, mJyotyuActorPack, mCobPack;

    CourseView*     mpCourseView;
    rio::BaseVec2f  mCourseViewPos;
    rio::BaseVec2i  mCourseViewSize;
    bool            mCourseViewResized;
    bool            mCourseViewHovered;
    bool            mCourseViewFocused;
    RenderMgr       mRenderMgrBgPrepare;
    s32             mCurrentFile;

#if RIO_IS_WIN
    s32                     mMetricsLocation;
#elif RIO_IS_CAFE
    ImGui_ImplGX2_Texture   mImGuiGX2Texture;
    GX2Sampler              mGX2Sampler;
#endif
};
