#pragma once
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <string>
#include <iostream>
#include <type_traits>
#include <bitset>
#include <memory>
#include <cassert>
#include <omp.h>

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
using std::bitset;
using std::list;
using std::pair;
using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::static_pointer_cast;


#include "cMath.h"
using namespace Math;

#include "cComponent.h"
#include "cTransform.h"
#include "cObject.h"
#include "IFlowBase.h"


#include "cSingleton.h"
#include "cObjectManager.h"
#include "cInputManager.h"
#include "cCameraManager.h"
#include "cImageManager.h"
#include "cRenderer.h"
