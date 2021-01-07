#include "pch.h"
#include "LibCrypto1.h"

using namespace std;

long long LibCrypto1::right_left_fast_pow(
    long long a,
    long long x)
{
    long long y = 1;
    long long s = a;

    for (int i = 0; i <= (int)floor(log2(x)); i++)
    {
        if (1 == ((x >> i) & 1))
        {
            y = (y * s);
        }
        s = (s * s);
    }

    return y;
}

long long LibCrypto1::left_right_fast_pow(
    long long a,
    long long x)
{
    long long y = 1;

    for (int i = (int)floor(log2(x)); i >= 0; i--)
    {
        y = (y * y);
        if (1 == ((x >> i) & 1))
        {
            y = (y * a);
        }
    }

    return y;
}

long long LibCrypto1::right_left_fast_pow_by_module(
    long long a,
    long long x,
    long long p)
{
    long long y = 1;
    long long s = a;

    for (int i = 0; i <= (int)floor(log2(x)); i++)
    {
        if (1 == ((x >> i) & 1))
        {
            y = (y * s) % p;
        }
        s = (s * s) % p;
    }

    return y;
}

long long LibCrypto1::left_right_fast_pow_by_module(
    long long a,
    long long x,
    long long p)
{
    long long y = 1;

    for (int i = (int)floor(log2(x)); i >= 0; i--)
    {
        y = (y * y) % p;
        if (1 == ((x >> i) & 1))
        {
            y = (y * a) % p;
        }
    }

    return y;
}

long long *LibCrypto1::abstract_gcd(
    long long a,
    long long b)
{
    long long q = 0;
    long long* u = new long long[3];
    long long v[3] = { b, 0, 1 };
    long long t[3];

    u[0] = a;
    u[1] = 1;
    u[2] = 0;

    while (v[0] != 0)
    {
        q = u[0] / v[0];

        t[0] = u[0] % v[0];
        t[1] = u[1] - q * v[1];
        t[2] = u[2] - q * v[2];

        for (int i = 0; i < 3; i++)
        {
            u[i] = v[i];
            v[i] = t[i];
        }
    }

    return u;
}

bool LibCrypto1::miller_rabin_prime_number_test(
    long long n,
    int k)
{
    if (n == 2 || n == 3)
    {
        return true;
    }
    if (n < 2 || (n % 2) == 0)
    {
        return false;
    }

    long long t = n - 1;
    int s = 0;

    while (t % 2 == 0)
    {
        t /= 2;
        s += 1;
    }

    for (int i = 0; i < k; i++)
    {
        long long a = 0;
        do
        {
            a = rand() % (n - 2);
        } while (a < 2 || a > n - 2);

        long long x = left_right_fast_pow_by_module(a, t, n);
        if (x == 1 || x == n - 1)
        {
            continue;
        }

        for (int r = 1; r < s; r++)
        {
            x = right_left_fast_pow_by_module(x, 2, n);
            if (x == 1)
            {
                return false;
            }

            if (x == n - 1)
            {
                break;
            }
        }

        if (x != n - 1)
        {
            return false;
        }
    }

    return true;
}

void LibCrypto1::prime_number_count(
    long long *const p,
    long long *const q,
    long long *const g,
    int k)
{
    /*random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned long long> dis(0, 1000000000);*/
    for (;;)
    {
        //*q = dis(gen);
        //*q = rand() % RAND_MAX;
        //*q = (rand() * rand() + rand()) % 1000000000;
        *q = rand() % RAND_MAX;
        if (miller_rabin_prime_number_test(*q, k))
        {
            *p = 2 * (*q) + 1;
            if (miller_rabin_prime_number_test(*p, k))
            {
                break;
            }
        }
        /*p = rand() % RAND_MAX;
        *q = rand() % RAND_MAX;
        if (*p == (2 * (*q) + 1) && ((*p - 1) == 2 * (*q)))
        {
            cout << "P = 2Q + 1:" << *p << " " << *q << endl;
            if (miller_rabin_prime_number_test(*p, k)
                && miller_rabin_prime_number_test(*q, k))
            {
                cout << "PRIME:" << *p << " " << *q << endl;
                break;
            }
            else
            {
                cout << "NOT PRIME:" << *p << " " << *q << endl;
            }
        }*/
    }

    //uniform_int_distribution<unsigned long long> g_dis(0, *p - 1);

    do
    {
        *g = rand() % (*p - 2) + 2;
        //*g = g_dis(gen);
    } while (left_right_fast_pow_by_module(*g, *q, *p) != 1);
}

long long LibCrypto1::diffi_hellman_key(
    long long p,
    long long g,
    long long xA,
    long long xB)
{
    long long y[2];
    long long z[2];

    y[0] = left_right_fast_pow_by_module(g, xA, p);
    y[1] = right_left_fast_pow_by_module(g, xB, p);

    cout << "Yi:" << y[0] << " " << y[1] << endl;

    z[0] = left_right_fast_pow_by_module(y[1], xA, p);
    z[1] = right_left_fast_pow_by_module(y[0], xB, p);

    cout << "Zi:" << z[0] << " " << z[1] << endl << endl;

    if (z[0] == z[1])
    {
        return z[0];
    }
    else
    {
        cout << "BAD KEY COUNT!!!" << endl;
        return -1;
    }
}

long long LibCrypto1::baby_step_giant_step(
    long long a,
    long long y,
    long long p)
{
    long long i;
    long long x = 0;
    unsigned long long k = 0;
    unsigned long long m = 0;

    m = (long long)sqrt(p) + 1;
    k = (long long)sqrt(p) + 1;
    cout << "M:" << m << endl << "K:" << k << endl << "P:" << p << endl;

    long long* a1 = new long long[m];
    long long* b = new long long[k];

    a1[0] = y % p;
    for (i = 1; i < m; i++)
    {
        a1[i] = a1[0] * right_left_fast_pow_by_module(a, i, p);
        //cout << a1[i] << " ";
    }
   //cout << endl;

    for (i = 0; i < k; i++)
    {
        b[i] = right_left_fast_pow_by_module(a, m * (i + 1), p);
        //cout << b[i] << " ";
    }
    //cout << endl;

    map<int, int> dict;
    for (i = 0; i < m; ++i)
    {
        dict[a1[i]] = i;
    }
    for (i = 0; i < k; ++i)
    {
        if (dict.count(b[i]))
        {
            cout << i + 1 << " " << dict[b[i]] << endl;
            x = (m * (i + 1) - (dict[b[i]]));
            break;
        }
    }

    return x;
}
