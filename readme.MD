# Steam Shortcut
Create a shortcut to a Steam game that is in the library of another user. When the application is closed, Steam will log back into the original account. Effectively "evade" a ban by opening a shortcut to the game on a banned account.

Works by using [command line options](https://developer.valvesoftware.com/wiki/Command_line_options#Steam) to launch Steam ("-login" and "-applaunch" specifically).

## Example Usage
video here

**Not raw footage, loading times are shortened*

## Setup
### Adding the shortcut to Steam
   1) Add steamshort.exe as a non-Steam game.
   2) Right click on the application in your Steam library and open "Properties."
   3) Enter launch options: `<mainAccountUsername> <targetAccountUsername> <steamAppID> <processName>`
   Where "mainAccountUsername" is the username of the current Steam account, "targetAccountUsername" is the username of the account that owns the game you would like to launch. 
   (You may need to open your Steam account details to find the usernames. Username is different from profile name). For Counter-Strike 2 the appID is `730` and the process name is `cs2.exe`. You can find appIDs in the URL of Steam store pages `store.steampowered.com/app/<appID>/<title>` and you can find the process name by using Task Manager.
### Disguising the shortcut as the game.
1) Source artwork for your game from [SteamGridDB](https://www.steamgriddb.com/). Counter-Strike 2 artwork is available in [this repo](https://github.com/jblsp/steamshortcut/tree/main/cs2_artwork).
2) Open the "Properties" window of the shortcut and change the title.
3) Double-click the icon and change it 

