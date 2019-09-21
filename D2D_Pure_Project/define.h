#pragma once

#define SafeRelease(p) {if(p) {(p)->Release(); (p) = nullptr;}}
#define SafeDelete(p) {if(p) delete(p); (p) = nullptr;}
#define SafeDeleteClass(p) { if(p) {(p)->Release(); delete(p);} (p) = nullptr;}

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

#ifndef Assert
#if defined(DEBUG) || defined(_DEBUG)
#define Assert(b) do { if (!(b)) { OutputDebugStringA("Assert : " #b "\n"); }} while(0)
#else
#define Assert(b)
#endif	//	DEBUG || _DEBUG
#endif

#define PI (float) 3.141592653589793f