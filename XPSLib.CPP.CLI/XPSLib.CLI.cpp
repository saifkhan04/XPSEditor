// XPSLib.CPP.CLI.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "XPSLib.CLI.h"
#include "..\XPSLib.CPP\XPSLib.h"

using namespace std;
string ManagedStringToStdString(System::String^ str)
{
	cli::array<unsigned char>^ bytes = System::Text::Encoding::ASCII->GetBytes(str);
	pin_ptr<unsigned char> pinned = &bytes[0];
	std::string nativeString((char*)pinned, bytes->Length);
	return nativeString;
}

XPSLib::Cpp::CLI::XPSApi::XPSApi()
	: _impl(new Cpp::XPSApi())
	// Allocate some memory for the native implementation
{

       }
int XPSLib::Cpp::CLI::XPSApi::SavefiletoLocation(System::String^ path1)
{
	string str1 = ManagedStringToStdString(path1);

	return _impl->SavefiletoLocation(str1); // Call corresponding native function
}
int XPSLib::Cpp::CLI::XPSApi::InsertText(System::String^ path1,float size)
{
	string str1 = ManagedStringToStdString(path1);

	return _impl->InsertText(str1,size); // Call corresponding native function
}
int XPSLib::Cpp::CLI::XPSApi::CreateBlankXPSFile()
{
	return _impl->CreateBlankXPSFile(); // Call corresponding native function
}
int XPSLib::Cpp::CLI::XPSApi::ChangePageSize(float width,float height)
{
	return _impl->ChangePageSize(width,height); // Call corresponding native function
}
int XPSLib::Cpp::CLI::XPSApi::SaveChanges()
{
	return _impl->SaveChanges(); // Call corresponding native function
}
int XPSLib::Cpp::CLI::XPSApi::InsertPicture(System::String^ path1)
{
	string str1 = ManagedStringToStdString(path1);
	
	return _impl->InsertPicture(str1); // Call corresponding native function
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


void XPSLib::Cpp::CLI::XPSApi::InitializeLibrary(System::String^ path)
{
	string nativePath = ManagedStringToStdString(path);
	LoadLibrary(nativePath.c_str()); // Actually load the delayed library from specific location
}

