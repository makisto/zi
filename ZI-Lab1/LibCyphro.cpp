#include "LibCyphro.h"

using namespace std;

void LibCyphro::shamir_decode_and_uncode(
	long long p, 
	long long cA,
	long long cB,
	long long dA,
	long long dB)
{
	char m;
	char m1;
	long long x1, x2, x3, x4;

	ifstream fin("input.txt");
	ofstream out("output_shamir.txt");
	ofstream out1("x1_code", ios::binary);
	ofstream out2("x2_code", ios::binary);
	ofstream out3("x3_code", ios::binary);

	if (fin.good() && out.good() && out1.good() && out2.good() && out3.good())
	{
		while (fin.get(m))
		{
			x1 = left_right_fast_pow_by_module(m, cA, p);
			out1 << x1 << " ";
			x2 = left_right_fast_pow_by_module(x1, cB, p);
			out2 << x2 << " ";
			x3 = left_right_fast_pow_by_module(x2, dA, p);
			out3 << x3 << " ";
			x4 = left_right_fast_pow_by_module(x3, dB, p);
			m1 = static_cast<char>(x4);
			out << m1;
		}
	}

	fin.close();
	out.close();
	out1.close();
	out2.close();
	out3.close();

	if (remove("x1_code"))
	{
		printf("Error removing file");
	}
	if (remove("x2_code"))
	{
		printf("Error removing file");
	}
	if (remove("x3_code"))
	{
		printf("Error removing file");
	}
}
/*void LibCyphro::shamir_unencrypt(
	long long p,
	long long cB,
	long long dA,
	long long dB)
{
	char m1;
	long long x1, x2, x3, x4;

	ifstream fin("incode_shamir", ios::binary);
	ofstream out("output_shamir.txt", ios::binary);

	if (fin.good() && out.good())
	{
		while (fin >> x1)
		{
			x2 = left_right_fast_pow_by_module(x1, cB, p);
			x3 = left_right_fast_pow_by_module(x2, dA, p);
			x4 = left_right_fast_pow_by_module(x3, dB, p);
			m1 = static_cast<char>(x4);
			out << m1;
		}
	}

	fin.close();
	out.close();
}*/
void LibCyphro::el_gamal_decode(
	long long p, 
	long long g, 
	long long dB)
{
	srand(time(NULL));

	char m;
	long long k, r, e; 

	ifstream fin("input.txt");
	ofstream out1("el_gamal_r", ios::binary);
	ofstream out2("el_gamal_e", ios::binary);

	if (fin.good() && out1.good() && out2.good())
	{
		while (fin.get(m))
		{
			k = rand() % (p - 2) + 1;
			r = left_right_fast_pow_by_module(g, k, p);
			out1 << r << " ";
			e = (m % p * left_right_fast_pow_by_module(dB, k, p)) % p;
			out2 << e << " ";
		}

		fin.close();
	    out1.close();
		out2.close();
	}
}
void LibCyphro::el_gamal_uncode(
	long long cB,
	long long p)
{
	char m;
	long long e, r, m1;

	ifstream fin1("el_gamal_e", ios::binary);
	ifstream fin2("el_gamal_r", ios::binary);
	ofstream out("output_el_gamal.txt");

	if (fin1.good() && fin2.good() && out.good()) 
	{
		while (fin1 >> e && fin2 >> r)
		{
			m1 = (e % p * left_right_fast_pow_by_module(r, p - 1 - cB, p)) % p;
			m = static_cast<char>(m1);
			out << m;
		}
	}

	fin1.close(); 
	fin2.close(); 
	out.close();

	if (remove("el_gamal_e"))
	{
		printf("Error removing file");
	}
	if (remove("el_gamal_r"))
	{
		printf("Error removing file");
	}
}
void LibCyphro::rsa_decode(
	long long d,
	long long n)
{
	ifstream fin("input.txt");
	ofstream out("incode_rsa", ios::binary);

	char m;
	long long e;

	if (fin.good() && out.good())
	{
		while (fin.get(m))
		{
			e = left_right_fast_pow_by_module(m, d, n);
			out << e << " ";
		}
	}

	fin.close();
	out.close();
}
void LibCyphro::rsa_uncode(
	long long c,
	long long n)
{
	ifstream fin("incode_rsa", ios::binary);
	ofstream out("output_rsa.txt");

	char m;
	long long m1, e;

	if (fin.good() && out.good())
	{
		while (fin >> e)
		{
			m1 = left_right_fast_pow_by_module(e, c, n);
			m = static_cast<char>(m1);
			out << m;
		}
	}

	fin.close();
	out.close();

	if (remove("incode_rsa"))
	{
		printf("Error removing file");
	}
}
void LibCyphro::vernam_decode()
{
	srand(time(NULL));

	char e; 
	char k;
	char m;

	ifstream fin("input.txt");
	ofstream out1("incode_e", ios::binary);
	ofstream out2("incode_k", ios::binary);

	if (fin.good() && out1.good() && out2.good()) 
	{
		while(fin.get(m))
		{
			k = rand() % 256;
			e = m ^ k;
			out1 << e;
			out2 << k;
		}

		fin.close();
		out1.close();
		out2.close();
	}
}
void LibCyphro::vernam_uncode()
{	
	char k;
	char e;
	char m1;

	ifstream fin1("incode_e", ios::binary);
	ifstream fin2("incode_k", ios::binary);
	ofstream out("output_vernam.txt");

	if (fin1.good() && fin2.good() && out.good()) 
	{
		while ((fin1.get(e)) && (fin2.get(k)))
		{
			m1 = e ^ k;
			out << m1;
		}
	}
	
	fin1.close(); 
	fin2.close(); 
	out.close();

	if (remove("incode_e"))
	{
		printf("Error removing file");
	}
	if (remove("incode_k"))
	{
		printf("Error removing file");
	}
}
