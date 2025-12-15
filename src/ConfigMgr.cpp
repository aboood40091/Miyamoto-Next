#include <ConfigMgr.h>

ConfigMgr::ConfigMgr(const char* file_name)
    : mFileName(file_name)
{
    mIni.SetUnicode();
    
    SI_Error rc = mIni.LoadFile(mFileName);
    
    if (rc == SI_FILE) // file doesn't exist but that's ok we will make one
        return;
    
    RIO_ASSERT(rc == SI_OK);
}

ConfigMgr::~ConfigMgr()
{
    save();
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
}

void ConfigMgr::setBool(const char* section, const char* key, bool value, const char* comment)
{
    SI_Error rc = mIni.SetBoolValue(section, key, value, comment);
    RIO_ASSERT(rc >= SI_OK);
}

void ConfigMgr::setDouble(const char* section, const char* key, f64 value, const char* comment)
{
    SI_Error rc = mIni.SetDoubleValue(section, key, value, comment);
    RIO_ASSERT(rc >= SI_OK);
}

void ConfigMgr::setInt(const char* section, const char* key, s32 value, const char* comment)
{
    SI_Error rc = mIni.SetLongValue(section, key, value, comment);
    RIO_ASSERT(rc >= SI_OK);
}

void ConfigMgr::save() const
{
    SI_Error rc = mIni.SaveFile(mFileName);
    RIO_ASSERT(rc == SI_OK);
}
