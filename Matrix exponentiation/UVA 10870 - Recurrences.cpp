//============================================================================
// Name        : UVA 10870 - Recurrences
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Recurrence Relation and Matrix Exponentiation
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define MAXD 20

#define ll long long

ll N, M, c[MAXD], a[MAXD];
int size;

void multiply(ll F[MAXD][MAXD], ll M[MAXD][MAXD], ll MOD)
{
    ll C[MAXD][MAXD];

    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
        {
            C[i][j] = 0;
            for (int k = 1; k <= size; k++)
            {
                C[i][j] += F[i][k] * M[k][j];
                C[i][j] %= MOD;
            }
        }

    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            F[i][j] = C[i][j];
}

void initialize(ll F[MAXD][MAXD])
{
    for (int i = 0; i <= size; i++)
        for (int j = 0; j <= size; j++)
            F[i][j] = 0;

    for (int i = 1; i <= size; i++)
        F[1][i] = a[i];

    for (int i = 2; i <= size; i++)
        F[i][i-1] = 1;
}

void power(ll F[MAXD][MAXD], ll n, ll MOD)
{
    if (n == 0 || n == 1)
        return;

    ll M[MAXD][MAXD];
    initialize(M);

    power(F, n / 2, MOD);
    multiply(F, F, MOD);

    if (n % 2)
        multiply(F, M, MOD);
}

ll solve(ll N, ll MOD)
{
    if (N <= size)
        return c[size - N + 1] % MOD;

    ll F[MAXD][MAXD];

    initialize(F);

    power(F, N-size, MOD);
    ll total = 0;
    for (int i = 1; i <= size; i++)
        total += F[1][i] * c[i];

    return total % MOD;
}

int main()
{
    scanf("%d%lld%lld", &size, &N, &M);
    while (size + N + M)
    {
        for (int i = 1; i <= size; i++)
            scanf("%lld", &a[i]);

        for (int i = size; i >= 1; i--)
            scanf("%lld", &c[i]);

        printf("%lld\n", solve(N, M));
        scanf("%d%lld%lld", &size, &N, &M);
    }
    return 0;
}
