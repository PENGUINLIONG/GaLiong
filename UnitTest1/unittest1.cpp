#include "stdafx.h"
#include "CppUnitTest.h"

#include <iostream>
using namespace std;

#include "..\GaLiong\Include\Entrance.h"
#pragma comment(lib, "GaLiong.lib")
using namespace LiongStudio::GaLiong;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(DoNothing)
		{
			return;
		}

		static void ElapseHandler(Timer &sender, void *userdata)
		{
			(*(reinterpret_cast<int *>(userdata)))++;
			Logger::WriteMessage(L"Timer elapsed!\n");
		}

		TEST_METHOD(TimerElapse)
		{
			int i = 0;
			Timer timer = Timer(&i, 50);
			timer += ElapseHandler;
			timer.Start();
			Logger::WriteMessage("Timer began!\n");
			Sleep(200);
			timer.Stop();
			Logger::WriteMessage("Timer ended!\n");
			//Sleep(100);
			timer.Start();
			Logger::WriteMessage("Timer began!\n");
			Sleep(200);
			timer.Stop();
			Logger::WriteMessage("Timer ended!\n");
		}

		TEST_METHOD(PNGIDRecognition)
		{
			ifstream stream;
			Assert::AreEqual(true, ImageFormat::Assert(stream, L"F:\\assets\\test3.png", ImageFileFormat::PNG));
		}
	};
}