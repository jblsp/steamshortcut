#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include "launcher.h"

// Semantic Version Number
#define VMAJOR 1
#define VMINOR 1
#define VPATCH 0

int main(int argc, char *argv[]) {

    char version[16];  // Assuming a maximum of 20 characters for the version string

    sprintf(version, "%d.%d.%d", VMAJOR, VMINOR, VPATCH);

    if (argc != 5) {
        printf("Steam Shortcut v%s\nUsage: %s <mainAccountUsername> <targetAccountUsername> <steamappID> <processName>\n", version, argv[0]);
        return 1;
    }

    printf("\033[1mSteam Shortcut v%s\033[0m\n", version);
    printf("Close this window at anytime to stop the process.\n\n");

    const char* steam_username = argv[1];
    const char* alt_username = argv[2];
    const char* app_ID = argv[3];
    const char* process_name = argv[4];
    char steam_launch_args[128] = "-login ";
    char steam_launch_args_alt[128] = "-login ";
    char game_launch_args[32] = "-applaunch ";

    strcat(steam_launch_args, steam_username);
    strcat(steam_launch_args_alt, alt_username);
    strcat(game_launch_args, app_ID);

    // steam is killed so there is no waiting for steam to shutdown
    killSteam();

    printf("Relaunching Steam...\n");
    launchSteam(steam_launch_args_alt);

    printf("Waiting for game to open...\n");
    while (!IsProcessRunning(process_name)) {
        launchSteam(game_launch_args);
        Sleep(1000);
    }

    printf("Waiting for game to close...\n");
    while (IsProcessRunning(process_name)) {
        Sleep(1000);
    }

    shutDownSteam();

    // reopen steam with original account
    printf("Opening Steam...");
    launchSteam(steam_launch_args);
    sleep(2000);
    
    return 0;
}
