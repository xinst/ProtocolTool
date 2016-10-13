//*************************************************************************
// SGFPlatform.h 2016-3-23 10:21
// Author: Xin Songtao
// Purpose: 
//
//*************************************************************************
#ifndef SGF_PLATFORM_H__
#define SGF_PLATFORM_H__


#include <stdint.h>
#include <assert.h>

// Integer formats of fixed bit width

typedef uint64_t	ui64;
typedef uint32_t	ui32;
typedef uint16_t	ui16;
typedef uint8_t		ui8;

typedef int64_t		i64;
typedef int32_t		i32;
typedef int16_t		i16;
typedef int8_t		i8;

typedef int			SOCK_FD;

#define SGF_PF_WINDOWS	1
#define SGF_PF_LINUX	2

#ifdef WIN32

#define SGF_PLATFORM SGF_PF_WINDOWS

#else

#define SGF_PLATFORM SGF_PF_LINUX

#endif // WIN32


#if SGF_PLATFORM == SGF_PF_WINDOWS
#define SGF_SPRINTF sprintf_s
#define SGF_STRICMP stricmp
#define SGF_SLEEP(s) Sleep(s)
#else
#define SGF_SPRINTF snprintf
#define SGF_STRICMP strcasecmp
#define SGF_SLEEP(s) usleep(s)
#endif

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

#endif // SGF_PLATFORM_H__

