#include "pch.h"
#include "CppUnitTest.h"
#include "../LB12.3B/main.cpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const char* testFileName = "testfile.dat"; // Ім'я тимчасового файлу
			// Створюємо файл і записуємо студента
			ofstream tempFile(testFileName, ios::binary);
			if (!tempFile)
			{
				Assert::Fail(L"Failed to create a temporary file");
			}
		}
	};
}
