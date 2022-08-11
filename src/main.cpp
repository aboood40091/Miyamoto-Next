#include <MainWindow.h>

#include <rio.h>

int main()
{
    // Initialize RIO with root task
    if (!rio::Initialize<MainWindow>())
        return false;

    // Main loop
    rio::EnterMainLoop();

    // Exit RIO
    rio::Exit();

    return 0;
}
