#include "msg.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) 
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) 
    {
        showConsoleMessage("This DLL is injected into the target process successfully");
        showDialogMessage(L"This DLL is injected into the target process successfully");
    }

    return TRUE;
}