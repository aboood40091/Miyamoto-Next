#include "ui/ThemeMgr.h"
#include <Preferences.h>

#include <ConfigMgr.h>

std::string Preferences::getTheme()
{
    return ConfigMgr::instance()->getString(cSection, "Theme", ThemeMgr::cDefaultTheme);
}

std::string Preferences::getContentPath()
{
    return ConfigMgr::instance()->getString(cSection, "ContentPath", "game/nsmbu");
}

bool Preferences::getForceSharcfb()
{
    return ConfigMgr::instance()->getBool(cSection, "ForceSharcfb", true);
}

f32 Preferences::getBigItemScale()
{
    return ConfigMgr::instance()->getFloat(cSection, "BigItemScale", 16.0f);
}

bool Preferences::getUseRealZoom()
{
    return ConfigMgr::instance()->getBool(cSection, "UseRealZoom", true);
}

bool Preferences::getPreserveUnitSize()
{
    return ConfigMgr::instance()->getBool(cSection, "PreserveUnitSize", true);
}

bool Preferences::getApplyDistantViewScissor()
{
    return ConfigMgr::instance()->getBool(cSection, "ApplyDistantViewScissor", true);
}

f32 Preferences::getScrollMovementSpeed()
{
    return ConfigMgr::instance()->getFloat(cSection, "ScrollMovementSpeed", 200.0f);
}

f32 Preferences::getArrowMovementSpeed()
{
    return ConfigMgr::instance()->getFloat(cSection, "ArrowMovementSpeed", 25.0f);
}

f32 Preferences::getFastArrowMovementSpeed()
{
    return ConfigMgr::instance()->getFloat(cSection, "FastArrowMovementSpeed", 100.0f);
}

void Preferences::setTheme(const std::string& value)
{
    ConfigMgr::instance()->setString(cSection, "Theme", value.c_str());
}

void Preferences::setContentPath(const std::string& value)
{
    ConfigMgr::instance()->setString(cSection, "ContentPath", value.c_str());
}

void Preferences::setForceSharcfb(bool value)
{
    ConfigMgr::instance()->setBool(cSection, "ForceSharcfb", value);
}

void Preferences::setBigItemScale(f32 value)
{
    ConfigMgr::instance()->setFloat(cSection, "BigItemScale", value);
}

void Preferences::setUseRealZoom(bool value)
{
    ConfigMgr::instance()->setBool(cSection, "UseRealZoom", value);
}

void Preferences::setPreserveUnitSize(bool value)
{
    ConfigMgr::instance()->setBool(cSection, "PreserveUnitSize", value);
}

void Preferences::setApplyDistantViewScissor(bool value)
{
    ConfigMgr::instance()->setBool(cSection, "ApplyDistantViewScissor", value);
}

void Preferences::setScrollMovementSpeed(f32 value)
{
    ConfigMgr::instance()->setFloat(cSection, "ScrollMovementSpeed", value);
}

void Preferences::setArrowMovementSpeed(f32 value)
{
    ConfigMgr::instance()->setFloat(cSection, "ArrowMovementSpeed", value);
}

void Preferences::setFastArrowMovementSpeed(f32 value)
{
    ConfigMgr::instance()->setFloat(cSection, "FastArrowMovementSpeed", value);
}

