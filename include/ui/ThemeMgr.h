#pragma once

#include <imgui.h>
#include <string>
#include <vector>
#include <map>

class ThemeMgr
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static ThemeMgr* instance() { return sInstance; }

    static constexpr const char* cDefaultTheme = "Dark Blue";

private:
    static inline ThemeMgr* sInstance = nullptr;

    ThemeMgr();
    ~ThemeMgr();

    ThemeMgr(const ThemeMgr&) = delete;
    ThemeMgr& operator=(const ThemeMgr&) = delete;

public:
    const std::string& getCurrentTheme() const
    {
        return mCurrentTheme;
    }

    std::vector<std::string> getThemes() const;
    void applyTheme(const std::string& name);
    
    void initialize();

private:
    void loadThemes_();

private:
    std::map<std::string, ImGuiStyle> mThemes;
    std::string mCurrentTheme;
};
