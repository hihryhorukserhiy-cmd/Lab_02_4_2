#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_2_4_2/Dictionary.h"
#include "../lab_2_4_2/Dictionary.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Dictionary d("TestDict", 10);
			Assert::IsTrue(d.addCard("hello", "привіт"));
			Assert::IsTrue(d.addCard("world", "світ"));
			Assert::IsFalse(d.addCard("hello", "алло"));
			Assert::AreEqual(2, d.getCount());
		}
	};
}
