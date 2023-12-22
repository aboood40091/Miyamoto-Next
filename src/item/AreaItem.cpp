#include <CourseView.h>
#include <Globals.h>
#include <action/ActionItemDataChange.h>
#include <action/ActionMgr.h>
#include <graphics/LayerID.h>
#include <graphics/QuadRenderer.h>
#include <item/AreaItem.h>

#include <gfx/lyr/rio_Renderer.h>

#include <imgui.h>

static const rio::Color4f sColor{
    145 / 255.f,
    200 / 255.f,
    255 / 255.f,
    255 / 255.f,
};

static const rio::Color4f sMaskColor{
      0 / 255.f,
      0 / 255.f,
      0 / 255.f,
     48 / 255.f
};

static f32 GetZoomMult(u32 zoom_type, u8 zoom_id)
{
    static const SafeArray<f32, 12> FLOAT_ARRAY_1022ced0 = {
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

    static const SafeArray<f32, 9> FLOAT_ARRAY_1022d020 = {
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

    static const SafeArray<f32, 10> FLOAT_ARRAY_1022cea8 = {
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
        return FLOAT_ARRAY_1022ced0[zoom_id];
    case 2:
        return FLOAT_ARRAY_1022d020[zoom_id];
    case 3:
    case 4:
    case 5:
    default:
        return FLOAT_ARRAY_1022cea8[zoom_id];
    }
}

AreaItem::AreaItem(const AreaData& area_data, u32 index, const agl::RenderBuffer& render_buffer)
    : ItemBase(ITEM_TYPE_AREA, index, area_data.offset.x, area_data.offset.y)
    , mpRenderBufferDV(&render_buffer)
    , mDrawCallbackDV(index)
    , mpLayerDV(nullptr)
    , mDrawDV(true)
{
    const f32 x =  s32(area_data.offset.x);
    const f32 y = -s32(area_data.offset.y);
    const f32 w =  s32(area_data.  size.x);
    const f32 h =  s32(area_data.  size.y);

    mRealBgZoom =
        std::min<f32>(
            std::min<f32>(
                std::min<f32>(
                    w / 398.22222222222222f,
                    h / 224.0f
                ),
                2.0f
            ),
            GetZoomMult(area_data.zoom_type, area_data.zoom_id)
        );

    const DistantViewData* p_dv_data = CourseView::instance()->getCourseDataFile().getDistantViewDataByID(area_data.bg2);
  //RIO_ASSERT(p_dv_data != nullptr);
    if (p_dv_data == nullptr)
        return;

    RIO_ASSERT(index < 64);
    mLayerItrDV = rio::lyr::Renderer::instance()->addLayer<RenderObjLayer>("DistantView", LAYER_ID_DISTANT_VIEW_0 - index);
    mpLayerDV = rio::lyr::Layer::peelIterator(mLayerItrDV);
    getDistantViewLayer()->initialize();
    getDistantViewLayer()->addDrawMethod(RenderObjLayer::cRenderStep_PostFx, rio::lyr::DrawMethod(this, &AreaItem::dv_PostFx_));
    getDistantViewLayer()->setRenderMgr(&mRenderMgrDV);
    mRenderMgrDV.setDrawCallback(&mDrawCallbackDV);

    const std::string& dv_name = p_dv_data->name;
    const std::string& dv_path = Globals::getContentPath() + "/Common/distant_view";
    RIO_LOG("DV Path: \"%s\", DV Name: \"%s\"\n", dv_path.c_str(), dv_name.c_str());

    const rio::BaseVec2f bg_pos {
        x + w * 0.5f,
        (y - h) + 0.5f * mRealBgZoom * 224.0f
    };

    const rio::BaseVec2f& center_pos = CourseView::instance()->getCenterWorldPos();

    const rio::BaseVec2f bg_screen_center {
        std::clamp<f32>(center_pos.x, x, x + w),
        std::clamp<f32>(center_pos.y, y - h, y)
    };
    const f32 screen_world_bottom = std::clamp<f32>(center_pos.y - CourseView::instance()->getScreenWorldHalfHeight(), y - h, y);

    f32 bg_offset_area_bottom_to_screen_bottom = std::clamp<f32>(
        screen_world_bottom - (y - h),
        0.0f, h
    );

    mpDistantViewMgr = std::make_unique<DistantViewMgr>(*mpRenderBufferDV);
    mpDistantViewMgr->initialize(
        dv_name, dv_path,
        Globals::forceSharcfb(),
        bg_pos,
        bg_screen_center,
        bg_offset_area_bottom_to_screen_bottom,
        mRealBgZoom
    );

  //RIO_LOG("Initialized DistantViewMgr\n");
}

AreaItem::~AreaItem()
{
    if (mpLayerDV != nullptr)
    {
        rio::lyr::Renderer::instance()->removeLayer(mLayerItrDV);
        mpLayerDV = nullptr;
    }
}

void AreaItem::onSceneUpdate()
{
    if (!mpDistantViewMgr)
        return;

    const AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    const f32 x =  s32(area_data.offset.x);
    const f32 y = -s32(area_data.offset.y);
    const f32 w =  s32(area_data.  size.x);
    const f32 h =  s32(area_data.  size.y);

    const rio::BaseVec2f& center_pos = CourseView::instance()->getCenterWorldPos();

    const rio::BaseVec2f bg_screen_center {
        std::clamp<f32>(center_pos.x, x, x + w),
        std::clamp<f32>(center_pos.y, y - h, y)
    };
    const f32 screen_world_bottom = std::clamp<f32>(center_pos.y - CourseView::instance()->getScreenWorldHalfHeight(), y - h, y);

    f32 bg_offset_area_bottom_to_screen_bottom = std::clamp<f32>(
        screen_world_bottom - (y - h),
        0.0f, h
    );

    mpDistantViewMgr->update(
        getDistantViewLayer(),
        bg_screen_center,
        bg_offset_area_bottom_to_screen_bottom,
        mRealBgZoom
    );
}

void AreaItem::gather()
{
    if (mpDistantViewMgr)
    {
        if (Globals::applyDistantViewScissor())
            calcDistantViewScissor_();

        if (mDrawDV)
        {
            mpDistantViewMgr->draw(getDistantViewLayer());
            mRenderMgrDV.calc();
        }
    }
}

void AreaItem::dispose()
{
    mRenderMgrDV.clear();
}

void AreaItem::move(s16 dx, s16 dy, bool commit)
{
    AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    area_data.offset.x = mBasePosition.x + dx;
    area_data.offset.y = mBasePosition.y + dy;
    if (commit)
    {
        mBasePosition.x = area_data.offset.x;
        mBasePosition.y = area_data.offset.y;
    }
}

void AreaItem::drawOpa()
{
    const AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    rio::Vector3f offs { f32(area_data.offset.x), -f32(area_data.offset.y + area_data.size.y), getZPos_() + 10 };
    rio::Vector2f size { f32(area_data.size.x), f32(area_data.size.y) };

    QuadRenderer::instance()->drawBox(
        QuadRenderer::Arg(sColor)
            .setItemID(mItemID)
            .setSelection(mIsSelected)
            .setCornerAndSize(offs, size)
    );
}

void AreaItem::drawXlu()
{
    const AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    if (!(area_data.mask & 0x20))
        return;

    rio::Vector3f offs { f32(area_data.offset.x), -f32(area_data.offset.y + area_data.size.y), getZPos_() };
    rio::Vector2f size { f32(area_data.size.x), f32(area_data.size.y) };

    QuadRenderer::instance()->drawQuad(
        QuadRenderer::Arg(sMaskColor)
            .setCornerAndSize(offs, size)
    );
}

void AreaItem::onSelectionChange_()
{
    if (mIsSelected)
        mSelectionData = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];
}

void AreaItem::drawSelectionUI()
{
    const AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    ImGui::Text("Area");
    ImGui::Separator();

    const u8 single_step = 1; //Needed for +/- buttons to appear.

    ImGui::InputScalar("ID", ImGuiDataType_U8, &mSelectionData.id, &single_step);

    ImGui::Separator();
    ImGui::DragScalarN("Offset", ImGuiDataType_U16, &mSelectionData.offset, 2);
    ImGui::DragScalarN("Size", ImGuiDataType_U16, &mSelectionData.size, 2);

    ImGui::Separator();

    ImGui::InputScalar("Color OBJ (Unused)", ImGuiDataType_U16, &mSelectionData.color_obj);
    ImGui::InputScalar("Color BG (Unused)", ImGuiDataType_U16, &mSelectionData.color_bg);

    ImGui::Separator();

    ImGui::InputScalar("Scroll ID", ImGuiDataType_U8, &mSelectionData.scroll, &single_step);
    if (ImGui::BeginChild("Scroll Preview", ImVec2(0, 0), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_AutoResizeY))
    {
        if (ImGui::CollapsingHeader("Scroll Data (Preview)"))
        {
            const ScrollData* const p_scroll_data = CourseView::instance()->getCourseDataFile().getScrollDataByID(mSelectionData.scroll);
            if (p_scroll_data == nullptr)
                ImGui::TextDisabled("Invalid");

            else
            {
                ScrollData& scroll_data = *const_cast<ScrollData*>(p_scroll_data);
                ImGui::BeginDisabled();
                {
                  //ImGui::InputScalar("ID", ImGuiDataType_U16, &scroll_data.id);
                    ImGui::DragScalarN("Bound", ImGuiDataType_S32, &(scroll_data.bound[0]), 2);
                    ImGui::DragScalarN("Bound (Lakitu)", ImGuiDataType_S32, &(scroll_data.bound[1]), 2);
                    ImGui::InputScalar("Flags", ImGuiDataType_U16, &scroll_data.flag, nullptr, nullptr, "%04X");
                    ImGui::DragScalarN("Multiplayer Bound Adjust", ImGuiDataType_S16, &scroll_data.mp_bound_adjust, 2);
                }
                ImGui::EndDisabled();
            }
        }
    }
    ImGui::EndChild();

    ImGui::Separator();

    ImGui::InputScalar("Zoom Type", ImGuiDataType_U8, &mSelectionData.zoom_type);
    ImGui::InputScalar("Zoom ID", ImGuiDataType_U8, &mSelectionData.zoom_id);
    ImGui::InputScalar("Zoom Change", ImGuiDataType_U8, &mSelectionData.zoom_change);

    ImGui::Separator();

    ImGui::InputScalar("Mask No", ImGuiDataType_U8, &mSelectionData.mask);

    ImGui::Separator();

    ImGui::InputScalar("Distant View ID", ImGuiDataType_U8, &mSelectionData.bg2, &single_step);
    if (ImGui::BeginChild("DV Preview", ImVec2(0, 0), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_AutoResizeY))
    {
        if (ImGui::CollapsingHeader("Distant View Data (Preview)"))
        {
            const DistantViewData* const p_dv_data = CourseView::instance()->getCourseDataFile().getDistantViewDataByID(mSelectionData.bg2);
            if (p_dv_data == nullptr)
                ImGui::TextDisabled("Invalid");

            else
            {
                DistantViewData& dv_data = *const_cast<DistantViewData*>(p_dv_data);
                ImGui::BeginDisabled();
                {
                  //ImGui::InputScalar("ID", ImGuiDataType_U16, &dv_data.id);
                    ImGui::DragScalarN("Offset (Unused)", ImGuiDataType_S16, &dv_data.offset, 3);
                    ImGui::InputText("Name", dv_data.name, CD_FILE_DV_NAME_MAX_LEN + 1);
                    ImGui::InputScalar("Parallax Mode (Unused)", ImGuiDataType_U8, &dv_data.parallax_mode);
                }
                ImGui::EndDisabled();
            }
        }
    }
    ImGui::EndChild();
    ImGui::InputScalar("Unused 0x13", ImGuiDataType_U8, &mSelectionData.bg3);

    ImGui::Separator();

    ImGui::InputScalar("Direction", ImGuiDataType_U8, &mSelectionData.direction);

    ImGui::Separator();

    ImGui::InputScalar("Unknown 0x15", ImGuiDataType_U8, &mSelectionData._15);

    ImGui::Separator();

    ImGui::InputScalar("Bgm", ImGuiDataType_U8, &mSelectionData.bgm);
    ImGui::InputScalar("Bgm Mode", ImGuiDataType_U8, &mSelectionData.bgm_mode);

    ImGui::Separator();

    ImGui::InputScalar("Unused 0x18", ImGuiDataType_U8, &mSelectionData.dv);

    ImGui::Separator();

    ImGui::InputScalar("Flags", ImGuiDataType_U8, &mSelectionData.flag, nullptr, nullptr, "%02X");

    ImGui::Separator();

    if (ImGui::Button("Apply"))
    {
        const bool anything_modified = memcmp(&mSelectionData, &area_data, sizeof(AreaData)) != 0;

        if (anything_modified)
        {
            ActionItemDataChange::Context context {
                mItemID,
                std::static_pointer_cast<const void>(
                    std::make_shared<const AreaData>(area_data)
                ),
                std::static_pointer_cast<const void>(
                    std::make_shared<const AreaData>(mSelectionData)
                )
            };
            ActionMgr::instance()->pushAction<ActionItemDataChange>(&context);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Discard"))
        mSelectionData = area_data;
}

void AreaItem::calcDistantViewScissor_()
{
    mDrawDV = false;

    const AreaData& area_data = CourseView::instance()->getCourseDataFile().getAreaData()[mItemID.getIndex()];

    const f32 x =  s32(area_data.offset.x);
    const f32 y = -s32(area_data.offset.y);
    const f32 w =  s32(area_data.  size.x);
    const f32 h =  s32(area_data.  size.y);

    const rio::BaseVec2f& center_pos = CourseView::instance()->getCenterWorldPos();

    const f32 screen_world_w_half = CourseView::instance()->getScreenWorldHalfWidth();
    const f32 screen_world_h_half = CourseView::instance()->getScreenWorldHalfHeight();

    const rio::BaseVec2f screen_world_min {
        center_pos.x - screen_world_w_half,
        center_pos.y - screen_world_h_half
    };

    const rio::BaseVec2f screen_world_max {
        center_pos.x + screen_world_w_half,
        center_pos.y + screen_world_h_half
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

        const rio::BaseVec2f& visible_area_min = CourseView::instance()->worldToViewPos(visible_area_world_min);
        const rio::BaseVec2f& visible_area_max = CourseView::instance()->worldToViewPos(visible_area_world_max);

        s32 scissor_min_x = std::max<s32>(visible_area_min.x, 0);
        s32 scissor_min_y = std::max<s32>(visible_area_max.y, 0);

        s32 scissor_max_x = std::min<s32>(visible_area_max.x, mpRenderBufferDV->getSize().x);
        s32 scissor_max_y = std::min<s32>(visible_area_min.y, mpRenderBufferDV->getSize().y);

        s32 scissor_w = scissor_max_x - scissor_min_x;
        s32 scissor_h = scissor_max_y - scissor_min_y;

        if (scissor_w > 0 && scissor_h > 0)
        {
            mScissorMin.x = scissor_min_x;
            mScissorMin.y = scissor_min_y;
            mScissorSize.x = scissor_w;
            mScissorSize.y = scissor_h;
            mDrawDV = true;
        }
    }
}

void AreaItem::dv_PostFx_(const rio::lyr::DrawInfo& draw_info)
{
    if (mDrawDV && mpDistantViewMgr)
        mpDistantViewMgr->applyDepthOfField();
}

void AreaItem::DrawCallbackDV::preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    CourseView::instance()->bindRenderBuffer(false);

    if (Globals::applyDistantViewScissor())
    {
        const AreaItem& item = *(CourseView::instance()->getAreaItem()[mIndex]);
        rio::Graphics::setScissor(item.mScissorMin.x, item.mScissorMin.y, item.mScissorSize.x, item.mScissorSize.y, item.mpRenderBufferDV->getSize().y);
    }
}

void AreaItem::DrawCallbackDV::preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void AreaItem::DrawCallbackDV::postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
}

void AreaItem::DrawCallbackDV::postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    CourseView::instance()->unbindRenderBuffer();
}
