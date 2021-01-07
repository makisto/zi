#include "pch.h"
#include "CppUnitTest.h"
#include "../LibCrypto1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZILab1DiffiHellmanUnitTest
{
	TEST_CLASS(ZILab1DiffiHellmanUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			long long expected = 21;
			long long actual = LibCrypto1::diffi_hellman_key(23, 5, 5, 7);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod2)
		{
			long long expected = 10;
			long long actual = LibCrypto1::diffi_hellman_key(19, 2, 5, 7);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod3)
		{
			long long expected = 16;
			long long actual = LibCrypto1::diffi_hellman_key(23, 7, 3, 4);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod4)
		{
			long long expected = 9;
			long long actual = LibCrypto1::diffi_hellman_key(17, 3, 10, 5);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestMethod5)
		{
			long long expected = 16;
			long long actual = LibCrypto1::diffi_hellman_key(19, 10, 4, 8);
			Assert::AreEqual(expected, actual);
		}
	};
}
