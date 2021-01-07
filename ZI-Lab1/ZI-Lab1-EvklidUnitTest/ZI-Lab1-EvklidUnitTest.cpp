#include "pch.h"
#include "CppUnitTest.h"
#include "../LibCrypto1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZILab1EvklidUnitTest
{
	TEST_CLASS(ZILab1EvklidUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			long long *expected = new long long[3];
			long long *actual = new long long[3];
			expected[0] = 3;
			expected[1] = -1;
			expected[2] = 2;
			actual = LibCrypto1::abstract_gcd(21, 12);
			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expected[i], actual[i]);
			}
		}
		TEST_METHOD(TestMethod2)
		{
			long long* expected = new long long[3];
			long long* actual = new long long[3];
			expected[0] = 6;
			expected[1] = 1;
			expected[2] = -2;
			actual = LibCrypto1::abstract_gcd(30, 12);
			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expected[i], actual[i]);
			}
		}
		TEST_METHOD(TestMethod3)
		{
			long long* expected = new long long[3];
			long long* actual = new long long[3];
			expected[0] = 8;
			expected[1] = 2;
			expected[2] = -1;
			actual = LibCrypto1::abstract_gcd(24, 40);
			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expected[i], actual[i]);
			}
		}
		TEST_METHOD(TestMethod4)
		{
			long long* expected = new long long[3];
			long long* actual = new long long[3];
			expected[0] = 1;
			expected[1] = 1;
			expected[2] = -2;
			actual = LibCrypto1::abstract_gcd(33, 16);
			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expected[i], actual[i]);
			}
		}
	};
}
