#include "EOS.h"
#include "Hooking.h"

void c_eos::init()
{

	EOS_InitializeOptions SDKOptions = {};
	SDKOptions.ApiVersion = EOS_INITIALIZE_API_LATEST;
	SDKOptions.AllocateMemoryFunction = nullptr;
	SDKOptions.ReallocateMemoryFunction = nullptr;
	SDKOptions.ReleaseMemoryFunction = nullptr;
	SDKOptions.ProductName = "Battlefield 2 EOS";
	SDKOptions.ProductVersion = "1.0";
	SDKOptions.Reserved = nullptr;
	SDKOptions.SystemInitializeOptions = nullptr;
	SDKOptions.OverrideThreadAffinity = nullptr;

	EOS_EResult InitResult = EOS_Initialize(&SDKOptions);

	if (InitResult != EOS_EResult::EOS_Success) {
		printf_s("Failed to initialized EOS service.");
	}
	else
		printf_s("EOS SDK intitialized.\n");

	static constexpr char EncryptionKey[] = "1111111111111111111111111111111111111111111111111111111111111111";

	EOS_Platform_Options PlatformOptions = {};
	PlatformOptions.ApiVersion = EOS_PLATFORM_OPTIONS_API_LATEST;
	PlatformOptions.bIsServer = EOS_FALSE;
	PlatformOptions.EncryptionKey = EncryptionKey;
	PlatformOptions.OverrideCountryCode = nullptr;
	PlatformOptions.OverrideLocaleCode = nullptr;
	PlatformOptions.Flags = EOS_PF_DISABLE_OVERLAY; // no overlay needed for the server app
	PlatformOptions.CacheDirectory = "C:\\";

	PlatformOptions.ProductId = "d634633b582c465cbfc3231b88002822";
	PlatformOptions.SandboxId = "3d95bb0c575d46a094a6258365f0cee0";
	PlatformOptions.DeploymentId = "62bac0215eab4b8d88b5806124c2e469";

	PlatformOptions.ClientCredentials.ClientId = "nullptr";
	PlatformOptions.ClientCredentials.ClientSecret = "nullptr";

	PlatformOptions.Reserved = NULL;

	this->PlatformHandle = EOS_Platform_Create(&PlatformOptions);

	if (this->PlatformHandle != nullptr)
		printf_s("EOS Platform handle has been created.\n");
	else
		printf_s("Failed to initialize EOS platform.\n");

	this->AntiCheatClientHandle = EOS_Platform_GetAntiCheatClientInterface(this->PlatformHandle);

	if (this->AntiCheatClientHandle != nullptr) {
		printf_s("EOS Anti Cheat handle has been initialized.\n");
		this->patch_revision();
	}
	else
	{
		MessageBoxA(NULL, "Failed to initialize EAC, please start the game via EAC Bootstrapper.", "Error", MB_ICONERROR | MB_OK);
		//exit(1);
	}
	
}

void c_eos::print_version()
{
	printf_s("EOS Version: %s.\n", EOS_GetVersion());
}

typedef int(__fastcall* readstr)(int a1, int* a2, const void* a3, int a4);
readstr ReadFunction;

int __fastcall readfunc(int a1, int* a2, const char* a3, int a4)
{
	std::string output(a3);

	if(output.find("\\sdkrevision\\") != std::string::npos)
		a3 = "\\eacrevision\\";

	return ReadFunction(a1, a2, a3, a4);
}

void c_eos::patch_revision()
{
	auto handle = (DWORD)GetModuleHandleA("BF2.exe");
	ReadFunction = (readstr)(0x675300); 

	CHooking* Hooks = new CHooking();

	Hooks->Begin();
	Hooks->Place(&(PVOID&)ReadFunction, readfunc);
	Hooks->End();
}   