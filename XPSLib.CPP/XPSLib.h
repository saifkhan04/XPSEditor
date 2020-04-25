#pragma once
#include "stdafx.h"
#include "ComDefinations.h"

namespace XPSLib
{
	namespace Cpp
	{
		// This is our native implementation
		// It's marked with __declspec(dllexport) 
		// to be visible from outside the DLL boundaries
		class __declspec(dllexport) XPSApi
		{
		public:
			HRESULT CreateDefaultXPSFile() const; // That's where our code goes
		};
	}
}