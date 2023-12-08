#include <map_obj/ObjDokanActorBase.h>

ObjDokanActorBase::ObjDokanActorBase(MapActorData& map_actor_data, u32 index, ObjDokan::Direction dir, bool cb, bool group, f32 position_offset_x, f32 position_offset_y)
    : MapActorItem(map_actor_data, index)
    , mObjDokan(dir)
    , cCB(cb)
    , cGroup(group)
    , cPositionOffset { position_offset_x, position_offset_y }
{
    updatePositionXY_();
    updatePositionZ_();

    if (updateParam_())
        mObjDokan.move(mPosition);

    setModelItemID_();
}

void ObjDokanActorBase::setModelItemID_()
{
    mObjDokan.setModelItemID(mItemID);
}

void ObjDokanActorBase::setModelSelection_()
{
    mObjDokan.setModelSelection(mIsSelected);
}

bool ObjDokanActorBase::updateParam_()
{
    s32 length = mMapActorData.settings[0] & 0xF;
    ObjDokan::Color color = ObjDokan::Color(mMapActorData.settings[0] >> 4 & 3);
    ObjDokan::Type type = ObjDokan::Type(mMapActorData.settings[0] >> 16 & 3);
    bool enable_draw_a = cCB || cGroup || !(mMapActorData.settings[0] >> 29 & 1);

    if (cCB)
    {
        length = 8;
        type = ObjDokan::TYPE_CB;
    }
    else if (type == ObjDokan::TYPE_MAME)
    {
        color = ObjDokan::COLOR_INVALID;
        type = ObjDokan::TYPE_BIG;
    }

    return mObjDokan.initialize(type, (length + 1) * 16, enable_draw_a, color);
}

void ObjDokanActorBase::onDataChange(DataChangeFlag flag)
{
    bool position_changed = false;

    if (flag & DATA_CHANGE_FLAG_LAYER)
    {
        updatePositionZ_();
        position_changed = mObjDokan.isCreated() || position_changed;
    }

    if (flag & DATA_CHANGE_FLAG_OFFSET)
    {
        updatePositionXY_();
        position_changed = mObjDokan.isCreated() || position_changed;
    }

    if (flag & DATA_CHANGE_FLAG_SETTINGS_0)
        position_changed = updateParam_() || position_changed;

    if (position_changed)
        mObjDokan.move(mPosition);
}
