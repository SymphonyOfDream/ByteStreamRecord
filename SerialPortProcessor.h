#pragma once


int OpenSerialPort(SPortSettings& serialPort);

DWORD WINAPI ThreadProc( LPVOID lpParam );
