#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <tlhelp32.h>
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


bool IsProcessRunning(const char* processName) {
    // create a snapshot of the system's process list
    // TH32CS_SNAPPROCESS specifies all processes in the system
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (strstr(pe32.szExeFile, processName)) {
                CloseHandle(hSnapshot);
                return true;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return false;
}

void shutDownSteam() {
    printf("Shutting down Steam...\n");
    system("\"C:\\Program Files (x86)\\Steam\\steam.exe\" -shutdown");
    while (IsProcessRunning("steam.exe")) {
        Sleep(1000);  // Sleep for 1 second
    }
}

void killSteam() {
    system("taskkill /f /im steam.exe");
}
