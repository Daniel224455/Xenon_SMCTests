#ifndef NOTIFS_H
#define NOTIFS_H

#include "../common.h"

#ifdef __cplusplus
extern "C" {
#endif

DWORD XexGetModuleHandle(LPCSTR moduleName, HANDLE* moduleHandle);
DWORD XexGetProcedureAddress(HANDLE module, DWORD ordinal, PDWORD address);

typedef void (*XNotifyQueueUI_t)(uint32_t type, uint32_t userIndex, uint64_t areas, const wchar_t *displayText, void *pContextData);

extern XNotifyQueueUI_t XNotifyQueueUI;

void ResolveXamFunctions(void);
void NotificationPopup(wchar_t *text);
void ShowNotification(const char *text);
void ShowMessageBox(const wchar_t *title, const wchar_t *text);
int ShowMessageBoxWithButtons(const wchar_t *title, const wchar_t *text, const wchar_t *button1, const wchar_t *button2);
void DisplayMessageBox(const char *title, const char *text);
int DisplayMessageBoxWithButtons(const char *title, const char *text, const char *button1, const char *button2);

#ifdef __cplusplus
}
#endif

#endif // NOTIFS_H