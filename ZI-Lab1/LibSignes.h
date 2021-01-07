#pragma once
#include "LibCyphro.h"
class LibSignes : public LibCyphro
{
public:
	void rsa_sign(char filename[], long long c, long long d, long long n);
	void rsa_verify(char filename[]);
	void el_gamal_sign(char filename[], long long p, long long g, long long x);
	void el_gamal_verify(char filename[], long long p, long long g, long long y);
	void gost_sign(char filename[], long long p, long long q, long long a, long long x);
	void gost_verify(char filename[], long long p, long long q, long long a, long long y);
};

