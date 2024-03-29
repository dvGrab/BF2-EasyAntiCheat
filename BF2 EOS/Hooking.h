#pragma once

#include "Main.h"

#include <unordered_map>
#include <string>

#pragma comment(lib, "detours.lib")
#include "detours.h"

class CHooking {

public:
	std::unordered_map<std::string, DWORD> Functions;

	void Begin();
	void Place(PVOID* ppPointer, PVOID pDetour);
	void End();

	DWORD GetModuleFunction(LPCSTR module, LPCSTR name);
};
