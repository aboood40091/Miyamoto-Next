#include <map_obj/DokanBase.h>

DokanBase::DokanBase(MapActorData& map_actor_data, Dokan::Direction dir, bool cb, bool group)
    : MapActorItem(map_actor_data)
{
    s32 length = mMapActorData.settings[0] & 0xF;
    Dokan::Color color = Dokan::Color(mMapActorData.settings[0] >> 4 & 3);
    Dokan::Type type = Dokan::Type(mMapActorData.settings[0] >> 16 & 3);
    bool a_visible = cb || group || !(mMapActorData.settings[0] >> 29 & 1);

    if (cb)
    {
        length = 8;
        type = Dokan::TYPE_CB;
    }
    else if (type == Dokan::TYPE_MAME)
    {
        color = Dokan::COLOR_INVALID;
        type = Dokan::TYPE_BIG;
    }

    mDokan = std::make_unique<Dokan>(dir, type, (length + 1) * 16, a_visible, color);
    if (!mDokan->isCreated())
        mDokan.reset();
}

void DokanBase::drawOpa(const rio::lyr::DrawInfo& draw_info)
{
    if (mDokan)
        return;

    MapActorItem::drawOpa(draw_info);
}

void DokanBase::drawXlu(const rio::lyr::DrawInfo& draw_info)
{
    if (mDokan)
        return;

    MapActorItem::drawXlu(draw_info);
}

void DokanBase::scheduleDraw()
{
    if (mDokan == nullptr)
        return;

    mDokan->scheduleDraw();
}
