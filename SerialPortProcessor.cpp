#include "stdafx.h"

#include "PortSettings.h"


#include "SerialPortProcessor.h"




int OpenSerialPort(SPortSettings& serialPort)
{
   serialPort.m_bStopThread = FALSE;
   serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
   serialPort.m_hOutputFile = INVALID_HANDLE_VALUE;

   // Dave Lowe's fixit for screwed-up comm ports; Run this before opening for use.
   int resultKludge = KludgeMakeLabComputerWorkDarnit(serialPort.m_wszComPort);

   // this is probably the riskiest step because the port could be wrong or unusable
   HANDLE hComm;
   hComm = ::CreateFile(serialPort.m_wszComPort,  
                        GENERIC_READ | GENERIC_WRITE, 
                        FILE_SHARE_READ | FILE_SHARE_WRITE,//0, 
                        0, 
                        OPEN_EXISTING,
                        0,
                        0);

   if (hComm == INVALID_HANDLE_VALUE)
   {
      return -1;
   }

   serialPort.m_hCommPort = hComm;


   // set the input buffersize
   int iBuffSize = 8*1024;
   bool bGoodSet = false;
   int k = 16;
   for (; k > 0 && bGoodSet == false; --k) {
	   if (::SetupComm(serialPort.m_hCommPort, 1024*k, 1024*k))
	   {
		   bGoodSet = true;
	   }
   }


#if defined(S100)
   if (!bGoodSet)
   {
	  ::CloseHandle(serialPort.m_hCommPort);
	  serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
	  return -2;
   }
#endif

   // set up the com port parameters
   DCB commState;
   if (!::GetCommState(serialPort.m_hCommPort, &commState))
   {
      ::CloseHandle(serialPort.m_hCommPort);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
      return -3;
   }

   commState.BaudRate = serialPort.m_iBaudRate;
   commState.ByteSize = serialPort.m_iDataBits;
   commState.Parity = serialPort.m_iParity;

   commState.StopBits = serialPort.m_iStopBits;

   switch (serialPort.m_iFlowControl)
   {
       case 0:
           // XON/XOFF
           commState.fOutX = TRUE;
           commState.fInX = TRUE;
           // hardware
           commState.fOutxCtsFlow = FALSE;
           commState.fOutxDsrFlow = FALSE;
           commState.fDtrControl = DTR_CONTROL_DISABLE;
           commState.fRtsControl = RTS_CONTROL_DISABLE;
           break;

       case 1:
           // XON/XOFF
           commState.fOutX = FALSE;
           commState.fInX = FALSE;
           // hardware
           commState.fOutxCtsFlow = TRUE;
           commState.fOutxDsrFlow = TRUE;
           commState.fDtrControl = DTR_CONTROL_ENABLE;
           commState.fRtsControl = RTS_CONTROL_ENABLE;
           break;

       default:
           // flow control == none

           // XON/XOFF
           commState.fOutX = FALSE;
           commState.fInX = FALSE;
           // hardware
           commState.fOutxCtsFlow = FALSE;
           commState.fOutxDsrFlow = FALSE;
           commState.fDtrControl = DTR_CONTROL_DISABLE;
           commState.fRtsControl = RTS_CONTROL_DISABLE;
           break;
   }

   if (!::SetCommState(serialPort.m_hCommPort, &commState))
   {
      ::CloseHandle(serialPort.m_hCommPort);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
      return -4;
   }

   // set up the com port timeouts
   COMMTIMEOUTS commTimeouts;
   if (!::GetCommTimeouts(serialPort.m_hCommPort, &commTimeouts))
   {
      ::CloseHandle(serialPort.m_hCommPort);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
      return -5;
   }


   if (serialPort.m_iBaudRate == 4800)
   {
      commTimeouts.ReadIntervalTimeout = 1;
      commTimeouts.ReadTotalTimeoutMultiplier = 0;
      commTimeouts.ReadTotalTimeoutConstant = 90;
   }
   else
   {
      commTimeouts.ReadIntervalTimeout = 1;
      commTimeouts.ReadTotalTimeoutMultiplier = 0;
      int timeoutConstant = (int)(INBOUND_BUF_SIZE / 11520.0 * 1000.0);
      commTimeouts.ReadTotalTimeoutConstant = timeoutConstant;
   }


   if (!::SetCommTimeouts(serialPort.m_hCommPort, &commTimeouts))
   {
      ::CloseHandle(serialPort.m_hCommPort);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
      return -6;
   }




   wchar_t m_wszFileName[MAX_PATH+1];
   wmemset(m_wszFileName, 0, _countof(m_wszFileName));

   SYSTEMTIME st;
   GetLocalTime(&st);

#if defined(S100)

   swprintf(m_wszFileName, L"\\Hard Disk\\SerialPortRecorder S100 %04d%02d%02d_%02d_%02d PORT %d.log", 
                       st.wYear, 
                       st.wMonth, 
                       st.wDay, 
                       st.wHour, 
                       st.wMinute, 
                       serialPort.m_iComPortNumber);

#else

   swprintf(m_wszFileName, L"\\USBDisk\\SerialPortRecorder S200 %04d%02d%02d_%02d_%02d PORT %d.log", 
                       st.wYear, 
                       st.wMonth, 
                       st.wDay, 
                       st.wHour, 
                       st.wMinute, 
                       serialPort.m_iComPortNumber);

#endif


   HANDLE hOutputFile;
   hOutputFile = ::CreateFile(m_wszFileName,  
                              GENERIC_WRITE, 
                              0, 
                              0, 
                              OPEN_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL, //FILE_FLAG_WRITE_THROUGH,
                              0);

   if (hOutputFile == INVALID_HANDLE_VALUE) {
      ::CloseHandle(serialPort.m_hCommPort);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
      return -7;
   }

   serialPort.m_hOutputFile = hOutputFile;

   // set the output buffersize
   ::SetupComm(serialPort.m_hOutputFile, OUTBOUND_BUF_SIZE, OUTBOUND_BUF_SIZE);


   DWORD dwBytesWritten;
   // First line of log file should indicate all port settings used so that
   // playback app can simply read this header line and set itself up.
   char strFileHeader[MAX_PATH+1];
   memset(strFileHeader, 0, sizeof(strFileHeader));

   char szComPortASCII[MAX_PATH+1];
   memset(szComPortASCII, 0, sizeof(szComPortASCII));
   char* pChar = (char*)serialPort.m_wszComPort;
   for (int idx = 0; idx < wcslen(serialPort.m_wszComPort); ++idx)
   {
      szComPortASCII[idx] = *pChar;
      pChar += 2;
   }

   int lineLength = sprintf(strFileHeader, "%s\t%s\t%d\t%d\t%d\t%d\t%d\r\n", 
                                       "SERIAL PORT",
                                       szComPortASCII, 
                                       serialPort.m_iBaudRate, 
                                       serialPort.m_iDataBits, 
                                       serialPort.m_iParity, 
                                       serialPort.m_iStopBits, 
                                       serialPort.m_iFlowControl);
   if (lineLength == -1) 
   {
      ::CloseHandle(serialPort.m_hCommPort);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;

      ::CloseHandle(serialPort.m_hOutputFile);
      serialPort.m_hOutputFile = INVALID_HANDLE_VALUE;
      return -8;
   }
   if (!::WriteFile(serialPort.m_hOutputFile, strFileHeader, lineLength, &dwBytesWritten, 0)) // || ((.5 * dwBytesWritten) != strFileHeader.GetLength())) 
   {
      ::CloseHandle(serialPort.m_hCommPort);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;

      ::CloseHandle(serialPort.m_hOutputFile);
      serialPort.m_hOutputFile = INVALID_HANDLE_VALUE;
      return -9;
   }

   return 0;
}



