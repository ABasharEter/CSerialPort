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
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\CSerialPort\CSerialPort.h"
#include "..\CSerialPort\CSerialPort.c"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CSerialPortTest
{		
	//I've not includecd all the unit tests here becase of the lack of com port hardware.
	//Feel free to test the library yourself.

	TEST_CLASS(MainUnitTest)
	{
	public:
		
		TEST_METHOD(BasicTest)
		{
			auto p1 = OpenPort(1);
			auto p2 = OpenPort(2);
			char sendstr[80] = "ACK";
			char recivestr[80];
			Assert::IsTrue(SendData(p1, sendstr)>0);
			Assert::IsTrue(ReciveData(p2, recivestr, 80)>0);
			Assert::AreEqual(sendstr, recivestr, "Assserting Send Recive");
			ClosePort(p1);
			ClosePort(p2);
		}
		TEST_METHOD(BoudTest)
		{
			auto p1 = OpenPort(1);
			auto p2 = OpenPort(2);
			char sendstr[80] = "ACK";
			char recivestr[80];


			Assert::IsTrue(SetPortBoudRate(p1, CP_BOUD_RATE_19200));
			Assert::IsTrue(SetPortBoudRate(p2, CP_BOUD_RATE_19200));
			Assert::IsTrue(SendData(p1, sendstr)>0);
			Assert::IsTrue(ReciveData(p2, recivestr, 80)>0);
			Assert::AreEqual(sendstr, recivestr, "Assserting Send Recive");
			ZeroMemory(recivestr, sizeof recivestr);


			Assert::IsTrue(SetPortBoudRate(p1, CP_BOUD_RATE_4800));
			Assert::IsTrue(SetPortBoudRate(p2, CP_BOUD_RATE_4800));
			Assert::IsTrue(SendData(p1, sendstr)>0);
			Assert::IsTrue(ReciveData(p2, recivestr, 80)>0);
			Assert::AreEqual(sendstr, recivestr, "Assserting Send Recive");
			ZeroMemory(recivestr, sizeof recivestr);

			Assert::IsTrue(SetPortBoudRate(p1, CP_BOUD_RATE_1155));
			Assert::IsTrue(SetPortBoudRate(p2, CP_BOUD_RATE_1155));
			Assert::IsTrue(SendData(p1, sendstr)>0);
			Assert::IsTrue(ReciveData(p2, recivestr, 80)>0);
			Assert::AreEqual(sendstr, recivestr, "Assserting Send Recive");
			ZeroMemory(recivestr, sizeof recivestr);

			Assert::IsTrue(SetPortBoudRate(p1, CP_BOUD_RATE_9600));
			Assert::IsTrue(SetPortBoudRate(p2, CP_BOUD_RATE_9600));
			Assert::IsTrue(SendData(p1, sendstr)>0);
			Assert::IsTrue(ReciveData(p2, recivestr, 80)>0);
			Assert::AreEqual(sendstr, recivestr, "Assserting Send Recive");
			ZeroMemory(recivestr, sizeof recivestr);

			ClosePort(p1);
			ClosePort(p2);
		}

	};
}