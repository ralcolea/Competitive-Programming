//============================================================================
// Name        : UVA 12003 - Array Transformer: SQRT Decomposition
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define MAX 300005
#define MAXSQR 600

#define ll long long

int N, Q, x, y, pos, SQRSize;
ll A[MAX], u, value;
vector<ll> groups[MAXSQR];

void update(int pos, ll value)
{
    int idx = pos / SQRSize;
    int size = groups[idx].size();

    int curr = lower_bound(groups[idx].begin(), groups[idx].end(), A[pos]) - groups[idx].begin();
    groups[idx][curr] = value;

    int j = curr;
    while (groups[idx][j-1] > groups[idx][j] && j > 0)
    {
        swap(groups[idx][j-1], groups[idx][j]);
        j--;
    }

    j = curr;
    while (groups[idx][j+1] < groups[idx][j] && j < size - 1)
    {
        swap(groups[idx][j+1], groups[idx][j]);
        j++;
    }

    // updating array value
    A[pos] = value;
}

ll process(int idx, ll value)
{
    int size = groups[idx].size();

    if (groups[idx][size - 1] < value)
        return (ll) size;

    ll lower = lower_bound(groups[idx].begin(), groups[idx].end(), value)
                    - groups[idx].begin();

    return lower;
}

ll query(int a, int b, ll value)
{
    int x = a / SQRSize;
    int y = b / SQRSize;

    ll total = 0;

    for (int val = a; val < (x + 1) * SQRSize; val++)
        if (A[val] < value)
            total++;

    for (int val = x + 1; val < y; val++)
        total += process(val, value);

    for (int val = y * SQRSize; val <= b; val++)
        if (A[val] < value)
            total++;

    return total;
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d%d%lld", &N, &Q, &u);

    SQRSize = sqrt(N) + 1;

    for (int i = 0; i <= SQRSize; i++)
        groups[i].clear();

    for (int i = 0; i < N; i++)
    {
        scanf("%lld", &A[i]);
        groups[i / SQRSize].push_back(A[i]);
    }

    // sorting groups
    for (int i = 0; i <= SQRSize; i++)
        sort(groups[i].begin(), groups[i].end());

    while (Q--)
    {
        scanf("%d%d%lld%d", &x, &y, &value, &pos);
        ll k = query(x - 1, y - 1, value);

        ll nvalue = (u * k) / (y - x + 1);
        update(pos - 1, nvalue);
    }

    for (int i = 0; i < N; i++)
        printf("%lld\n", A[i]);

    return 0;
}
