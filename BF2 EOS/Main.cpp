#include "Main.h"
#include "EOS.h"


int __stdcall Startup()
{
	c_eos* eos = new c_eos();

	AllocConsole();

	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	SetConsoleTitleA("BF2 EOS - Debug Console");

	/* Debug print if EOS initialized. */
		
	eos->init();

	eos->print_version();

	return 1;
}

BOOL DllMain(HINSTANCE Instance, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		
			std::thread init(Startup);
			init.detach();

		break;
	}

	return 1;
}
