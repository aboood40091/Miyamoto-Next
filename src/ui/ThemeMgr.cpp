#include <ui/ThemeMgr.h>
#include <Preferences.h>
#include <rio.h>

bool ThemeMgr::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new ThemeMgr();
    return true;
}

void ThemeMgr::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

ThemeMgr::ThemeMgr()
{
    loadThemes_();
}

ThemeMgr::~ThemeMgr()
{
}

void ThemeMgr::initialize()
{
    applyTheme(Preferences::instance()->getTheme());
}

std::vector<std::string> ThemeMgr::getThemes() const
{
    std::vector<std::string> theme_names;

    for (const auto& it : mThemes)
        theme_names.push_back(it.first);

    return theme_names;
}

void ThemeMgr::applyTheme(const std::string& name)
{
    const auto& it = mThemes.find(name);
    if (it == mThemes.end())
        return;

    RIO_LOG("ThemeMgr: Applying theme '%s'\n", name.c_str());

    mCurrentTheme = it->first;
    ImGui::GetStyle() = it->second;
    
    Preferences::instance()->setTheme(name);
}

void ThemeMgr::loadThemes_()
{
    mThemes.clear();

    ImGuiStyle default_theme;

    ImVec4* colors = default_theme.Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.07f, 0.12f, 0.15f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.48f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.16f, 0.39f, 0.48f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.77f, 0.98f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.77f, 0.98f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.16f, 0.38f, 0.48f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.24f, 0.69f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.77f, 0.98f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.71f, 0.98f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.77f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.77f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.48f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.56f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.56f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.77f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.77f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.77f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.18f, 0.46f, 0.58f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.77f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.54f, 0.68f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.13f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.34f, 0.42f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.77f, 0.98f, 0.70f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.35f, 0.81f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.00f, 0.63f, 0.90f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.00f, 0.71f, 1.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.34f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.25f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.77f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.00f, 0.71f, 1.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    default_theme.ChildRounding = 4.0f;
    default_theme.FrameRounding = 4.0f;
    default_theme.GrabRounding = 4.0f;
    default_theme.PopupRounding = 4.0f;
    default_theme.ScrollbarRounding = 4.0f;
    default_theme.TabRounding = 4.0f;
    default_theme.WindowRounding = 4.0f;

    mThemes[cDefaultTheme] = default_theme;

    ImGuiStyle light_theme;

    colors = light_theme.Colors;
    colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
    colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.77f, 0.98f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.77f, 0.98f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.26f, 0.77f, 0.98f, 0.78f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.46f, 0.70f, 0.80f, 0.60f);
    colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.77f, 0.98f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.71f, 0.98f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.77f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.77f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.77f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.14f, 0.61f, 0.80f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.14f, 0.61f, 0.80f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.77f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.77f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.76f, 0.81f, 0.84f, 0.93f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.77f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.60f, 0.80f, 0.88f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.92f, 0.93f, 0.93f, 0.98f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.74f, 0.86f, 0.91f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.77f, 0.98f, 0.22f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.35f, 0.81f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.00f, 0.63f, 0.90f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.00f, 0.71f, 1.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.78f, 0.92f, 0.98f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.57f, 0.62f, 0.64f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.68f, 0.72f, 0.74f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.77f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.26f, 0.77f, 0.98f, 0.95f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.77f, 0.98f, 0.80f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    light_theme.ChildRounding = 4.0f;
    light_theme.FrameRounding = 4.0f;
    light_theme.GrabRounding = 4.0f;
    light_theme.PopupRounding = 4.0f;
    light_theme.ScrollbarRounding = 4.0f;
    light_theme.TabRounding = 4.0f;
    light_theme.WindowRounding = 4.0f;

    mThemes["Light Blue"] = light_theme;
    
    ImGuiStyle amoled_theme;
    
    colors = amoled_theme.Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.18f, 0.18f, 0.18f, 0.9f);
    colors[ImGuiCol_Border]                 = ImVec4(0.18f, 0.18f, 0.18f, 0.3f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.0f, 0.0f, 0.0f, 0.24f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.55f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.18f, 0.18f, 0.18f, 0.55f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.2f, 0.21f, 0.22f, 1.0f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06, 0.06, 0.06, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.13f, 0.13f, 0.13f, 1.0f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.55f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.33f, 0.33f, 0.33f, 0.55f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.4f, 0.4f, 0.4f, 0.55f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.55f, 0.55f, 0.55f, 0.55f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.33f, 0.33f, 0.33f, 0.55f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.55f, 0.55f, 0.55f, 0.55f);
    colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.55f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.18f, 0.18f, 0.18f, 0.55f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.2f, 0.21f, 0.22f, 1.0f);
    colors[ImGuiCol_Header]                 = ImVec4(0.0f, 0.0f, 0.0f, 0.52f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.0f, 0.0f, 0.0f, 0.36f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.2f, 0.21f, 0.22f, 0.33f);
    colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.3f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.3f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.4f, 0.44f, 0.46f, 1.0f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.3f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.3f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.4f, 0.44f, 0.46f, 1.0f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.0f, 0.0f, 0.0f, 0.52f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.13f, 0.13f, 0.13f, 1.0f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.2f, 0.2f, 0.2f, 0.36f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.0f, 0.0f, 0.0f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.13f, 0.13f, 0.13f, 1.0f);
    colors[ImGuiCol_PlotLines]              = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.58f, 0.58f, 0.58f, 1.0f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.0f, 0.0f, 0.0f, 0.52f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.0f, 0.0f, 0.0f, 0.52f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.3f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.2f, 0.21f, 0.22f, 1.0f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.32f, 0.66f, 0.85f, 1.0f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.0f, 0.0f, 0.0f, 0.7f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.0f, 0.0f, 0.0f, 0.2f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.0f, 0.0f, 0.0f, 0.35f);
    
    amoled_theme.Alpha = 1.0f;
    amoled_theme.DisabledAlpha = 0.6f;
    amoled_theme.WindowPadding = ImVec2(9.0f, 4.0f);
    amoled_theme.WindowRounding = 7.0f;
    amoled_theme.WindowBorderSize = 1.0f;
    amoled_theme.WindowMinSize = ImVec2(32.0f, 32.0f);
    amoled_theme.WindowTitleAlign = ImVec2(0.0f, 0.5f);
    amoled_theme.WindowMenuButtonPosition = ImGuiDir_Left;
    amoled_theme.ChildRounding = 4.0f;
    amoled_theme.ChildBorderSize = 1.0f;
    amoled_theme.PopupRounding = 3.0f;
    amoled_theme.PopupBorderSize = 1.0f;
    amoled_theme.FramePadding = ImVec2(10.0f, 3.6f);
    amoled_theme.FrameRounding = 3.0f;
    amoled_theme.FrameBorderSize = 1.0f;
    amoled_theme.ItemSpacing = ImVec2(6.0f, 6.0f);
    amoled_theme.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
    amoled_theme.CellPadding = ImVec2(6.0f, 6.0f);
    amoled_theme.IndentSpacing = 20.0f;
    amoled_theme.ColumnsMinSpacing = 6.0f;
    amoled_theme.ScrollbarSize = 12.0f;
    amoled_theme.ScrollbarRounding = 9.0f;
    amoled_theme.GrabMinSize = 10.0f;
    amoled_theme.GrabRounding = 3.0f;
    amoled_theme.TabRounding = 3.0f;
    amoled_theme.TabBorderSize = 1.0f;
    amoled_theme.TabMinWidthForCloseButton = 0.0f;
    amoled_theme.ColorButtonPosition = ImGuiDir_Right;
    amoled_theme.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    amoled_theme.SelectableTextAlign = ImVec2(0.0f, 0.0f);
    
    mThemes["AMOLED"] = amoled_theme;
}
