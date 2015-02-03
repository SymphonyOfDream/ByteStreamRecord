#include "stdafx.h"

#include "CAN.h"

#include "PortSettings.h"



#include "CANPortProcessor.h"


#if defined(S100)


int OpenCANPort(SPortSettings& serialPort)
{
   serialPort.m_bStopThread = FALSE;
   serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
   serialPort.m_hOutputFile = INVALID_HANDLE_VALUE;

   // this is probably the riskiest step because the port could be wrong or unusable
   HANDLE hComm;
   hComm = CreateFile(serialPort.m_wszComPort,  
							GENERIC_WRITE | GENERIC_READ, 
                        FILE_SHARE_READ | FILE_SHARE_WRITE,//0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

   if (hComm == INVALID_HANDLE_VALUE)
   {
      return -1;
   }

   serialPort.m_hCommPort = hComm;


   // Reset the CAN chip
   if (!::DeviceIoControl(serialPort.m_hCommPort, IOCTL_RESET_CHIP, NULL, 0, NULL, 0, NULL, NULL)) 
   {
      ::CloseHandle(hComm);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
      return -2;
   } 

   // Set the baudrate
   if (!::DeviceIoControl(serialPort.m_hCommPort, IOCTL_CAN_SET_BAUDRATE, &(serialPort.m_iBaudRate), sizeof(ULONG), NULL, 0, NULL, NULL)) 
   {
      ::CloseHandle(hComm);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
      return -3;
   } 


   // Clear the CAN queue.  Get rid of any old messages before we start.
   if (!::DeviceIoControl(serialPort.m_hCommPort, IOCTL_CAN_CLEAR_QUEUE, NULL, 0, NULL, 0, NULL, NULL)) {
      ::CloseHandle(hComm);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
      return -4;
   } 




   wchar_t m_wszFileName[MAX_PATH+1];
   wmemset(m_wszFileName, 0, _countof(m_wszFileName));

   SYSTEMTIME st;
   GetLocalTime(&st);

   swprintf(m_wszFileName, L"\\SD\\CANPortRecorder - %04d%02d%02d_%02d_%02d PORT %d.log", 
                       st.wYear, 
                       st.wMonth, 
                       st.wDay, 
                       st.wHour, 
                       st.wMinute, 
                       serialPort.m_iComPortNumber);

   HANDLE hOutputFile;
   hOutputFile = ::CreateFile(m_wszFileName,  
                              GENERIC_WRITE, 
                              0, 
                              0, 
                              OPEN_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL, //FILE_FLAG_WRITE_THROUGH,
                              0);

   if (hOutputFile == INVALID_HANDLE_VALUE) {
      ::CloseHandle(hComm);
      serialPort.m_hCommPort = INVALID_HANDLE_VALUE;
      return -7;
   }

   serialPort.m_hOutputFile = hOutputFile;


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
                                       "CAN PORT",
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


#define CAN_MSG_ARRAY_CAPACITY  256
static CAN_MSG _aCanMessages[CAN_MSG_ARRAY_CAPACITY] = {0};

// EACH LINE:
// Tck Cnt      CAN_MSG bytes      Line Terminator
// ticks   \t   0102030405060708   \r\n

//  sizeof(CAN_MSG)  because that's what we're recording
// *2  because we convert the CAN_MSG bytes from binary
//     values to 2-digit hex strings/byte (255/0xFF == "FF")
// +9 because tickcount milliseconds is expended to a total
//    of 9 digits (leading 0's if necessary)
// + 1 because of the '\t' after the milliseconds
// + 2 because of the trailing '\r\n' line terminator
// +16 because i'm tired and want to be sure.
#define CAN_OUTPUT_LINE_SIZE (sizeof(CAN_MSG)*2 + 9+1+2+16)

static char _szSingleRecord[CAN_OUTPUT_LINE_SIZE];


DWORD WINAPI CANThreadProc( LPVOID lpParam ) 
{ 
   // Cast the parameter to the correct data type.
   // The pointer is known to be valid because 
   // it was checked for NULL before the thread was created.
   SPortSettings* pPort = (SPortSettings*)lpParam;

   int iResult = 0;


   const DWORD dwCAN_MSG_BYTE_COUNT = sizeof(CAN_MSG);

	DWORD dwNow;
   DWORD dwBytesWrittenToFile = 0;

   while (!pPort->m_bStopThread) 
	{
      DWORD dwNumMessages = 0;
      BOOL bRC 
         = ::DeviceIoControl(pPort->m_hCommPort, 
                             IOCTL_CAN_GET_NUM_MSGS, 
                             NULL, 
                             0, 
                             &dwNumMessages, 
                             sizeof(DWORD), 
                             NULL, 
                             NULL);

      if (!bRC) 
      {
         DWORD dwLastErr = GetLastError();
         iResult = (pPort->m_iComPortNumber + 2000);
         ::Sleep(100);
         continue;
      }
      else if (!dwNumMessages)
      {
         ::Sleep(1);
         continue;
      }

      const DWORD dwMessagesToRead = dwNumMessages > CAN_MSG_ARRAY_CAPACITY
                             ? CAN_MSG_ARRAY_CAPACITY
                             : dwNumMessages;

      DWORD dwReadBytesCount;
      bRC = ::ReadFile(pPort->m_hCommPort, 
                       &(_aCanMessages[0]), 
                       dwCAN_MSG_BYTE_COUNT*dwMessagesToRead, 
                       &dwReadBytesCount, 
                       NULL);

	   if (!bRC) 
      {
         DWORD dwLastErr = GetLastError();
         iResult = (pPort->m_iComPortNumber + 2000);
         ::Sleep(100);
         continue;
	   }

		pPort->m_dwTotalBytesRead += dwReadBytesCount;

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
		

      const int iReadMessageCount = int(dwReadBytesCount / dwCAN_MSG_BYTE_COUNT);
      
      for (int canMsgIdx = 0; canMsgIdx < iReadMessageCount; ++canMsgIdx)
      {
         CAN_MSG* pCanMsg = &(_aCanMessages[canMsgIdx]);

         memset(_szSingleRecord, 0, sizeof(_szSingleRecord));
         int iOutputLineLength = 0;

		   // Start of each data line has:
		   // "[Running TOTAL Milliseconds]\t"
         iOutputLineLength = sprintf(_szSingleRecord, "%09lu\t", dwNow);

         // write the data in hex (i.e., 0xFF => "FF", 0x01 => "01", etc.)
         unsigned char* pucCanMsgByte = (unsigned char*)pCanMsg;
         for (int byteIdx = 0; 
              byteIdx < sizeof(CAN_MSG); 
              ++byteIdx, iOutputLineLength += 2)
         {
            memcpy(&_szSingleRecord[iOutputLineLength], 
                   g_aszHexStrings[pucCanMsgByte[byteIdx]],
                   2);
         }

         // EOL
         memcpy(&_szSingleRecord[iOutputLineLength], 
                "\r\n",
                2);

         iOutputLineLength += 2;

         dwBytesWrittenToFile = 0;
         if (!::WriteFile(pPort->m_hOutputFile, _szSingleRecord, iOutputLineLength, &dwBytesWrittenToFile, 0))
         {
           // error writing to file; abort, returning the port # + 2400
           DWORD dwLastErr = GetLastError();
           iResult = (pPort->m_iComPortNumber + 2600);
         }
      }  // for (int canMsgIdx = 0; canMsgIdx < iReadMessageCount; ++canMsgIdx)
   }  // while (!pPort->m_bStopThread) 


   // write the final EOL
   if (!::WriteFile(pPort->m_hOutputFile, "\r\n", 2, &dwBytesWrittenToFile, 0))
   {
      // error writing to file; abort, returning the port # + 2600
      DWORD dwLastErr = GetLastError();
      iResult = (pPort->m_iComPortNumber + 2600);
   }

   if (!::FlushFileBuffers(pPort->m_hOutputFile))
   {
      // error writing to file; abort, returning the port # + 2700
      DWORD dwLastErr = GetLastError();
      iResult = (pPort->m_iComPortNumber + 2700);
   }

   ::CloseHandle(pPort->m_hCommPort);
   ::CloseHandle(pPort->m_hOutputFile);

   return iResult; 
} 







#endif
