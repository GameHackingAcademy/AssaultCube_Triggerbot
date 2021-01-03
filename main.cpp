#include <Windows.h>

DWORD ori_call_address = 0x4607C0;
DWORD ori_jump_address = 0x0040ADA2;

INPUT input = { 0 };
DWORD edi_value = 0;

__declspec(naked) void codecave() {

	__asm {
		call ori_call_address
		pushad
		mov edi_value, eax
	}

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

	_asm {
		popad
		jmp ori_jump_address
	}
}

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
