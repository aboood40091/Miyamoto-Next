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
    static const std::string sDefaultTheme;

private:
    static ThemeMgr* sInstance;

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

private:
    void loadThemes_();

private:
    std::map<std::string, ImGuiStyle> mThemes;
    std::string mCurrentTheme;
};
