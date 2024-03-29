#include "Hooking.h"

void CHooking::Begin()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
}

void CHooking::Place(PVOID* ppPointer, PVOID pDetour)
{
	DetourAttach(ppPointer, pDetour);
}

void CHooking::End()
{
	DetourTransactionCommit();
}

DWORD CHooking::GetModuleFunction(LPCSTR module, LPCSTR name)
{
	auto handle = GetModuleHandleA(module);

	if (!handle)
		return 0xfff;

	auto function = reinterpret_cast<DWORD>(GetProcAddress(handle, name));

	if (!function)
		return 0xfff;

	this->Functions[name] = function;

	return function;
}