#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemBase.h>

class LocationItem : public ItemBase
{
public:
    LocationItem(Location& location, u32 index);

    void move(s16 dx, s16 dy, bool commit) override;
    void drawSelectionUI() override;

    void drawOpa();
    void drawXlu();

private:
    f32 getZPos_() const
    {
        return 3600.0f - 10;
    }

    void onSelectionChange_() override;

private:
    Location mSelectionData;
};
