//============================================================================
// Name        : SPOJ SQFREE - Square-free integers
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Inclusion and Exclusion Principle
//============================================================================

#include <bits/stdc++.h>
using namespace std;
#define MAX 32005

#define MAXP 300000

#define ll long long

int casos, primes, factors;
bool mark[MAX];
ll N, A, B, p[MAXP], fact[MAXP];

void sieve()
{
    memset(mark, 1, sizeof(mark));
    p[0] = 2;
    primes = 1;

    mark[2] = true;
    for (ll i = 4; i < MAX; i += 2)
        mark[i] = false;

    for (ll i = 3; i < MAX; i += 2)
    {
        if (mark[i])
        {
            p[primes++] = i;
            for (ll j = i * i; j < MAX; j += 2*i)
                mark[j] = false;
        }
    }
}

void factorize(ll P)
{
    factors = 0;
    for (int i = 0; p[i] * p[i] <= P; i++)
    {
        if (P % p[i] == 0)
        {
            fact[factors++] = p[i];
            while (P % p[i] == 0)
                P /= p[i];
        }
    }

    if (P > 1)
        fact[factors++] = P;
}

ll compute(ll R)
{
    ll total = 0;
    for (int mask = 1; mask < (1 << factors); mask++)
    {
        ll curr = 1;
        int bits = 0;
        for (int i = 0; i < factors; i++)
        {
            if (mask & (1 << i))
            {
                bits++;
                curr *= fact[i];
            }
        }

        if (bits % 2 == 1)
            total += R / curr;
        else
            total -= R / curr;
    }
    return R - total;
}

int main()
{
    sieve();
    scanf("%d", &casos);
    while (casos--)
    {
        scanf("%lld", &N);
        factorize(N);
        printf("%lld\n", compute(N));
    }
    return 0;
}
