#pragma once

#include "build_config.h"

#ifdef OS_WIN
#if defined(AV_IMPLEMENTATION_TEST)
#define AV_EXPORT
#else
#if defined(AV_IMPLEMENTATION)
#define AV_EXPORT __declspec(dllexport)
#else
#define AV_EXPORT __declspec(dllimport)
#endif  // defined(AV_IMPLEMENTATION)
#endif // defined(AV_IMPLEMENTATION_TEST)
#else
#define AV_EXPORT
#endif

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

#ifdef WIN32

#ifdef __cplusplus
extern "C" {
#endif

const char* AVAPI_GetVersion();
void* AVAPI_CreateContext();
void  AVAPI_EnableCrashReport(bool enable, bool showUi);

#ifdef __cplusplus
}
#endif

typedef const char* (*PROC_AVAPI_GetVersion)();
typedef void* (*PROC_AVAPI_CreateContext)();
typedef void (*PROC_AVAPI_EnableCrashReport)(bool enable, bool showUi);

#endif