#include "CSerialPort.h"

void main()
{
	auto p1 = OpenPort(1);
	auto p2 = OpenPort(1);
	char sendstr[80] = "ACK";
	char recivestr[80];
	(SendData(p1, sendstr)>0);
	(ReciveData(p2, recivestr, 80)>0);

	ClosePort(p1);
	ClosePort(p2);

}