#pragma once

#include <util/SimpleIniWrapper.h>

class ConfigMgr
{
public:
    ConfigMgr(const char* file_name);
    ~ConfigMgr() = default;
    
    ConfigMgr(const ConfigMgr&) = delete;
    ConfigMgr& operator=(const ConfigMgr&) = delete;

    [[nodiscard]]
    std::string getString(const char* section, const char* key, const char* default_value = nullptr);
    
    [[nodiscard]]
    bool getBool(const char* section, const char* key, bool default_value = false);
    
    [[nodiscard]]
    f64 getDouble(const char* section, const char* key, f64 default_value = 0.0);
    
    [[nodiscard]]
    f32 getFloat(const char* section, const char* key, f32 default_value = 0.0f)
    {
        return static_cast<f32>(getDouble(section, key, default_value));
    }
    
    [[nodiscard]]
    s32 getInt(const char* section, const char* key, s32 default_value = 0);
    
    void setString(const char* section, const char* key, const char* value, const char* comment = nullptr);
    void setBool(const char* section, const char* key, bool value, const char* comment = nullptr);
    void setDouble(const char* section, const char* key, f64 value, const char* comment = nullptr);
    void setFloat(const char* section, const char* key, f32 value, const char* comment = nullptr)
    {
        setDouble(section, key, value, comment);
    }
    void setInt(const char* section, const char* key, s32 value, const char* comment = nullptr);

private:
    void save_();
    
private:
    CSimpleIniA mIni;
    const char* mFileName;
};
