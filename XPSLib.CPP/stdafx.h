// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <Windows.h>
#include <wincodec.h>
#include "XpsObjectModel_1.h"
#include "xpsprint.h"
#include <Wincodecsdk.h>
#include <comdef.h>
#include <string>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <memory>

typedef unsigned char JOCTET;
#define GETJOCTET(value)  (value)

using namespace std;

#define VNUM_STR "1.0"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>

// TODO: reference additional headers your program requires here
