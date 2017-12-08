#    CSerialPort Project Overview
This is a small and easy to use C library for serial port communication targeted for windows platform.
It is a user-friendly wrapper for the Windows API serial port communication functions.
It handles opening and closing of ports and data transition as well as some port's configurations.
See the CSerialPort.h file for more details.

## Requirements
This project works only on windows platform and require Windows API to be compiled.
The project is made to work with C language projects but you can use it in C++ projects as well.

## Installing
The installation process is very simple. Just include the CSerialPort.h file in your 
hedders files and the CSerialPort.c in your source files then start calling the library functions.
To do this copy the CSerialPort.h and CSerialPort.c files to your project folder, then add them to 
the project in Visual Studio then include CSerialPort.h file.

## Simple Example
This walk throw will help you create a simple project.
You can also see the unit test project CSerialPortTest for real coded test.

1. Connect the serial port number 1 to the serial port number 2 in your machine.
2. Open visual studio and create a win32 c\c++ console project.
3. Downloading and installing this library in your project.
4. In your main source file write the following code:
```
	#include <iostream>
	#include "CSerialPort.h"

	using namespace std;
	int main(){
		auto p1 = OpenPort(1);
		auto p2 = OpenPort(2);
		char sendstr[80] = "Hello CSerialPort";
		char recivestr[80];
		SendData(p1, sendstr);
		ReciveData(p2, recivestr, 80);
		cout<<recivestr<<endl;
		ClosePort(p1);
		ClosePort(p2);
		return 0;
	}
```
5. compile and run this file.

# License
This project is done by Ahmad Bashar Eter and provided under MIT License.
Feel free to modify this code but mention my name in its source files.

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





