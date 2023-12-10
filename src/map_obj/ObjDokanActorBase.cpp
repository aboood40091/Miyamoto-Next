#include <map_obj/ObjDokanActorBase.h>

ObjDokanActorBase::ObjDokanActorBase(MapActorData& map_actor_data, u32 index, ObjDokan::Direction dir, bool cb, bool group, f32 position_offset_x, f32 position_offset_y)
    : MapActorItem(map_actor_data, index)
    , mObjDokan(dir)
    , cCB(cb)
    , cGroup(group)
    , cPositionOffset { position_offset_x, position_offset_y }
{
    updatePositionXY_(map_actor_data);
    updatePositionZ_(map_actor_data);

    if (updateParam_(map_actor_data))
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

bool ObjDokanActorBase::updateParam_(const MapActorData& map_actor_data)
{
    s32 length = map_actor_data.settings[0] & 0xF;
    ObjDokan::Color color = ObjDokan::Color(map_actor_data.settings[0] >> 4 & 3);
    ObjDokan::Type type = ObjDokan::Type(map_actor_data.settings[0] >> 16 & 3);
    bool enable_draw_a = cCB || cGroup || !(map_actor_data.settings[0] >> 29 & 1);

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

void ObjDokanActorBase::onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag)
{
    bool position_changed = false;

    if (flag & DATA_CHANGE_FLAG_LAYER)
    {
        updatePositionZ_(map_actor_data);
        position_changed = mObjDokan.isCreated() || position_changed;
    }

    if (flag & DATA_CHANGE_FLAG_OFFSET)
    {
        updatePositionXY_(map_actor_data);
        position_changed = mObjDokan.isCreated() || position_changed;
    }

    if (flag & DATA_CHANGE_FLAG_SETTINGS_0)
        position_changed = updateParam_(map_actor_data) || position_changed;

    if (position_changed)
        mObjDokan.move(mPosition);
}
