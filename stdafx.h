// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#pragma warning( disable : 4201 )

#if !defined(WINCE)

   // Modify the following defines if you have to target a platform prior to the ones specified below.
   // Refer to MSDN for the latest info on corresponding values for different platforms.
   #ifndef WINVER            // Allow use of features specific to Windows XP or later.
      #define WINVER 0x0501      // Change this to the appropriate value to target other versions of Windows.
   #endif

   #ifndef _WIN32_WINNT      // Allow use of features specific to Windows XP or later.                   
      #define _WIN32_WINNT 0x0501   // Change this to the appropriate value to target other versions of Windows.
   #endif                  

   #ifndef _WIN32_WINDOWS      // Allow use of features specific to Windows 98 or later.
      #define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
   #endif

   #ifndef _WIN32_IE         // Allow use of features specific to IE 6.0 or later.
      #define _WIN32_IE 0x0600   // Change this to the appropriate value to target other versions of IE.
   #endif

   #define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
   // Windows Header Files:
   #include <windows.h>

 
#else

   #pragma comment(linker, "/nodefaultlib:libc.lib")
   #pragma comment(linker, "/nodefaultlib:libcd.lib")

   // NOTE - this value is not strongly correlated to the Windows CE OS version being targeted
   #if !defined(WINVER)
      #define WINVER _WIN32_WCE
   #endif

   #include <ceconfig.h>
   #if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
      #define SHELL_AYGSHELL
   #endif

   #ifdef _CE_DCOM
      #define _ATL_APARTMENT_THREADED
   #endif

   #include <aygshell.h>
   #pragma comment(lib, "aygshell.lib")


   // Windows Header Files:
   #include <windows.h>


   #if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
      #ifndef _DEVICE_RESOLUTION_AWARE
         #define _DEVICE_RESOLUTION_AWARE
      #endif
   #endif

   #ifdef _DEVICE_RESOLUTION_AWARE
      #include "DeviceResolutionAware.h"
   #endif

   #if _WIN32_WCE < 0x500 && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
      #pragma comment(lib, "ccrtrtti.lib")
      #ifdef _X86_   
         #if defined(_DEBUG)
            #pragma comment(lib, "libcmtx86d.lib")
         #else
            #pragma comment(lib, "libcmtx86.lib")
         #endif
      #endif
   #endif

   #include <altcecrt.h>


#endif

#pragma warning( default : 4201 )


// TODO: reference additional headers your program requires here

// Taken from curr ver of stdlib.h
// (winmobile doesn't seem to have this macro)
#if !defined(_countof)
   #if !defined(__cplusplus)
      #define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
   #else
      extern "C++"
      {
      template <typename _CountofType, size_t _SizeOfArray>
      char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
      #define _countof(_Array) sizeof(*__countof_helper(_Array))
      }
   #endif
#endif



#include <wchar.h>



// minimum practical inbount size is 128
#define INBOUND_BUF_SIZE 512
#define OUTBOUND_BUF_SIZE 1024

#include "PortSettings.h"

#include <list>



extern const char g_aszHexStrings[][3];
extern DWORD g_dwRecordStartMilliseconds;

extern "C" 
{

int KludgeMakeLabComputerWorkDarnit(const wchar_t* wszComPort);

extern int g_iPortsCount;
extern SPortSettings g_aPortsToRecord[10];

};


// TODO: reference additional headers your program requires here

