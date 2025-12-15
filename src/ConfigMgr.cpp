#include "SimpleIni.h"
#include "misc/rio_Types.h"
#include <ConfigMgr.h>

bool ConfigMgr::createSingleton()
{
    if (sInstance)
        return false;
    
    sInstance = new ConfigMgr();
    return true;
}

void ConfigMgr::destroySingleton()
{
    if (!sInstance)
        return;
    
    delete sInstance;
    sInstance = nullptr;
}

ConfigMgr::ConfigMgr()
{
    mIni.SetUnicode();
    
    SI_Error rc = mIni.LoadFile(cFileName);
    
    if (rc == SI_FILE) // file doesn't exist but that's ok we will make one
        return;
    
    RIO_ASSERT(rc == SI_OK);
}

ConfigMgr::~ConfigMgr()
{
}

std::string ConfigMgr::getString(const char* section, const char* key, const char* default_value)
{
    return mIni.GetValue(section, key, default_value);
}

bool ConfigMgr::getBool(const char* section, const char* key, bool default_value)
{
    return mIni.GetBoolValue(section, key, default_value);
}

f64 ConfigMgr::getDouble(const char* section, const char* key, f64 default_value)
{
    return mIni.GetDoubleValue(section, key, default_value);
}

s32 ConfigMgr::getInt(const char* section, const char* key, s32 default_value)
{
    return static_cast<s32>(mIni.GetLongValue(section, key, default_value));
}

void ConfigMgr::setString(const char* section, const char* key, const char* value, const char* comment)
{
    SI_Error rc = mIni.SetValue(section, key, value, comment);
    RIO_ASSERT(rc >= SI_OK);
    save_();
}

void ConfigMgr::setBool(const char* section, const char* key, bool value, const char* comment)
{
    SI_Error rc = mIni.SetBoolValue(section, key, value, comment);
    RIO_ASSERT(rc >= SI_OK);
    save_();
}

void ConfigMgr::setDouble(const char* section, const char* key, f64 value, const char* comment)
{
    SI_Error rc = mIni.SetDoubleValue(section, key, value, comment);
    RIO_ASSERT(rc >= SI_OK);
    save_();
}

void ConfigMgr::setInt(const char* section, const char* key, s32 value, const char* comment)
{
    SI_Error rc = mIni.SetLongValue(section, key, value, comment);
    RIO_ASSERT(rc >= SI_OK);
    save_();
}

void ConfigMgr::save_()
{
    SI_Error rc = mIni.SaveFile(cFileName);
    RIO_ASSERT(rc == SI_OK);
}
