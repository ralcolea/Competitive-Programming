//============================================================================
// Name        : SPOJ - UPDATEIT
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAX 10005

#define ll long long

int casos, N, U, x, y, val, queries;
long long fenwick[MAX];

ll read(int index, ll tree[MAX])
{
    ll sum = 0;
    while (index)
    {
        sum += tree[index];
        index -= (index & -index);
    }

    return sum;
}

void update(ll value, int index, ll tree[MAX])
{
    while (index <= N)
    {
        tree[index] += value;
        index += (index & -index);
    }
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d", &casos);
    while (casos--)
    {
        scanf("%d%d", &N, &U);

        // initializing fenwick for next test case
        for (int i = 1; i <= N; i++)
            fenwick[i] = 0;

        for (int i = 1; i <= U; i++)
        {
            scanf("%d%d%d", &x, &y, &val);

            // range updates
            update(+val, x + 1, fenwick);
            update(-val, y + 2, fenwick);
        }

        scanf("%d", &queries);
        while (queries--)
        {
            scanf("%d", &x);
            printf("%lld\n", read(x + 1, fenwick));
        }
    }

    return 0;
}
