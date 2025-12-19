#include <MainWindow.h>

#include <rio.h>

#if RIO_IS_WIN
    #include <Windows.h>
#endif

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
    // Initialize RIO with root task
    if (!rio::Initialize<MainWindow>(cInitializeArg))
        return -1;

    // Main loop
    rio::EnterMainLoop();

    // Exit RIO
    rio::Exit();

    return 0;
}
