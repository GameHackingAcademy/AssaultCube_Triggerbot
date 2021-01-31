/*
A triggerbot for Assault Cube that fires the player's weapon whenever the crosshair goes over another player.

This works by hooking the game's feature that displays nametags when you hover a player. Whenever a player is hovered over, our codecave
will send a mouse down event to the game. Otherwise, it will send a mouse up event to stop firing.

This must be injected into the Assault Cube process to work. One way to do this is to use a DLL injector. 
Another way is to enable AppInit_DLLs in the registry.

The offsets and method to discover them are discussed in the article at: https://gamehacking.academy/lesson/26
*/
#include <Windows.h>

DWORD ori_call_address = 0x4607C0;
DWORD ori_jump_address = 0x0040ADA2;

INPUT input = { 0 };
DWORD edi_value = 0;

// Our codecave that program execution will jump to. The declspec naked attribute tells the compiler to not add any function
// headers around the assembled code
__declspec(naked) void codecave() {
	// Asm blocks allow you to write pure assembly
	// In this case, we use it to call the function we hooked and save all the registers
	// After we make the call, we move its return value in eax into a variable
	__asm {
		call ori_call_address
		pushad
		mov edi_value, eax
	}

	// If the result of the call is not zero, then we are looking at a player
	// Create a mouse event to simulate the left mouse button being pressed down and send it to the game
	// Otherwise, raise the mouse button up so we stop firing
	if (edi_value != 0) {
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(INPUT));
	}
	else {
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(INPUT));
	}

	// Restore the registers and jump back to original code
	_asm {
		popad
		jmp ori_jump_address
	}
}

// When our DLL is attached, unprotect the memory at the code we wish to write at
// Then set the first opcode to E9, or jump
// Caculate the location using the formula: new_location - original_location+5
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	DWORD old_protect;
	unsigned char* hook_location = (unsigned char*)0x0040AD9D;

	if (fdwReason == DLL_PROCESS_ATTACH) {
		VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
		*hook_location = 0xE9;
		*(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5);
	}

	return true;
}
