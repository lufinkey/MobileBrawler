
#pragma once

#if defined(__APPLE__)
	#include "TargetConditionals.h"
#endif

#if defined(TARGET_OS_IPHONE)
	#define TARGETPLATFORM_IOS
#elif defined(TARGET_IPHONE_SIMULATOR)
	#define TARGETPLATFORM_IOS
	#define TARGETPLATFORM_IOS_SIMULATOR
#elif defined (__ANDROID__)
	#define TARGETPLATFORM_ANDROID
#endif

#if defined(TARGETPLATFORM_IOS) || defined(TARGETPLATFORM_ANDROID)
	#define TARGETPLATFORM_MOBILE
#endif

#if defined(_WIN32) || defined(__MINGW32__)
	#define TARGETPLATFORM_WINDOWS
#elif defined(TARGET_OS_MAC)
	#define TARGETPLATFORM_MAC
#elif defined(__linux__) || defined(__linux)
	#define TARGETPLATFORM_LINUX
#elif defined(__unix__) || defined(__unix)
	#define TARGETPLATFORM_UNIX
#elif defined(__posix)
	#define TARGETPLATFORM_POSIX
#endif

#if defined(TARGETPLATFORM_WINDOWS) || defined(TARGETPLATFORM_MAC) || defined(TARGETPLATFORM_LINUX) || defined(TARGETPLATFORM_UNIX) || defined(TARGETPLATFORM_POSIX)
	#define TARGETPLATFORM_DESKTOP
#endif
