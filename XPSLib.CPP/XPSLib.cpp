#include "stdafx.h"
#include "XPSLib.h"

HRESULT XPSLib::Cpp::XPSApi::CreateDefaultXPSFile() const
{
	HRESULT hr = S_OK;

	IXpsOMObjectFactory1_t				xpsFactory(NULL);
	IXpsOMPackage1_t					xpsPackage(NULL);

	hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	if (SUCCEEDED(hr)) {
		hr = CoCreateInstance(
			__uuidof(XpsOMObjectFactory),
			NULL,
			CLSCTX_INPROC_SERVER,
			__uuidof(IXpsOMObjectFactory1_t),
			reinterpret_cast<LPVOID*>(&xpsFactory));
	}

	hr = xpsFactory->CreatePackageFromFile1(
		L"C:\\Users\\khansai\\Desktop\\test.xps",
		FALSE,
		&xpsPackage);

	hr = xpsPackage->WriteToFile(
		L"C:\\Users\\khansai\\Desktop\\output.xps",
		NULL,                    // LPSECURITY_ATTRIBUTES
		FILE_ATTRIBUTE_NORMAL,
		FALSE                    // Optimize Markup Size
	);

	return hr;
}


