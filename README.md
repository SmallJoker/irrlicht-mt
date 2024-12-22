IrrlichtMt fork
===============

IrrlichtMt is the 3D engine of [Minetest](https://github.com/minetest).
It is based on the [Irrlicht Engine](https://irrlicht.sourceforge.io/) but is now developed independently.

The original [IrrlichtMt](https://github.com/minetest/irrlicht) repository has been merged into the Minetest tree.
The goal of this repository is to continue the spirit of a standalone library by backporting crucial fixes from Minetest and the upstream Irrlicht source.


Build
-----

The build system is CMake.

The following libraries are required to be installed:

* zlib, libPNG, libJPEG
* OpenGL
  * or on mobile: OpenGL ES (can be optionally enabled on desktop too)
* on Unix: X11
* SDL2 (see below)

Aside from standard search options (`ZLIB_INCLUDE_DIR`, `ZLIB_LIBRARY`, ...) the following options are available:

* `BUILD_SHARED_LIBS` (default: `ON`) - Build IrrlichtMt as a shared library
* `BUILD_EXAMPLES` (default: `OFF`) - Build example applications
* `ENABLE_OPENGL` - Enable OpenGL driver
* `ENABLE_OPENGL3` (default: `OFF`) - Enable OpenGL 3+ driver
* `ENABLE_GLES2` - Enable OpenGL ES 2+ driver
* `USE_SDL2` (default: platform-dependent, usually `ON`) - Use SDL2 instead of older native device code

Note: if `zconf.h` cannot be found due to separate (out-of-tree) build directories,
do specify two paths in the same CMake option. e.g. `/path/to/zlib;/path/to/zlib_build`.

CMake will create the file `${BUILD_DIR}/cmake/IrrlichtMtTargets.cmake` which it can then be imported from another project by pointing `find_package()` or the `CMAKE_PREFIX_PATH` variable to the build directory.


### Build on Linux

	git clone https://github.com/THIS_REPO/NAME
	cd irrlicht
	cmake . -DBUILD_SHARED_LIBS=OFF
	make -j


### Build on Windows

It is highly recommended to use vcpkg as package manager.

After you successfully built vcpkg you can easily install the required libraries:

	vcpkg install zlib libjpeg-turbo libpng sdl2 --triplet x64-windows

Run the following script in PowerShell:

	git clone https://github.com/minetest/irrlicht
	cd irrlicht
	cmake -B build -G "Visual Studio 17 2022" -A "Win64" -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake -DBUILD_SHARED_LIBS=OFF
	cmake --build build --config Release


Platforms
---------

We aim to support these platforms:

* Windows via MinGW
* Linux (GL or GLES)
* macOS
* Android

This doesn't mean other platforms don't work or won't be supported, if you find something that doesn't work contributions are welcome.

Compatibility matrix
--------------------

Driver (rows) vs Device (columns)

|                           | SDL [1]  | Linux [2]      | OSX [3]          | Win32 [4]       |
|---------------------------|----------|----------------|------------------|-----------------|
| OpenGL 1.2 (to 2.1)       | Works    | Works (GLX)    | Works (NSOpenGL) | Works (WGL)     |
| OpenGL 3.2+               | Works    | Testing (GLX)  | Not implemented  | Testing (WGL)   |
| OpenGL ES 2.x             | Works    | Untested (EGL) | Not implemented  | Untested (EGL)  |
| WebGL 1                   | Untested | Untested (EGL) | Not implemented  | Not implemented |
| Null (no graphics output) | Works    | Works          | Works            | Works           |

Notes:

* [1] `CIrrDeviceSDL`: supports Android, Linux, macOS, Windows
* [2] `CIrrDeviceLinux`: supports Linux
* [3] `CIrrDeviceOSX`: supports macOS
* [4] `CIrrDeviceWin32`: supports Windows


License
-------

The license of the Irrlicht Engine is based on the zlib/libpng license and applies to this fork, too.

	The Irrlicht Engine License
	===========================

	Copyright (C) 2002-2012 Nikolaus Gebhardt

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	 claim that you wrote the original software. If you use this software
	 in a product, an acknowledgement in the product documentation would be
	 appreciated but is not required.
	2. Altered source versions must be clearly marked as such, and must not be
	 misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
