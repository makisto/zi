#include "LibCrypto1.h"

class LibCyphro : public LibCrypto1
{
public:
	void shamir_decode_and_uncode(long long p, long long cA, long long cB, long long dA, long long dB);
	//void shamir_unencrypt(long long p, long long cB, long long dA, long long dB);
	void el_gamal_decode(long long p, long long g, long long dB);
	void el_gamal_uncode(long long cB, long long p);
	void rsa_decode(long long d, long long n);
	void rsa_uncode(long long c, long long n);
	void vernam_decode();
	void vernam_uncode();
};
