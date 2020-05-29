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
			XPSApi() :m_xpsPackage(NULL),m_page(NULL){

			}
			
			~XPSApi()
			{
				if (m_xpsPackage) {
					m_xpsPackage->Release();
					m_xpsPackage = NULL;
				}
				if (m_page) {
					m_page->Release();
					m_page = NULL;
				}
			}
		   
			HRESULT SavefiletoLocation(string str) const; // That's where our code goes
			HRESULT CreateBlankXPSFile() const;
			HRESULT ChangePageSize(float width, float height) const;
			HRESULT SaveChanges(string str) const;
			HRESULT InsertPicture(string str1) const;
			HRESULT InsertText(string str1,float size,string str2) const;
			HRESULT
				WriteText_AddTextToPage(
					__in    IXpsOMObjectFactory   *xpsFactory,
					// The font resource to use for this run
					__in    IXpsOMFontResource    *xpsFont,
					// The font size
					__in    float                 fontEmSize,
					// The solid color brush to use for the font
					__in    IXpsOMSolidColorBrush *xpsBrush,
					// The starting location of this glyph run
					__in    XPS_POINT             *origin,
					// The text to use for this run
					__in    LPCWSTR               unicodeString,
					// The page on which to write this glyph run
					__in IXpsOMPage            *xpsPage) const;
			HRESULT GetImageProperties(
				__in IStream_t	imageStream,
				__out XPS_SIZE &imagesize,
				__out FLOAT &dpiX,
				__out FLOAT &dpiY
			) const;
			HRESULT XPSLib::Cpp::XPSApi::CreateRectanglePath(
				__in  IXpsOMObjectFactory1_t   &xpsFactory,
				__in  const XPS_RECT			*rect,
				__out IXpsOMPath_t           &rectPath
			) const;
		private:
			IXpsOMPackage1 *m_xpsPackage;
			IXpsOMPage      *m_page;

		    static string m_pathcopy;
		};

		string XPSApi::m_pathcopy =" ";
		
	}
}