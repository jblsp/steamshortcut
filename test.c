#include <windows.h>
#include <stdlib.h>

int main() {
    char steamCmd[512];
    strcpy(steamCmd, "\"C:\\Program Files (x86)\\Steam\\steam.exe\"");

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi; // Not used, but required by CreateProcess

    // Create a non-const buffer for the command
    char commandBuffer[MAX_PATH];
    strncpy(commandBuffer, steamCmd, sizeof(commandBuffer));

    CreateProcess(NULL, commandBuffer, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

    return 0;
}