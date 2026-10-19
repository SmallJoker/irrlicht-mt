// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#pragma once

//! Irrlicht SDK Version
#define IRRLICHT_VERSION_MAJOR 1
#define IRRLICHT_VERSION_MINOR 9
#define IRRLICHT_VERSION_REVISION 19

//! Identifies the IrrlichtMt fork
#define IRRLICHT_VERSION_MT_REVISION IRRLICHT_VERSION_REVISION

#define IRRLICHT_SDK_VERSION "1.9.19-mt"

#ifdef _WIN32
#define IRRCALLCONV __stdcall
#else
#define IRRCALLCONV
#endif

#ifndef IRRLICHT_API
#define IRRLICHT_API
#endif
