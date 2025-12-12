#include "notifs.h"

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

void ShowMessageBox(const wchar_t *title, const wchar_t *text)
{
    LPCWSTR buttons[1] = {L"OK"};
    MESSAGEBOX_RESULT result;
    XOVERLAPPED overlapped;
    
    memset(&overlapped, 0, sizeof(overlapped));
    memset(&result, 0, sizeof(result));
    
    DWORD ret = XShowMessageBoxUI(XUSER_INDEX_ANY, title, text, 1, buttons, 0, XMB_ALERTICON, &result, &overlapped);
    
    if (ret == ERROR_IO_PENDING)
    {
        while (!XHasOverlappedIoCompleted(&overlapped))
            Sleep(50);
    }
}

int ShowMessageBoxWithButtons(const wchar_t *title, const wchar_t *text, const wchar_t *button1, const wchar_t *button2)
{
    LPCWSTR buttons[2] = {button1, button2};
    MESSAGEBOX_RESULT result;
    XOVERLAPPED overlapped;
    
    memset(&overlapped, 0, sizeof(overlapped));
    memset(&result, 0, sizeof(result));
    
    DWORD ret = XShowMessageBoxUI(XUSER_INDEX_ANY, title, text, 2, buttons, 0, XMB_ALERTICON, &result, &overlapped);
    
    if (ret == ERROR_IO_PENDING)
    {
        while (!XHasOverlappedIoCompleted(&overlapped))
            Sleep(50);
    }
    
    return result.dwButtonPressed;
}

void DisplayMessageBox(const char *title, const char *text)
{
    wchar_t wTitle[256];
    wchar_t wText[512];
    
    wsprintfW(wTitle, L"%S", title);
    wsprintfW(wText, L"%S", text);
    
    ShowMessageBox(wTitle, wText);
}

int DisplayMessageBoxWithButtons(const char *title, const char *text, const char *button1, const char *button2)
{
    wchar_t wTitle[256];
    wchar_t wText[512];
    wchar_t wButton1[64];
    wchar_t wButton2[64];
    
    wsprintfW(wTitle, L"%S", title);
    wsprintfW(wText, L"%S", text);
    wsprintfW(wButton1, L"%S", button1);
    wsprintfW(wButton2, L"%S", button2);
    
    return ShowMessageBoxWithButtons(wTitle, wText, wButton1, wButton2);
}