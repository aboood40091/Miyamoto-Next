#include <Preferences.h>
#include <ui/ThemeMgr.h>

bool Preferences::createSingleton()
{
    if (sInstance)
        return false;
    
    sInstance = new Preferences();
    return true;
}

void Preferences::destroySingleton()
{
    if (!sInstance)
        return;
    
    delete sInstance;
    sInstance = nullptr;
}

Preferences::Preferences()
    : mConfig("preferences.ini")
{
}

std::string Preferences::getTheme()
{
    return mConfig.getString(cSection, "Theme", ThemeMgr::cDefaultTheme);
}

void Preferences::setTheme(const std::string& value)
{
    mConfig.setString(cSection, "Theme", value.c_str());
}

std::string Preferences::getContentPath()
{
    return mConfig.getString(cSection, "ContentPath", "game/nsmbu");
}

void Preferences::setContentPath(const std::string& value)
{
    mConfig.setString(cSection, "ContentPath", value.c_str());
}

bool Preferences::getForceSharcfb()
{
    return mConfig.getBool(cSection, "ForceSharcfb", true);
}

void Preferences::setForceSharcfb(bool value)
{
    mConfig.setBool(cSection, "ForceSharcfb", value);
}

f32 Preferences::getBigItemScale()
{
    return mConfig.getFloat(cSection, "BigItemScale", 16.0f);
}

void Preferences::setBigItemScale(f32 value)
{
    mConfig.setFloat(cSection, "BigItemScale", value);
}

f32 Preferences::getZoomUnitSize()
{
    return mConfig.getFloat(cSection, "ZoomUnitSize", 32.0f);
}

void Preferences::setZoomUnitSize(f32 value)
{
    mConfig.setFloat(cSection, "ZoomUnitSize", value);
}

bool Preferences::getApplyDistantViewScissor()
{
    return mConfig.getBool(cSection, "ApplyDistantViewScissor", true);
}

void Preferences::setApplyDistantViewScissor(bool value)
{
    mConfig.setBool(cSection, "ApplyDistantViewScissor", value);
}

f32 Preferences::getScrollMovementSpeed()
{
    return mConfig.getFloat(cSection, "ScrollMovementSpeed", 200.0f);
}

void Preferences::setScrollMovementSpeed(f32 value)
{
    mConfig.setFloat(cSection, "ScrollMovementSpeed", value);
}

f32 Preferences::getArrowMovementSpeed()
{
    return mConfig.getFloat(cSection, "ArrowMovementSpeed", 25.0f);
}

void Preferences::setArrowMovementSpeed(f32 value)
{
    mConfig.setFloat(cSection, "ArrowMovementSpeed", value);
}

f32 Preferences::getFastArrowMovementSpeed()
{
    return mConfig.getFloat(cSection, "FastArrowMovementSpeed", 100.0f);
}

void Preferences::setFastArrowMovementSpeed(f32 value)
{
    mConfig.setFloat(cSection, "FastArrowMovementSpeed", value);
}

bool Preferences::getSmoothZoom()
{
    return mConfig.getBool(cSection, "SmoothZoom", true);
}

void Preferences::setSmoothZoom(bool value)
{
    mConfig.setBool(cSection, "SmoothZoom", value);
}
