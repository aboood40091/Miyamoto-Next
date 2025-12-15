#pragma once

#include <misc/rio_Types.h>

#include <SimpleIni.h>
#if RIO_IS_WIN
    #undef near
    #undef far
#endif // RIO_IS_WIN

class ConfigMgr
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static ConfigMgr* instance() { return sInstance; }

private:
    static inline ConfigMgr* sInstance = nullptr;
    static constexpr const char* cFileName = "config.ini";
    
    ConfigMgr();
    ~ConfigMgr();
    
    ConfigMgr(const ConfigMgr&) = delete;
    ConfigMgr& operator=(const ConfigMgr&) = delete;

public:
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
};
