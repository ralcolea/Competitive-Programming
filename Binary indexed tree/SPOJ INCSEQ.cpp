//============================================================================
// Name        : SPOJ - INCSEQ
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAX  100005
#define MaxK 55
#define MOD  5000000

#define ll long long
#define endl '\n'

int N, K, value;
ll dp[MaxK][MAX + 5];

ll read(int index, ll fenwick[MAX + 5])
{
    ll sum = 0;
    while (index)
    {
        sum += fenwick[index];
        sum %= MOD;
        index -= (index & -index);
    }

    return sum;
}

void update(ll val, int index, ll fenwick[MAX + 5])
{
    while (index <= MAX)
    {
        fenwick[index] += val;
        fenwick[index] %= MOD;
        index += (index & -index);
    }
}

void solve()
{
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &value);
        value++;

        for (int j = 2; j <= K; j++)
            update(read(value - 1, dp[j - 1]), value, dp[j]);

        // base case
        update(1, value, dp[1]);
    }

    printf("%lld\n", read(MAX, dp[K]));
}

int main()
{
    scanf("%d%d", &N, &K);
    solve();
    return 0;
}
