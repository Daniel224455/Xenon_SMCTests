#include "../common.h"

extern "C" {
    DWORD XexGetModuleHandle(LPCSTR moduleName, HANDLE* moduleHandle);
    DWORD XexGetProcedureAddress(HANDLE module, DWORD ordinal, PDWORD address);
}

typedef void (*XNotifyQueueUI_t)(uint32_t type, uint32_t userIndex, uint64_t areas, const wchar_t *displayText, void *pContextData);
XNotifyQueueUI_t XNotifyQueueUI = NULL;

void ResolveXamFunctions(void)
{
    HANDLE handle = NULL;
    DWORD addr = 0;
    
    XexGetModuleHandle("xam.xex", &handle);
    if (handle == NULL)
        return;
    
    XexGetProcedureAddress(handle, 656, &addr);
    if (addr != 0)
        XNotifyQueueUI = (XNotifyQueueUI_t)addr;
}

void NotificationPopup(wchar_t *text)
{
    if (XNotifyQueueUI != NULL)
    {
        XNotifyQueueUI(14, 0, XNOTIFY_SYSTEM, text, NULL);
    }
}

void ShowNotification(const char *text)
{
    wchar_t message[256];
    ResolveXamFunctions();
    wsprintfW(message, L"%S", text);
    NotificationPopup(message);
}