DWORD WINAPI ThreadProc( LPVOID lpParam ) 
{ 
    // Cast the parameter to the correct data type.
    // The pointer is known to be valid because 
    // it was checked for NULL before the thread was created.
    SPortSettings* pPort = (SPortSettings*)lpParam;

    int iResult = 0;


    DWORD nbrBytesRead;
    DWORD nbrBytesWritten;


	// *2 because we're expanding from binary bytes to
	// 2-digit hex strings/byte
	// +9 because tickcount milliseconds is expended to a total
	// of 9 digits (leading 0's if necessary)
	// + 1 because of the '\t' after the milliseoncs
	// + 2 because of the trailing '\r\n' line terminator
	// +16 because i'm tired and want to be sure.
    char strRecord[INBOUND_BUF_SIZE*2 + 9+1+2+16];

	DWORD dwNow;

    while (!pPort->m_bStopThread) 
	{
      memset(pPort->m_aucInboundBytes, 0, sizeof(pPort->m_aucInboundBytes));
      nbrBytesRead = 0;

        // get the data, if any
        if (!ReadFile(pPort->m_hCommPort, pPort->m_aucInboundBytes, sizeof(pPort->m_aucInboundBytes), &nbrBytesRead, NULL))
        {
            DWORD dwLastErr = GetLastError();
            iResult = (pPort->m_iComPortNumber + 2000);
        }

        if (nbrBytesRead == 0)
        {
            Sleep(1);
            continue;
        }

		dwNow = ::GetTickCount();

		if (dwNow < g_dwRecordStartMilliseconds)
		{
			// GetTickCount() rollover occured.
			// 0     dwNow   g_dwRecordStartMilliseconds     UINT_MAX
			// |     |       |                               |
			// +-----+-------+-------------------------------+
			dwNow = (UINT_MAX - g_dwRecordStartMilliseconds) + dwNow;
		}
		else 
		{
			// 0   g_dwRecordStartMilliseconds     dwNow     UINT_MAX
			// |   |                                |        |
			// +---+--------------------------------+--------+
			dwNow = dwNow - g_dwRecordStartMilliseconds;
		}

		pPort->m_dwTotalBytesRead += nbrBytesRead;
		
		// Start of each data line has:
		// "[Running TOTAL Milliseconds]\t"
        int lineLength = sprintf(strRecord, "%09lu\t", dwNow);

        // write the data in hex
        for (int byteIdx = 0; byteIdx < nbrBytesRead; ++byteIdx)
        {
			memcpy(&strRecord[(2 * byteIdx) + lineLength], 
				   g_aszHexStrings[pPort->m_aucInboundBytes[byteIdx]],
				   2);
        }

		lineLength += nbrBytesRead * 2;

        // EOL
		memcpy(&strRecord[lineLength], 
			   "\r\n",
			   2);

		lineLength += 2;

        if (!WriteFile(pPort->m_hOutputFile, strRecord, lineLength, &nbrBytesWritten, 0))
        {
            // error writing to file; abort, returning the port # + 2400
            DWORD dwLastErr = GetLastError();
            iResult = (pPort->m_iComPortNumber + 2400);
            break;
        }
    }  // while (!pPort->m_bStopThread) 


    // write the final EOL
    if (!WriteFile(pPort->m_hOutputFile, "\r\n", 2, &nbrBytesWritten, 0))
    {
        // error writing to file; abort, returning the port # + 2600
        DWORD dwLastErr = GetLastError();
        iResult = (pPort->m_iComPortNumber + 2600);
    }

    if (!FlushFileBuffers(pPort->m_hOutputFile))
    {
        // error writing to file; abort, returning the port # + 2700
        DWORD dwLastErr = GetLastError();
        iResult = (pPort->m_iComPortNumber + 2700);
    }
            
    CloseHandle(pPort->m_hCommPort);
    CloseHandle(pPort->m_hOutputFile);

    return iResult; 
} 







