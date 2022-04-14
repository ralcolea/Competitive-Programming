//============================================================================
// Name        : Codeforces 348 Div 1 C: Subset sums
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Sqrt Decomposition
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAXN   100005
#define MAXSQR 320
#define ll long long

struct range
{
    int a, b, sign;
    range(int aa, int bb, int ss)
    {
        a = aa;
        b = bb;
        sign = ss;
    }
};

int n, m, queries, SQRSize, a, b;
ll num[MAXN], upd_group[MAXSQR], sum_group[MAXSQR];
vector<range> groups[MAXN];

ll query_range(int a, int b)
{
    ll total = 0;
    int x = a / SQRSize;
    int y = b / SQRSize;
    if (x == y)
    {
        for (int val = a; val <= b; val++)
            total += num[val] + upd_group[x];
    }
    else
    {
        // processing first group
        for (int val = a; val < (x + 1) * SQRSize; val++)
            total += num[val] + upd_group[x];

        // processing middle groups
        for (int val = x + 1; val < y; val++)
            total += sum_group[val];

        // processing last group
        for (int val = y * SQRSize; val <= b; val++)
            total += num[val] + upd_group[y];
    }

    return total;
}

ll query(int index)
{
    ll total = 0;
    for (unsigned int i = 0; i < groups[index].size(); i++)
    {
        a = groups[index][i].a;
        b = groups[index][i].b;
        int sign = groups[index][i].sign;
        total += sign * query_range(a, b);
    }
    return total;
}

void update_range(int a, int b, ll value)
{
    int x = a / SQRSize;
    int y = b / SQRSize;

    if (x == y)
    {   // same group
        for (int val = a; val <= b; val++)
            num[val] += value;
    }
    else
    {
        // processing first group
        for (int val = a; val < (x + 1) * SQRSize; val++)
            num[val] += value;

        // processing middle groups
        for (int val = x+1; val < y; val++)
        {
            upd_group[val] += value;
            sum_group[val] += (value * SQRSize);
        }

        // processing last group
        for (int val = y * SQRSize; val <= b; val++)
            num[val] += value;
    }
}

void update(int index, ll value)
{
    for (unsigned int i = 0; i < groups[index].size(); i++)
    {
        a = groups[index][i].a;
        b = groups[index][i].b;
        int sign = groups[index][i].sign;
        update_range(a, b, sign * value);
    }
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> queries;

    // sqrt initialization
    SQRSize = sqrt(n) + 1;
    for (int i = 0; i <= SQRSize; i++)
        sum_group[i] = upd_group[i] = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
        sum_group[i / SQRSize] += num[i];
    }

    for (int j = 0; j < m; j++)
    {
        int k;
        groups[j].clear();
        cin >> k;
        int mx = 0, mn = n, aux[MAXN];
        for (int i = 0; i < k; i++)
        {
            cin >> aux[i];
            aux[i]--;
            mx = max(mx, aux[i]);
            mn = min(mn, aux[i]);
        }
        // inserting range [mvn, mx];
        groups[j].push_back(range(mn, mx, +1));
        sort(aux, aux + k);
        for (int i = 0; i < k-1; i++)
            if (aux[i] + 1 <= aux[i+1] - 1)
                groups[j].push_back(range(aux[i] + 1, aux[i+1] - 1, -1));
    }

    for (int q = 0; q < queries; q++)
    {
        char type;
        int index;
        cin >> type >> index;
        index--;
        if (type == '?')
        {
            cout << query(index) << "\n";
        }
        else if (type == '+')
        {
            ll v;
            cin >> v;
            update(index, v);
        }
    }
    return 0;
}
