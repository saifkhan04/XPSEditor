// XPSLib.CPP.CLI.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "XPSLib.CLI.h"
#include "..\XPSLib.CPP\XPSLib.h"

using namespace std;

XPSLib::Cpp::CLI::XPSApi::XPSApi()
	: _impl(new Cpp::XPSApi())
	// Allocate some memory for the native implementation
{
}

int XPSLib::Cpp::CLI::XPSApi::CreateDefaultXPSFile()
{
	return _impl->CreateDefaultXPSFile(); // Call corresponding native function
}

void XPSLib::Cpp::CLI::XPSApi::Destroy()
{
	if (_impl != nullptr)
	{
		delete _impl;
		_impl = nullptr;
	}
}

XPSLib::Cpp::CLI::XPSApi::~XPSApi()
{
	// C++ CLI compiler will automaticly make all ref classes implement IDisposable.
	// The default implementation will invoke this method + call GC.SuspendFinalize.
	Destroy(); // Clean-up any native resources 
}

XPSLib::Cpp::CLI::XPSApi::!XPSApi()
{
	// This is the finalizer
	// It's essentially a fail-safe, and will get called
	// in case Logic was not used inside a using block.
	Destroy(); // Clean-up any native resources 
}

string ManagedStringToStdString(System::String^ str)
{
	cli::array<unsigned char>^ bytes = System::Text::Encoding::ASCII->GetBytes(str);
	pin_ptr<unsigned char> pinned = &bytes[0];
	std::string nativeString((char*)pinned, bytes->Length);
	return nativeString;
}

void XPSLib::Cpp::CLI::XPSApi::InitializeLibrary(System::String^ path)
{
	string nativePath = ManagedStringToStdString(path);
	LoadLibrary(nativePath.c_str()); // Actually load the delayed library from specific location
}



