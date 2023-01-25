#pragma once

#include <course/CourseDataFile.h>

class SpriteItem
{
public:
    SpriteItem(Sprite& sprite);

    Sprite& getSprite() { return mSprite; }
    const Sprite& getSprite() const { return mSprite; }

    void draw() const;

private:
    Sprite& mSprite;
};
