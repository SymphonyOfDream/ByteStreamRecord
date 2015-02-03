#pragma once


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



#undef LIBRARY_ORIONRADIOREADER_API
#if defined(_WINDLL)

   #if defined(LIBRARY_BYTESTREAMRECORDER_EXPORTS)
      #define LIBRARY_BYTESTREAMRECORDER_API __declspec(dllexport)
   #else
      #define LIBRARY_BYTESTREAMRECORDER_API __declspec(dllimport)
   #endif

#else

   #define LIBRARY_BYTESTREAMRECORDER_API

#endif



      




