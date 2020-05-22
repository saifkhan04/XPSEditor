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
			HRESULT SaveChanges() const;
			HRESULT InsertPicture(string str1) const;
			HRESULT InsertText(string str1,float size) const;
		private:
			IXpsOMPackage1 *m_xpsPackage;
			IXpsOMPage      *m_page;
		    static string m_pathcopy;
		};

		string XPSApi::m_pathcopy =" ";
		
	}
}