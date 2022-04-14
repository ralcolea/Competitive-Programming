//============================================================================
// Name        : UVA 10229 - Modular Fibonacci
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Recurrence Relation and Matrix Exponentiation
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll N, M;

void multiply(ll F[2][2], ll M[2][2], ll MOD)
{
    ll x = ((F[0][0] * M[0][0]) % MOD + (F[0][1] * M[1][0]) % MOD) % MOD;
    ll y = ((F[0][0] * M[0][1]) % MOD + (F[0][1] * M[1][1]) % MOD) % MOD;
    ll z = ((F[1][0] * M[0][0]) % MOD + (F[1][1] * M[1][0]) % MOD) % MOD;
    ll w = ((F[1][0] * M[0][1]) % MOD + (F[1][1] * M[1][1]) % MOD) % MOD;

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(ll F[2][2], ll n, ll MOD)
{
    if (n == 0 || n == 1)
        return;

    ll M[2][2] = {{1,1},{1,0}};

    power(F, n / 2, MOD);
    multiply(F, F, MOD);

    if (n % 2)
        multiply(F, M, MOD);
}

ll fib(ll N, ll MOD)
{
    ll F[2][2] = {{1,1},{1,0}};

    if (N == 0)
        return 0;

    power(F, N-1, MOD);
    return F[0][0];
}

int main()
{
    while (scanf("%lld%lld", &N, &M) != EOF)
        printf("%lld\n", fib(N, 1 << M));
    return 0;
}
