# AssaultCube Triggerbot
A triggerbot for Assault Cube that fires the player's weapon whenever the crosshair goes over another player.

![Triggerbot](https://github.com/GameHackingAcademy/AssaultCube_Triggerbot/blob/master/cube.gif?raw=true)

This works by hooking the game's feature that displays nametags when you hover a player. Whenever a player is hovered over, our codecave will send a mouse down event to the game. Otherwise, it will send a mouse up event to stop firing.

This must be injected into the Urban Terror process to work. One way to do this is to use a DLL injector. Another way is to enable AppInit_DLLs in the registry.

The offsets and method to discover them are discussed in the article at: https://gamehacking.academy/lesson/26
