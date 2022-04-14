//============================================================================
// Name        : SPOJ GONE - G-One Numbers
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Counting Range DP
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define N 100

#define ll long long

bool mem[N][N], mark[N];
ll D[N][N], a, b;
char cad[N];
int primes[N], p, casos;

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
ll F(int dig, int sum)
{
    if (dig == 0)
        return (ll)(*lower_bound(primes, primes + p, sum) == sum);

    if (mem[dig][sum])
        return D[dig][sum];

    mem[dig][sum] = 1;
    ll ret = 0;
    for (int i = 0; i <= 9; i++)
        ret += F(dig - 1, sum + i);

    D[dig][sum] = ret;
    return ret;
}

ll solve(ll x)
{
    ll ret = 0;
    sprintf(cad, "%lld", x);
    int len = strlen(cad);
    int remain = len;
    int curr_sum = 0;

    for (int i = 0; i < len; i++)
    {
        remain--;
        int d = cad[i] - '0';

        // for all numbers starting with digits less than x[i]
        for (int j = 0; j < d; j++)
        {
            ret += F(remain, curr_sum + j);
        }

        // updating property
        curr_sum += d;
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
