//============================================================================
// Name        : SPOJ LUCIFER - LUCIFER Number
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Counting Range DP
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define N 100

#define ll long long

bool mem[10][N][N], mark[N];
ll D[10][N][N], a, b;
char cad[N], c[N];
int primes[N], p, casos, len;

void initialize()
{
    // sieve to generate all prime sums less than 80
    p = 0;
    primes[p++] = 2;
    memset(mark, 1, sizeof(mark));
    for (int i = 4; i < N; i += 2)
        mark[i] = false;

    for (int i = 3; i < N; i += 2)
        if (mark[i])
        {
            primes[p++] = i;
            for (int j = i*i; j < N; j += 2*i)
                mark[j] = false;
        }
}

// function F(k, property)
ll F(int dig, int odd, int even)
{
    if (dig == 0)
    {
        return (ll)(*lower_bound(primes, primes + p, even - odd) == even - odd);
    }

    if (mem[dig][odd][even])
        return D[dig][odd][even];

    mem[dig][odd][even] = 1;
    ll ret = 0LL;
    for (int i = 0; i <= 9; i++)
    {
        if (dig % 2 == 0)
            ret += F(dig - 1, odd, even + i);
        else
            ret += F(dig - 1, odd + i, even);
    }

    D[dig][odd][even] = ret;
    return ret;
}

ll solve(ll x)
{
    ll ret = 0;
    sprintf(cad, "%lld", x);
    len = strlen(cad);
    int remain = len;

    int sum_even = 0, sum_odd = 0;
    for (int i = 0; i < len; i++)
    {
        remain--;
        int d = cad[i] - '0';

        // for all numbers starting with digits less than x[i]
        for (int j = 0; j < d; j++)
        {
            if ((len - i) % 2)
                ret += F(remain, sum_odd + j, sum_even);
            else
                ret += F(remain, sum_odd, sum_even + j);
        }

        // updating property
        if ((len - i) % 2)
            sum_odd += d;
        else
            sum_even += d;
    }
    return ret;
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    initialize();
    scanf("%d", &casos);
    while (casos--)
    {
        scanf("%lld%lld", &a, &b);
        ll ans = solve(b + 1) - solve(a);
        printf("%lld\n", ans);
    }
    return 0;
}
