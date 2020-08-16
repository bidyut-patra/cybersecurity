#include "msg.h"

void showConsoleMessage(const char *msg)
{
    std::cout << msg << std::endl;
}

void showDialogMessage(LPCWSTR msg)
{
    MessageBoxW(0, msg, L"DLL Injection", MB_ICONINFORMATION);
}