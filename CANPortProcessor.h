#pragma once

#if defined(S100)

int OpenCANPort(SPortSettings& serialPort);

DWORD WINAPI CANThreadProc( LPVOID lpParam );

#endif
