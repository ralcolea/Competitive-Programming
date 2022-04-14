//============================================================================
// Name        : COJ 1151 - Coprimes II
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Inclusion and Exclusion Principle
//============================================================================

#include <bits/stdc++.h>
using namespace std;
#define MAXSQR 32005

#define ll long long

int casos, p[MAXSQR], primes, fact[MAXSQR], factors;
bool mark[MAXSQR];
ll N, A, B;

void sieve()
{
    memset(mark, 1, sizeof(mark));
    p[0] = 2;
    primes = 1;

    mark[2] = true;
    for (int i = 4; i < MAXSQR; i += 2)
        mark[i] = false;

    for (int i = 3; i < MAXSQR; i += 2)
    {
        if (mark[i])
        {
            p[primes++] = i;
            for (int j = i * i; j < MAXSQR; j += 2*i)
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

ll compute(int R)
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
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    sieve();
    scanf("%d", &casos);
    while (casos--)
    {
        scanf("%lld%lld%lld", &N, &A, &B);
        factorize(N);
        printf("%lld\n", compute(B) - compute(A-1));
    }
    return 0;
}
