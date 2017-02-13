#pragma once

#if defined(ANDROID)

#define OS_ANDROID 1

#elif defined(__APPLE__)

#include <TargetConditionals.h>
#define OS_MACOSX 1

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#define OS_IOS 1
#endif

#elif defined(__linux__)

#define OS_LINUX 1
#include <unistd.h>

#if defined(__GLIBC__) && !defined(__UCLIBC__)
#define LIBC_GLIBC 1
#endif

#elif defined(_WIN32)

#define OS_WIN 1
#include <WinSock2.h>
#include <windows.h>
#else

#error Please add support for your platform in build_config.h

#endif

#if defined(OS_ANDROID)
#define STD_STRING_ITERATOR_IS_CHAR_POINTER
#define BASE_STRING16_ITERATOR_IS_CHAR16_POINTER
#endif