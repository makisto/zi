#pragma once
#include <map>
#include <ctime>
#include <cmath>
#include <string>
#include <random>
#include <fstream>
#include <iostream>

class LibCrypto1
{
	public:
		static long long right_left_fast_pow(long long a, long long x);
		static long long right_left_fast_pow_by_module(long long a, long long x, long long p);
		static long long left_right_fast_pow(long long a, long long x);
		static long long left_right_fast_pow_by_module(long long a, long long x, long long p);
		static long long *abstract_gcd(long long a, long long b);
		static bool miller_rabin_prime_number_test(long long n, int k);
		static void prime_number_count(long long *const p, long long *const q, long long *const g, int k);
		static long long diffi_hellman_key(long long p, long long g, long long xA, long long xB);
		static long long baby_step_giant_step(long long a, long long y, long long p);
};

