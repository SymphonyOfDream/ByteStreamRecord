// PortRecorderThread.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "atlstr.h"
#include "limits.h"

#include "PortSettings.h"

#include "PublicMain.h"

#include <tchar.h>
#include <strsafe.h>


#include "SerialPortProcessor.h"

#include "CANPortProcessor.h"





extern "C" 
{


#if !defined(WINCE)
   #define DEFAULT_SERIALPORT_SPECIFICATION_TEMPLATE     L"\\\\.\\COM%d"
   #define DEFAULT_SERIALPORT_SPECIFICATION_TEMPLATE_A    "\\\\.\\COM%d"
#else
   #define DEFAULT_SERIALPORT_SPECIFICATION_TEMPLATE     L"COM%d:"
   #define DEFAULT_SERIALPORT_SPECIFICATION_TEMPLATE_A    "COM%d:"
#endif

#if defined (S100)
   #define DEFAULT_CANPORT_SPECIFICATION_TEMPLATE     L"CAN%d:"
#endif





static bool _bInitialized = false;
BOOL _abThreadStopArray[THREAD_MAX];


void ErrorHandler(LPTSTR lpszFunction);



LIBRARY_BYTESTREAMRECORDER_API 
void PortRecorder_Initialize(void)
{
    memset(g_aPortsToRecord, 0, sizeof(g_aPortsToRecord));

	g_iPortsCount = 0;

    memset(_abThreadStopArray, FALSE, _countof(_abThreadStopArray));

    _bInitialized = true;
}



// _AddSerialPort* expect Stop Bits value to be
// set via .NET's enum.  This means the values MUST be 
// as follows when sent to these methods:

/***FROM .NET:
	public enum StopBits
	{
		// Summary:
		//     No stop bits are used. This value is not supported. Setting the System.IO.Ports.SerialPort.StopBits
		//     property to System.IO.Ports.StopBits.None raises an System.ArgumentOutOfRangeException.
		None = 0,
		//
		// Summary:
		//     One stop bit is used.
		One = 1,
		//
		// Summary:
		//     Two stop bits are used.
		Two = 2,
		//
		// Summary:
		//     1.5 stop bits are used.
		OnePointFive = 3,
	}
*/

#if defined(S100)

LIBRARY_BYTESTREAMRECORDER_API 
int PortRecorder_AddJ1939Port(int iCANPortNumber,
                              int iCANBaudRate)
{
   SPortSettings* pPort = &(g_aPortsToRecord[g_iPortsCount]);

	pPort->m_bIsCANPort = TRUE;

	pPort->m_iComPortNumber = iCANPortNumber;
	
	swprintf(pPort->m_wszComPort, 
		      DEFAULT_CANPORT_SPECIFICATION_TEMPLATE,
			   iCANPortNumber);

	pPort->m_iBaudRate = iCANBaudRate;
	pPort->m_iDataBits = 0; // Not used
	pPort->m_iParity = 0; // Not used
	pPort->m_iStopBits = 0; // Not used
	pPort->m_iFlowControl = 0; // Not used

	return g_iPortsCount++;
}

#endif



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
							   int iFlowControl)
{
   SPortSettings* pPort = &(g_aPortsToRecord[g_iPortsCount]);

	pPort->m_bIsCANPort = FALSE;

	pPort->m_iComPortNumber = iComPortNumber;
	
	swprintf(pPort->m_wszComPort, 
		     DEFAULT_SERIALPORT_SPECIFICATION_TEMPLATE,
			 iComPortNumber);

	pPort->m_iBaudRate = iBaudRate;
	pPort->m_iDataBits = iDataBits;
	pPort->m_iParity = iParity;

	// The case values are taken from .NET definitions
    switch (iStopBits)
    {
        case 1:
			pPort->m_iStopBits = ONESTOPBIT;
            break;

        case 2:
			pPort->m_iStopBits = TWOSTOPBITS;
            break;

		case 3:
			pPort->m_iStopBits = ONE5STOPBITS;
            break;
    }

	pPort->m_iFlowControl = iFlowControl;

	return g_iPortsCount++;
}



// This method used for standard COM port names
// (i.e., "COM1:", etc.)
// Returns ID of Port playback object.
// Returns -1 on error.
LIBRARY_BYTESTREAMRECORDER_API 
int PortRecorder_AddNonStandardSerialPort(int iComPortNumber,
										   const wchar_t* wszComPort,
										   int iBaudRate,
										   int iDataBits,
										   int iParity,
										   int iStopBits,
										   int iFlowControl)
{
   SPortSettings* pPort = &(g_aPortsToRecord[g_iPortsCount]);

	pPort->m_bIsCANPort = FALSE;

	pPort->m_iComPortNumber = iComPortNumber;
	wcscpy(pPort->m_wszComPort, wszComPort);
	pPort->m_iBaudRate = iBaudRate;
	pPort->m_iDataBits = iDataBits;
	pPort->m_iParity = iParity;

	// The case values are taken from .NET definitions
    switch (iStopBits)
    {
        case 1:
			pPort->m_iStopBits = ONESTOPBIT;
            break;

        case 2:
			pPort->m_iStopBits = TWOSTOPBITS;
            break;

		case 3:
			pPort->m_iStopBits = ONE5STOPBITS;
            break;
    }

	pPort->m_iFlowControl = iFlowControl;

	return g_iPortsCount++;
}


