#include <string>
#include <fstream>
#include "LibSignes.h"
#include "../ZI-Lab1/md5.h"

using namespace std;

void LibSignes::rsa_sign(
    char filename[], 
    long long c, 
    long long d,
    long long n)
{
    ofstream out("incode_rsa", ios::binary);
    
    long long s;
    string h = "";

    if (out.good())
    {
        h = md5(filename);
        out << n << endl << d << endl;
        for (int i = 0; i < 32; i++)
        {
            s = left_right_fast_pow_by_module(h[i], c, n);
            out << s << " ";
        }
    }
    out.close();
}

void LibSignes::rsa_verify(
    char filename[])
{
    ifstream fin("incode_rsa", ios::binary);

    long long s;
    long long n;
    long long d;
    long long w;

    string h = "";

    if (fin.good())
    {
        fin >> n >> d;

        h = md5(filename);
        for (int i = 0; i < 32; i++)
        {
            fin >> s;
            w = left_right_fast_pow_by_module(s, d, n);
            if (w == h[i])
            {
                continue;
            }
            else
            {
                cout << "NON CONFIRMED" << endl;
                break;
            }
        }
        cout << "CONFIRMED" << endl;
    }
    fin.close();
}

void LibSignes::el_gamal_sign(
    char filename[],
    long long p,
    long long g,
    long long x)
{
    ofstream out("incode_el_gamal", ios::binary);

    string h = "";
    long long k = 0;
    long long r = 0;
    long long s = 0;
    long long u = 0;
    long long k1 = 0;
    long long* v = new long long[3];

    if (out.good())
    {
        h = md5(filename);
        for (int i = 0; i < 32; i++)
        {
            h[i] %= p;
            for (;;)
            {
                k = rand() % (p - 2) + 1;
                v = abstract_gcd(k, p - 1);
                if (1 == v[0])
                {
                    r = left_right_fast_pow_by_module(g, k, p);
                    u = left_right_fast_pow_by_module((h[i] - x * r), 1, (p - 1));
                    if (u < 0)
                    {
                        u += (p - 1);
                    }
                    k1 = v[1];
                    if (k1 < 0)
                    {
                        k1 += (p - 1);
                    }
                    s = left_right_fast_pow_by_module((k1 * u), 1, (p - 1));
                    out << r << " " << s << endl;
                    break;
                }
            }
        }
    }
    out.close();
}

void LibSignes::el_gamal_verify(
    char filename[],
    long long p,
    long long g,
    long long y)
{
    long long r;
    long long s;

    ifstream fin("incode_el_gamal", ios::binary);

    string h = "";

    if (fin.good())
    {
        h = md5(filename);
        for (int i = 0; i < 32; i++)
        {
            h[i] %= p;
            fin >> r >> s;
            if (((left_right_fast_pow_by_module(y, r, p) * left_right_fast_pow_by_module(r, s, p)) % p)
                == (left_right_fast_pow_by_module(g, h[i], p)))
            {
                continue;
            }
            else
            {
                cout << "NON CONFIRMED" << endl;
                break;
            }
        }
        cout << "CONFIRMED" << endl;
    }
    fin.close();
}

void LibSignes::gost_sign(
    char filename[],
    long long p,
    long long q,
    long long a,
    long long x)
{
    ofstream out("incode_gost", ios::binary);

    string h = "";
    long long k = 0;
    long long r = 0;
    long long s = 0;

    if (out.good())
    {
        h = md5(filename);
        for (int i = 0; i < 32; i++)
        {
            h[i] %= q;
            while (r == 0 && s == 0)
            {
                k = rand() % (q - 1);
                r = left_right_fast_pow_by_module(a, k, p) % q;
                s = left_right_fast_pow_by_module((k * h[i] + x * r), 1, q);
            }
            out << r << " " << s << endl;
            r = s = 0;
        }
    }
    out.close();
}

void LibSignes::gost_verify(
    char filename[],
    long long p,
    long long q,
    long long a,
    long long y)
{
    string h = "";

    long long r;
    long long s;

    long long h1 = 0;
    long long u1 = 0;
    long long u2 = 0;
    long long v = 0;

    long long* u = new long long[3];

    ifstream fin("incode_gost", ios::binary);

    if (fin.good())
    {
        h = md5(filename);
        for (int i = 0; i < 32; i++)
        {
            h[i] %= q;
            if (h[i] == 0)
            {
                h[i]++;
            }
            fin >> r >> s;

            if ((r < q) && (s < q) && (r > 0) && (s > 0))
            {
                u = abstract_gcd(h[i], q);
                if (1 == u[0])
                {
                    h1 = u[1];
                    if (h1 < 0)
                    {
                        h1 += q;
                    }
                }
                u1 = left_right_fast_pow_by_module(s * h1, 1, q);
                u2 = left_right_fast_pow_by_module(-r * h1, 1, q);
                v = ((left_right_fast_pow_by_module(a, u1, p) * left_right_fast_pow_by_module(y, u2, p)) % p) % q;

                if (v == r)
                {
                    continue;
                }
            }
            else
            {
                cout << "NON CONFIRMED" << endl;
                break;
            }
        }
        cout << "CONFIRMED" << endl;
    }
    fin.close();
}