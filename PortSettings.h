#pragma once


struct SPortSettings
{
public:
   int m_iComPortNumber;
   int m_iBaudRate;
   int m_iDataBits;
   int m_iParity;
   int m_iStopBits;
   int m_iFlowControl;
   HANDLE m_hCommPort;
   HANDLE m_hOutputFile;
   BOOL m_bStopThread;

   BOOL m_bIsCANPort;

   DWORD m_dwTotalBytesRead;

   wchar_t m_wszComPort[MAX_PATH+1];

   unsigned char m_aucInboundBytes[INBOUND_BUF_SIZE];

};

