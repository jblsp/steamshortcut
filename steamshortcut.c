#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>

// Function to check if a process with the given name is running
bool IsProcessRunning(const char* processName) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        CloseHandle(hProcessSnap);
        return false;
    }

    if (Process32First(hProcessSnap, &pe32)) {
        do {
            if (strstr(pe32.szExeFile, processName) != NULL) {
                CloseHandle(hProcessSnap);
                return true;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);
    return false;
}

void shutDownSteam() {
    printf("Shutting down Steam...\n");
    system("\"C:\\Program Files (x86)\\Steam\\steam.exe\" -shutdown");
    while (IsProcessRunning("steam.exe")) {
        Sleep(1000);  // Sleep for 1 second
    }
}

// Creates a separate process that launches steam so we don't get stuck on system()
void launchSteam(char *args) {
    char steamCmd[512];
    strcpy(steamCmd, "\"C:\\Program Files (x86)\\Steam\\steam.exe\" ");
    strcat(steamCmd, args);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a non-const buffer for the command
    char commandBuffer[MAX_PATH];
    strncpy(commandBuffer, steamCmd, sizeof(commandBuffer));

    if (CreateProcess(NULL, commandBuffer, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // Successfully launched Steam, close the process and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        // Handle the error if Steam couldn't be launched
        printf("Error launching Steam: %d\n", GetLastError());
    }
}

void killSteam() {
    system("taskkill /f /im steam.exe");
}


int main(int argc, char *argv[]) {
    
    // TODO: check for args
    
    if (argc != 4) {
        printf("Usage: %s <mainAccountUsername> <targetAccountUsername> <steamappID>\n", argv[0]);
        return 1;
    }

    const char* originalUsername = argv[1];
    const char* cs2Username = argv[2];
    const char* appID = argv[3];
    char steam_args[256];

    killSteam();

    printf("Relaunching Steam...\n");
    strcpy(steam_args, "-login ");
    strcat(steam_args, cs2Username);
    launchSteam(steam_args);
    
    // launch desired app
    strcpy(steam_args, "-applaunch ");
    strcat(steam_args, appID);
    launchSteam(steam_args);

    printf("Waiting for CS2 to open...\n");
    while (!IsProcessRunning("cs2.exe")) {
        Sleep(1000); 
    }

    printf("Waiting for CS2 to close...\n");
    while (IsProcessRunning("cs2.exe")) {
        Sleep(1000);
    }

    shutDownSteam();

    // reopen steam with original account
    printf("Opening Steam...");
    strcpy(steam_args, "-login ");
    strcat(steam_args, originalUsername);
    launchSteam(steam_args);

    return 0;
}
