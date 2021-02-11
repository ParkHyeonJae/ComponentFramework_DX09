#pragma once
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <string>
#include <iostream>


#include "SDKsound.h"
#include "SDKwavefile.h"

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "dsound.lib")

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#define g_DEVICE DXUTGetD3D9Device()
#define g_DeltaTime DXUTGetElapsedTime()

#define g_SAFE_DELETE(a) delete a; a= nullptr;
#define g_SAFE_RELEASE(a) a->Release();

#define PURE = 0

const float WINSIZE_X = 1280;
const float WINSIZE_Y = 720;

#define WINHALF_VECTOR Vector2(WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f)

#define VECTOR2_ZERO Vector2(0,0)
#define VECTOR2_HALF Vector2(0.5, 0.5)
#define VECTOR2_ONE Vector2(1.0, 1.0)


using Vector2 = D3DXVECTOR2;
using Matrix = D3DXMATRIX;
using Color = D3DCOLOR;


using std::string;
using std::map;
using std::vector;
using std::make_pair;

#include "cMath.h"
using namespace Math;


#include "cFlowBase.h"
#include "cSingleton.h"
#include "cInputManager.h"
#include "cCameraManager.h"
#include "cImageManager.h"