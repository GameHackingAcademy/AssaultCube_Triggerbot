# Assault Cube Triggerbot
Referenced in https://gamehacking.academy/lesson/5/5.

A triggerbot for Assault Cube 1.2.0.2 that fires the player's weapon whenever the crosshair goes over another player.

![Triggerbot](https://github.com/GameHackingAcademy/AssaultCube_Triggerbot/blob/master/cube.gif?raw=true)

This works by hooking the game's feature that displays nametags when you hover over a player. Whenever a player is hovered over, our code cave will send a mouse down event to the game. Otherwise, it will send a mouse up event to stop firing.

This must be injected into the Assault Cube process to work. One way to do this is to use a DLL injector. Another way is to enable AppInit_DLLs in the registry.
