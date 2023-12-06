#pragma once

#include <course/CourseDataFile.h>
#include <item/ItemBase.h>

class LocationItem : public ItemBase
{
public:
    LocationItem(Location& location, u32 index);

    Location& getLocation() { return mLocation; }
    const Location& getLocation() const { return mLocation; }

    void move(s16 dx, s16 dy, bool commit) override
    {
        mLocation.offset.x = mBasePosition.x + dx;
        mLocation.offset.y = mBasePosition.y + dy;
        if (commit)
        {
            mBasePosition.x = mLocation.offset.x;
            mBasePosition.y = mLocation.offset.y;
        }
    }

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
    Location& mLocation;
    Location mSelectionData;
};
