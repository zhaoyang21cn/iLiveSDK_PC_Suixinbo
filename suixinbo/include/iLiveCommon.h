#ifndef iLiveCommon_h_
#define iLiveCommon_h_

#include <assert.h>
#include <stdarg.h>
#include <Windows.h>

#ifdef iLiveSDKImpl
#define iLiveAPI __declspec(dllexport)
#else
#define iLiveAPI __declspec(dllimport)
#endif

#define	ILIVE_MININUM_STRING_CAPACITY		32
#define	ILIVE_INVALID_INDEX				-1

typedef size_t				sizet;
typedef wchar_t				wchar;

typedef signed char			int8;
typedef signed short		int16;
typedef signed int			int32;
typedef signed long long	int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

#define SafeFree(p) { free(p); (p) = 0; }
#define SafeDelete(p) {delete (p); (p) = 0;}
#define SafeDeleteArr(pArr) {delete[] (pArr); (pArr) = 0;}

template<typename T> inline void
iliveSwap(T& a, T&b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

template<typename T> inline T
iliveMin(const T& v1, const T& v2)
{
	return v1<v2 ? v1 : v2;
}

template<typename T> inline T
iliveMax(const T& v1, const T& v2)
{
	return v1>v2 ? v1 : v2;
}

template<typename T> inline T
iliveClamp(const T& x, const T& min, const T& max)
{
	assert(max >= min);
	return iliveMin<T>( max, iliveMax(min, x) );
}

iLiveAPI void*		iliveMalloc(sizet size);
iLiveAPI void		iliveFree(void* block);
iLiveAPI void		iliveMemCpy(void* dst, const void* src, int n);
iLiveAPI void		iliveMemCpy(char* dst, const char* src, int n);
iLiveAPI void		iliveMemCpy(wchar* dst, const wchar* src, int n);
iLiveAPI int		iliveStrLen(const char* s);
iLiveAPI int		iliveStrLen(const wchar* s);
iLiveAPI void		iliveMemSet(char* dst, char ch, int n);
iLiveAPI void		iliveMemSet(wchar* dst, wchar ch, int n);
iLiveAPI void		iliveMemMove(char* dst, const char* src, int n);
iLiveAPI void		iliveMemMove(wchar* dst, const wchar* src, int n);
iLiveAPI char		iliveToLower(char ch);
iLiveAPI wchar		iliveToLower(wchar ch);
iLiveAPI char		iliveToUpper(char ch);
iLiveAPI wchar		iliveToUpper(wchar ch);
iLiveAPI int		iliveStrCmp(const char* lhs, const char* rhs);
iLiveAPI int		iliveStrCmp(const wchar* lhs, const wchar* rhs);
iLiveAPI int		iliveStrIgnoreCaseCmp(const char* lhs, const char* rhs);
iLiveAPI int		iliveStrIgnoreCaseCmp(const wchar* lhs, const wchar* rhs);
iLiveAPI int		iliveVsnprintf(char* buf, int count, const char* format, va_list args);
iLiveAPI int		iliveVsnprintf(wchar* buf, int count, const wchar* format, va_list args);
iLiveAPI int		iliveMemCmp(const char* buf1, const char* buf2, int count);
iLiveAPI int		iliveMemCmp(const wchar* buf1, const wchar* buf2, int count);
iLiveAPI char*		iliveMemChr(const char* buf, char ch, int count);
iLiveAPI wchar*		iliveMemChr(const wchar* buf, wchar ch, int count);

#endif//iLiveCommon_h_