LIBRARY_BYTESTREAMRECORDER_API 
void PortRecorder_DeInitialize(void)
{
    PortRecorder_StopRecording();
    _bInitialized = false;
}



LIBRARY_BYTESTREAMRECORDER_API 
DWORD PortRecorder_GetTotalBytesRecorded(int iPortRecorderObjectID)
{
	if (iPortRecorderObjectID < 0 || iPortRecorderObjectID >= g_iPortsCount)
		return 0;

	return g_aPortsToRecord[iPortRecorderObjectID].m_dwTotalBytesRead;
}


LIBRARY_BYTESTREAMRECORDER_API 
int PortRecorder_StartRecording(void)
{
    if (!_bInitialized)
        return -1;

    HANDLE  ahThreadArray[THREAD_MAX]; 
    memset(ahThreadArray, NULL, sizeof(ahThreadArray));

    DWORD   adwThreadIdArray[THREAD_MAX];
    memset(adwThreadIdArray, 0, sizeof(adwThreadIdArray));

    // Call into thread launching code
    // Launching code will create a thread for every port in g_aPortsToRecord
    int threadIdx = 0;
    BOOL bStartThreads;
    bStartThreads =true;
    int iResult = 0;
    DWORD dw = 0;
    for (int portSettingsIdx = 0; portSettingsIdx < g_iPortsCount; ++portSettingsIdx) 
    {
        SPortSettings* pNextPort = &(g_aPortsToRecord[portSettingsIdx]);

        int iRC;
        if (!pNextPort->m_bIsCANPort)
           iRC = OpenSerialPort(*pNextPort);
#if defined(S100)
        else
           iRC = OpenCANPort(*pNextPort);
#endif

        if (iRC)
           break;



        // Create the thread to begin execution later

        if (!pNextPort->m_bIsCANPort)
        {
           ahThreadArray[threadIdx] = CreateThread( 
               NULL,                   // default security attributes
               0,                      // use default stack size  
               ThreadProc,       // thread function name
               pNextPort,          // argument to thread function 
               CREATE_SUSPENDED,    // we'll check for creation 
               &adwThreadIdArray[threadIdx]);   // returns the thread identifier 
        }
#if defined(S100)
        else
        {
           ahThreadArray[threadIdx] = CreateThread( 
               NULL,                   // default security attributes
               0,                      // use default stack size  
               CANThreadProc,       // thread function name
               pNextPort,          // argument to thread function 
               CREATE_SUSPENDED,    // we'll check for creation 
               &adwThreadIdArray[threadIdx]);   // returns the thread identifier 
        }
#endif

        // Check the return value for success.
        // If CreateThread fails, terminate execution. 
        // This will automatically clean up threads and memory. 

        if (ahThreadArray[threadIdx] != NULL) 
        {
           // It's very important that our threads are NOT delayed by
           // the client's GUI thread for whatever reason.
           ::SetThreadPriority(ahThreadArray[threadIdx], THREAD_PRIORITY_ABOVE_NORMAL);
        }
        else
        {
            // error creating the thread; abort, returning the port # + 4000
            iResult = (pNextPort->m_iComPortNumber + 4000);
            bStartThreads = false;
            break;
        }

        ++threadIdx;
    }  // for (int portSettingsIdx = 0; portSettingsIdx < g_iPortsCount; ++portSettingsIdx)

    // Each created thread will open its own single port to record and start recording data.

   if (bStartThreads) 
   {
      g_dwRecordStartMilliseconds = ::GetTickCount();

      for (int idx = 0; idx < threadIdx; ++idx) 
      {
         if (ResumeThread(ahThreadArray[idx]) == -1) 
         {
            PortRecorder_StopRecording();
            return 2;
         }
      }
   }

   return iResult;
}


void ErrorHandler(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code.

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dw,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpMsgBuf,
				0, NULL );

    // Display the error message.

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    // Free the error-handling buffer allocations.

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

LIBRARY_BYTESTREAMRECORDER_API 
int PortRecorder_StopRecording(void)
{
    if (!_bInitialized)
        return -1;

    // Call into thread launching code
    // Launching code will set a flag for all create threads' thread loops to end
    // Each running thread will dump out of it's loop and close the serial port prior to returning

    for (int idx = 0; idx < g_iPortsCount; ++idx)
    {
        SPortSettings* pNextPort = &(g_aPortsToRecord[idx]);
        pNextPort->m_bStopThread = TRUE;
    }

    return 0;
}

};
