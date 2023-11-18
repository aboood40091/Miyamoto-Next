#include <map_obj/ObjDokanActorBase.h>

ObjDokanActorBase::ObjDokanActorBase(MapActorData& map_actor_data, ObjDokan::Direction dir, bool cb, bool group)
    : MapActorItem(map_actor_data)
{
    s32 length = mMapActorData.settings[0] & 0xF;
    ObjDokan::Color color = ObjDokan::Color(mMapActorData.settings[0] >> 4 & 3);
    ObjDokan::Type type = ObjDokan::Type(mMapActorData.settings[0] >> 16 & 3);
    bool a_visible = cb || group || !(mMapActorData.settings[0] >> 29 & 1);

    if (cb)
    {
        length = 8;
        type = ObjDokan::TYPE_CB;
    }
    else if (type == ObjDokan::TYPE_MAME)
    {
        color = ObjDokan::COLOR_INVALID;
        type = ObjDokan::TYPE_BIG;
    }

    mObjDokan = std::make_unique<ObjDokan>(dir, type, (length + 1) * 16, a_visible, color);
    if (!mObjDokan->isCreated())
        mObjDokan.reset();
}

void ObjDokanActorBase::scheduleDraw()
{
    if (mObjDokan == nullptr)
        return;

    mObjDokan->scheduleDraw();
}
