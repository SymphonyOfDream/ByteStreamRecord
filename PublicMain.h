#pragma once

#include "dllmain.h"


// sized for the current string display panel
#define THREAD_MAX 15


extern "C" 
{

LIBRARY_BYTESTREAMRECORDER_API 
void PortRecorder_Initialize(void);



LIBRARY_BYTESTREAMRECORDER_API 
void PortRecorder_DeInitialize(void);


LIBRARY_BYTESTREAMRECORDER_API 
DWORD PortRecorder_GetTotalBytesRecorded(int iPortRecorderObjectID);



// This method used for standard COM port names
// (i.e., "COM1:", etc.)
// Returns ID of Port playback object.
// Returns -1 on error.
LIBRARY_BYTESTREAMRECORDER_API 
int PortRecorder_AddSerialPort(int iComPortNumber,
						       int iBaudRate,
						       int iDataBits,
						       int iParity,
						       int iStopBits,
					 	       int iFlowControl);

// This method used for non-standard COM port names
// (i.e., "CAN1:", etc.)
// Returns ID of Port playback object.
// Returns -1 on error.
LIBRARY_BYTESTREAMRECORDER_API 
int PortRecorder_AddNonStandardSerialPort(int iComPortNumber,
										  const wchar_t* wszComPort,
										  int iBaudRate,
										  int iDataBits,
										  int iParity,
										  int iStopBits,
										  int iFlowControl);



LIBRARY_BYTESTREAMRECORDER_API 
int PortRecorder_StartRecording(void);



LIBRARY_BYTESTREAMRECORDER_API 
int PortRecorder_StopRecording(void);

};
