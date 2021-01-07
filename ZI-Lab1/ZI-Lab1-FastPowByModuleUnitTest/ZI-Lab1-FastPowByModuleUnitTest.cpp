#include "pch.h"
#include "CppUnitTest.h"
#include "../LibCrypto1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZILab1FastPowByModuleUnitTest
{
	TEST_CLASS(ZILab1FastPowByModuleUnitTest)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			long long expected = 6;
			long long actual = LibCrypto1::left_right_fast_pow_by_module(2, 8, 10);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod2)
		{
			long long expected = 7;
			long long actual = LibCrypto1::left_right_fast_pow_by_module(3, 7, 10);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod3)
		{
			long long expected = 43;
			long long actual = LibCrypto1::left_right_fast_pow_by_module(7, 19, 100);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod4)
		{
			long long expected = 7;
			long long actual = LibCrypto1::left_right_fast_pow_by_module(7, 57, 100);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod5)
		{
			long long expected = 6;
			long long actual = LibCrypto1::right_left_fast_pow_by_module(2, 8, 10);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod6)
		{
			long long expected = 7;
			long long actual = LibCrypto1::right_left_fast_pow_by_module(3, 7, 10);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod7)
		{
			long long expected = 43;
			long long actual = LibCrypto1::right_left_fast_pow_by_module(7, 19, 100);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod8)
		{
			long long expected = 7;
			long long actual = LibCrypto1::right_left_fast_pow_by_module(7, 57, 100);
			Assert::AreEqual(expected, actual);
		}
	};
}
