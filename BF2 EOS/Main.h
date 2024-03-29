#pragma once

#include <Windows.h>
#include <stdio.h>
#include <thread>

extern "C" 
{ 
	__declspec(dllexport) int __stdcall Startup();
}