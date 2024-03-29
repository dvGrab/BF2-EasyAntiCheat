#pragma once

#include "Main.h"

#include <eos_sdk.h>
#include <eos_version.h>
#include <eos_anticheatclient.h>

#pragma comment(lib, "EOSSDK-Win32-Shipping.lib")

class c_eos {
private:
	EOS_HPlatform PlatformHandle = nullptr;
	EOS_HAntiCheatClient AntiCheatClientHandle = nullptr;

public:
	void init();
	void print_version();
	void patch_revision();
};
extern c_eos* eos;
