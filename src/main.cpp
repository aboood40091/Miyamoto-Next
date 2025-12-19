#include <MainWindow.h>

#include <rio.h>

#if RIO_IS_DESKTOP
#include <tracy/Tracy.hpp>
#endif // RIO_IS_DESKTOP

#if RIO_IS_WIN

#include <misc/win/rio_Windows.h>

extern "C" {

__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;

}

#endif // RIO_IS_WIN

static const rio::InitializeArg cInitializeArg = {
    .window = {
#if RIO_IS_DESKTOP
        .resizable = true,
        .gl_major = 4,
        .gl_minor = 3
#endif // RIO_IS_DESKTOP
    }
};

int main()
{
#if RIO_IS_DESKTOP
    TracyNoop;
#endif // RIO_IS_DESKTOP

    // Initialize RIO with root task
    if (!rio::Initialize<MainWindow>(cInitializeArg))
        return -1;

    // Main loop
    rio::EnterMainLoop();

    // Exit RIO
    rio::Exit();

    return 0;
}
