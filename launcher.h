#ifndef LAUNCHER_H
#define LAUNCHER_H

void launchSteam(char *args);
bool IsProcessRunning(const char* processName);
void shutDownSteam();
void killSteam();

#endif
