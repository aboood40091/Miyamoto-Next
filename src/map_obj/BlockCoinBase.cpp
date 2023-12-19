#include <CourseView.h>
#include <course/BgRenderer.h>
#include <map_obj/BlockCoinBase.h>

void BlockCoinBase::onDataChange(const MapActorData& map_actor_data, DataChangeFlag flag)
{
    if (flag & DATA_CHANGE_FLAG_OFFSET)
        updatePositionXY_(map_actor_data);

    if (flag & DATA_CHANGE_FLAG_LAYER)
        updatePositionZ_(map_actor_data);
}

void BlockCoinBase::scheduleDraw()
{
    if (drawBox())
        return;

    const MapActorData& map_actor_data = CourseView::instance()->getCourseDataFile().getMapActorData()[mItemID.getIndex()];

    BgRenderer::instance()->drawUnit(
        mItemID, mPosition, getUnitID_(), map_actor_data.layer
    );
}
