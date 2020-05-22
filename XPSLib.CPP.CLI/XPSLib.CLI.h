#pragma once

namespace XPSLib
{
	namespace Cpp
	{
		// First a Forward Declaration to Cpp::Logic class:
		class XPSApi; // This allows us to mention it in this header file
					 // without actually including the native version of Logic.h

		namespace CLI
		{
			// Next is the managed wrapper of Logic:
			public ref class XPSApi
			{
			public:
				// Managed wrappers are generally less concerned 
				// with copy constructors and operators, since .NET will
				// not call them most of the time.
				// The methods that do actually matter are:
				// The constructor, the "destructor" and the finalizer
				XPSApi();
				~XPSApi();
				!XPSApi();
				
				int SavefiletoLocation(System::String^ path1);
				int CreateBlankXPSFile();
				int ChangePageSize(float width, float height);
				int SaveChanges();
				int InsertPicture(System::String^ imagepath);
				int InsertText(System::String^ path1,float size);
				void Destroy(); // Helper function
				static void InitializeLibrary(System::String^ path);
			private:
				// Pointer to our implementation
				Cpp::XPSApi* _impl;
				
			};
		}
	}
}