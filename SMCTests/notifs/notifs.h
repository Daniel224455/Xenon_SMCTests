#ifndef NOTIFS_H
#define NOTIFS_H

#include "../common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*XNotifyQueueUI_t)(uint32_t type, uint32_t userIndex, uint64_t areas, const wchar_t *displayText, void *pContextData);

extern XNotifyQueueUI_t XNotifyQueueUI;

void ResolveXamFunctions(void);
void NotificationPopup(wchar_t *text);
void ShowNotification(const char *text);

#ifdef __cplusplus
}
#endif

#endif