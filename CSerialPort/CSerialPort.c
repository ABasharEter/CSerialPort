/*
Copyright (c) 2017 Ahmad Bashar Eter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "CSerialPort.h"

PORT OpenPort(int idx)
{
	HANDLE hComm;
	TCHAR comname[100];
	wsprintf(comname, TEXT("\\\\.\\COM%d"), idx);
	hComm = CreateFile(comname,            //port name 
		GENERIC_READ | GENERIC_WRITE, //Read/Write   				 
		0,            // No Sharing                               
		NULL,         // No Security                              
		OPEN_EXISTING,// Open existing port only                     
		0,            // Non Overlapped I/O                           
		NULL);        // Null for Comm Devices
	
	if (hComm == INVALID_HANDLE_VALUE)
		return NULL;
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (SetCommTimeouts(hComm, &timeouts) == FALSE)
		return NULL;

	if (SetCommMask(hComm, EV_RXCHAR) == FALSE)
		return NULL;

	return hComm;
}
void ClosePort(PORT com_port)
{
	CloseHandle(com_port);
}

int SetPortBoudRate(PORT com_port, int rate)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return FALSE;
	dcbSerialParams.BaudRate = rate;
	Status = SetCommState(com_port, &dcbSerialParams);
	return Status;
}

int SetPortDataBits(PORT com_port, int bits)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return FALSE;
	dcbSerialParams.ByteSize = bits;
	Status = SetCommState(com_port, &dcbSerialParams);
	return Status;
}

int SetPortStopBits(PORT com_port, int bits)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return FALSE;
	dcbSerialParams.StopBits = bits;
	Status = SetCommState(com_port, &dcbSerialParams);
	return Status;
}

int SetPortParity(PORT com_port, int parity)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return FALSE;
	dcbSerialParams.Parity = parity;
	Status = SetCommState(com_port, &dcbSerialParams);
	return Status;
}

int GetPortBoudRate(PORT com_port)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return -1;
	return dcbSerialParams.BaudRate;
}
int GetPortDataBits(PORT com_port) {
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return -1;
	return dcbSerialParams.ByteSize;
}
int GetPortStopBits(PORT com_port) {
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return -1;
	return dcbSerialParams.StopBits;
}
int GetPortParity(PORT com_port) {
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return -1;
	return dcbSerialParams.Parity;
}

int SendData(PORT com_port, const char * data)
{
	DWORD  dNoOFBytestoWrite = strlen(data);
	DWORD  dNoOfBytesWritten;
	BOOL Status = WriteFile(com_port,
				data,
				dNoOFBytestoWrite,
				&dNoOfBytesWritten,
				NULL);
	if (Status == FALSE)
		return -1;
	return dNoOfBytesWritten;
}

int ReciveData(PORT com_port, char * data,int len)
{
	DWORD dwEventMask;
	DWORD NoBytesRead;
	BOOL Status = WaitCommEvent(com_port, &dwEventMask, NULL);
	if (Status == FALSE) {
		return FALSE;
	}
	Status = ReadFile(com_port, data, len, &NoBytesRead, NULL);
	data[NoBytesRead] = 0;
	if (Status == FALSE) {
		return FALSE;
	}
	return TRUE;
}