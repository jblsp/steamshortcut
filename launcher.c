#include <windows.h>
#include <string.h>
#include "launcher.h"

void launchSteam(char *args) {
    char path[512] = "\"C:\\Program Files (x86)\\Steam\\steam.exe\"";
    if (args) {
        strcat(path, " ");
        strcat(path, args);
    }

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    CreateProcess(NULL, path, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}