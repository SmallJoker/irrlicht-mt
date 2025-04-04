// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

static const char *const copyright = "Irrlicht Engine (c) 2002-2017 Nikolaus Gebhardt"; // put string in binary

#ifdef _IRR_WINDOWS_
#include <windows.h>
#if defined(_DEBUG) && !defined(__GNUWIN32__)
#include <crtdbg.h>
#endif // _DEBUG
#endif

#include "irrlicht.h"
#include "matrix4.h"
#include "SMaterial.h"

#ifdef _IRR_COMPILE_WITH_WINDOWS_DEVICE_
#include "CIrrDeviceWin32.h"
#endif

#ifdef _IRR_COMPILE_WITH_X11_DEVICE_
#include "CIrrDeviceLinux.h"
#endif

#ifdef _IRR_COMPILE_WITH_OSX_DEVICE_
#include "CIrrDeviceOSX.h"
#endif

#ifdef _IRR_COMPILE_WITH_SDL_DEVICE_
#include "CIrrDeviceSDL.h"
#endif

namespace irr
{
//! stub for calling createDeviceEx
IRRLICHT_API IrrlichtDevice *IRRCALLCONV createDevice(video::E_DRIVER_TYPE driverType,
		const core::dimension2d<u32> &windowSize,
		u32 bits, bool fullscreen,
		bool stencilbuffer, bool vsync, IEventReceiver *res)
{
	(void)copyright; // prevent unused variable warning

	SIrrlichtCreationParameters p;
	p.DriverType = driverType;
	p.WindowSize = windowSize;
	p.Bits = (u8)bits;
	p.Fullscreen = fullscreen;
	p.Stencilbuffer = stencilbuffer;
	p.Vsync = vsync;
	p.EventReceiver = res;

	return createDeviceEx(p);
}

extern "C" IRRLICHT_API IrrlichtDevice *IRRCALLCONV createDeviceEx(const SIrrlichtCreationParameters &params)
{

	IrrlichtDevice *dev = 0;

#ifdef _IRR_COMPILE_WITH_WINDOWS_DEVICE_
	if (params.DeviceType == EIDT_WIN32 || (!dev && params.DeviceType == EIDT_BEST))
		dev = new CIrrDeviceWin32(params);
#endif

#ifdef _IRR_COMPILE_WITH_OSX_DEVICE_
	if (params.DeviceType == EIDT_OSX || (!dev && params.DeviceType == EIDT_BEST))
		dev = new CIrrDeviceMacOSX(params);
#endif

#ifdef _IRR_COMPILE_WITH_X11_DEVICE_
	if (params.DeviceType == EIDT_X11 || (!dev && params.DeviceType == EIDT_BEST))
		dev = new CIrrDeviceLinux(params);
#endif

#ifdef _IRR_COMPILE_WITH_SDL_DEVICE_
	if (params.DeviceType == EIDT_SDL || (!dev && params.DeviceType == EIDT_BEST))
		dev = new CIrrDeviceSDL(params);
#endif

	if (dev && !dev->getVideoDriver() && params.DriverType != video::EDT_NULL) {
		dev->closeDevice(); // destroy window
		dev->run();         // consume quit message
		dev->drop();
		dev = 0;
	}

	return dev;
}

namespace core
{
const matrix4 IdentityMatrix(matrix4::EM4CONST_IDENTITY);
}

namespace video
{
const SMaterial IdentityMaterial;

extern "C" IRRLICHT_API bool IRRCALLCONV isDriverSupported(E_DRIVER_TYPE driver)
{
	switch (driver) {
	case EDT_NULL:
		return true;
#ifdef ENABLE_OPENGL3
	case EDT_OPENGL3:
		return true;
#endif
#ifdef _IRR_COMPILE_WITH_OPENGL_
	case EDT_OPENGL:
		return true;
#endif
#ifdef _IRR_COMPILE_WITH_OGLES2_
	case EDT_OGLES2:
		return true;
#endif
#ifdef _IRR_COMPILE_WITH_WEBGL1_
	case EDT_WEBGL1:
		return true;
#endif
	default:
		return false;
	}
}
}

} // end namespace irr

#if defined(_IRR_WINDOWS_API_) && !defined(_IRR_STATIC_LIB_)

BOOL APIENTRY DllMain(HANDLE hModule,
		DWORD ul_reason_for_call,
		LPVOID lpReserved)
{
	// _crtBreakAlloc = 139;

	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
#if defined(_DEBUG) && !defined(__GNUWIN32__)
		_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif // defined(_IRR_WINDOWS_)
