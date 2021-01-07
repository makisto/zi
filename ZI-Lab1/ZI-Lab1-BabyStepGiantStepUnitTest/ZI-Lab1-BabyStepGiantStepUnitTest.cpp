#include "pch.h"
#include "CppUnitTest.h"
#include "../LibCrypto1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZILab1BabyStepGiantStepUnitTest
{
	TEST_CLASS(ZILab1BabyStepGiantStepUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			long long expected = 17;
			long long actual = LibCrypto1::baby_step_giant_step(2, 21, 29);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod2)
		{
			long long expected = 10;
			long long actual = LibCrypto1::baby_step_giant_step(3, 25, 31);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod3)
		{
			long long expected = 28;
			long long actual = LibCrypto1::baby_step_giant_step(2, 12, 37);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod4)
		{
			srand(time(NULL));
			long long expected = 14;
			long long actual = LibCrypto1::baby_step_giant_step(6, 21, 41);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod5)
		{
			long long expected = 30;
			long long actual = LibCrypto1::baby_step_giant_step(3, 11, 43);
			Assert::AreEqual(expected, actual);
		}
	};
}
