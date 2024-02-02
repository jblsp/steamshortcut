#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include "launcher.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <mainAccountUsername> <targetAccountUsername> <steamappID> <processName>\n", argv[0]);
        return 1;
    }

    printf("\033[1mSteam Shortcut v1.0\033[0m\n");
    printf("Close this window at anytime to stop the process.\n\n");

    const char* original_username = argv[1];
    const char* alt_username = argv[2];
    const char* app_ID = argv[3];
    const char* process_name = argv[4];
    char steam_args[256];

    // steam is killed so there is no waiting for steam to shutdown this process
    killSteam();

    printf("Relaunching Steam...\n");
    strcpy(steam_args, "-login ");
    strcat(steam_args, alt_username);
    launchSteam(steam_args);
    
    // launch desired app
    strcpy(steam_args, "-applaunch ");
    strcat(steam_args, app_ID);
    launchSteam(steam_args);

    printf("Waiting for game to open...\n");
    while (!IsProcessRunning(process_name)) {
        Sleep(1000); 
    }

    printf("Waiting for game to close...\n");
    while (IsProcessRunning(process_name)) {
        Sleep(1000);
    }

    shutDownSteam();

    // reopen steam with original account
    printf("Opening Steam...");
    strcpy(steam_args, "-login ");
    strcat(steam_args, original_username);
    launchSteam(steam_args);

    return 0;
}
