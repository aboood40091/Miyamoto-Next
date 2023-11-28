#include <ui/ImGuiUtil.h>

#if RIO_IS_CAFE
#include <controller/rio_ControllerMgr.h>
#include <controller/cafe/rio_CafeVPadDeviceCafe.h>
#include <controller/cafe/rio_CafeWPadDeviceCafe.h>
#endif // RIO_IS_CAFE
#include <gfx/rio_Graphics.h>
#include <gfx/rio_Window.h>

#if RIO_IS_CAFE
#include <imgui_impl_gx2.h>
#include <imgui_impl_wiiu.h>
#else
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif // RIO_IS_CAFE

void ImGuiUtil::initialize()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
#if RIO_IS_CAFE
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
#else
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
#endif // RIO_IS_CAFE
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

#if !RIO_IS_CAFE
    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
#endif

#if RIO_IS_CAFE
    // Scale everything by 1.5 for the Wii U
    ImGui::GetStyle().ScaleAllSizes(1.5f);
    io.FontGlobalScale = 1.5f;
#endif // RIO_IS_CAFE

    // Setup platform and renderer backends
#if RIO_IS_CAFE
    ImGui_ImplWiiU_Init();
    ImGui_ImplGX2_Init();
#else
    ImGui_ImplGlfw_InitForOpenGL(rio::Window::instance()->getNativeWindow().getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
#endif // RIO_IS_CAFE
}

void ImGuiUtil::shutdown()
{
    // Cleanup
#if RIO_IS_CAFE
    ImGui_ImplGX2_Shutdown();
    ImGui_ImplWiiU_Shutdown();
#else
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
#endif // RIO_IS_CAFE
    ImGui::DestroyContext();
}

void ImGuiUtil::setDisplaySize(f32 width, f32 height)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = width;
    io.DisplaySize.y = height;
}

void ImGuiUtil::newFrame()
{
    // Start the Dear ImGui frame
#if RIO_IS_CAFE
    ImGui_ImplWiiU_ControllerInput input;
    // VPAD
    {
        rio::CafeVPadDevice* device = static_cast<rio::CafeVPadDevice*>(rio::ControllerMgr::instance()->getControlDevice(rio::ControllerDefine::DEVICE_CAFE_V_PAD));
        if (device)
        {
            {
                const rio::CafeVPadDevice::VPadInfo& v_pad_info = device->getVPadInfo();
                if (v_pad_info.last_read_error == VPAD_READ_SUCCESS)
                    input.vpad = const_cast<VPADStatus*>(&(v_pad_info.status[0]));
            }
        }
    }
    // KPAD
    {
        rio::CafeWPadDevice* device = static_cast<rio::CafeWPadDevice*>(rio::ControllerMgr::instance()->getControlDevice(rio::ControllerDefine::DEVICE_CAFE_W_PAD));
        if (device)
        {
            for (int i = 0; i < 4; i++)
            {
                const rio::CafeWPadDevice::KPadInfo& k_pad_info = device->getKPadInfo(i);
                if (k_pad_info.last_read_error == KPAD_ERROR_OK)
                    input.kpad[i] = const_cast<KPADStatus*>(&(k_pad_info.status[0]));
            }
        }
    }
    ImGui_ImplWiiU_ProcessInput(&input);
    ImGui_ImplGX2_NewFrame();
#else
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
#endif // RIO_IS_CAFE
    ImGui::NewFrame();
}

void ImGuiUtil::render()
{
    ImGuiIO& io = ImGui::GetIO();

    // Rendering
    ImGui::Render();

    // Render draw data
#if RIO_IS_CAFE
    ImGui_ImplGX2_RenderDrawData(ImGui::GetDrawData());
#else
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif // RIO_IS_CAFE

#if RIO_IS_CAFE
    // Render keyboard overlay
    rio::Graphics::setViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y, 0.0f, 1.0f);
    rio::Graphics::setScissor(0, 0, io.DisplaySize.x, io.DisplaySize.y);
    ImGui_ImplWiiU_DrawKeyboardOverlay();
#else
    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
#endif // RIO_IS_CAFE
}
