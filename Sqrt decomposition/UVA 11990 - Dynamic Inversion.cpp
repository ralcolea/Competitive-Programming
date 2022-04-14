//============================================================================
// Name        : UVA 11990: Dynamic Inversion
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Sqrt Decomposition
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAXN 200005
#define MAXSQR 455
#define ll long long

int N, K, value;
int SQRSize;
vector<int> blocks[MAXSQR];
ll position[MAXN], numbers[MAXN], tree[MAXN];
bool removed[MAXN];

ll upper(int a, int b, int v)
{
    ll total = 0;

    int x = a / SQRSize;
    int y = b / SQRSize;

    if (x == y)
    {
        for (int val = a; val <= b; val++)
        {
            if (numbers[val] > v && !removed[val])
                total++;
        }
    }
    else
    {
        // processing first block
        for (int val = a; val < (x + 1) * SQRSize; val++)
            if (numbers[val] > v && !removed[val])
                total++;

        // processing middle blocks
        for (int val = x + 1; val < y; val++)
            total += blocks[val].end() -
                    lower_bound(blocks[val].begin(), blocks[val].end(), v);

        // processing last block
        for (int val = y * SQRSize; val <= b; val++)
            if (numbers[val] > v && !removed[val])
                total++;
    }

    return total;
}

ll lower(int a, int b, int v)
{
    ll total = 0;

    int x = a / SQRSize;
    int y = b / SQRSize;

    if (x == y)
    {
        for (int val = a; val <= b; val++)
        {
            if (numbers[val] < v && !removed[val])
                total++;
        }
    }
    else
    {
        // processing first block
        for (int val = a; val < (x + 1) * SQRSize; val++)
            if (numbers[val] < v && !removed[val])
                total++;

        // processing middle blocks
        for (int val = x + 1; val < y; val++)
            total += lower_bound(blocks[val].begin(), blocks[val].end(), v)
                    - blocks[val].begin();

        // processing last block
        for (int val = y * SQRSize; val <= b; val++)
            if (numbers[val] < v && !removed[val])
                total++;
    }

    return total;
}

ll update(int v)
{
    int pos = position[v];
    removed[pos] = true;

    ll total = 0;
    total += upper(0, pos - 1, v);
    total += lower(pos + 1, N - 1, v);

    // removing value from blocks
    int x = pos / SQRSize;
    blocks[x].erase(lower_bound(blocks[x].begin(), blocks[x].end(), v));

    return total;
}

void update_tree(int index, ll value)
{
    while (index <= N)
    {
        tree[index] += value;
        index += (index & -index);
    }
}

ll query(int index)
{
    ll total = 0;
    while (index > 0)
    {
        total += tree[index];
        index -= (index & -index);
    }
    return total;
}

ll inversions()
{
    ll total = 0;
    for (int i = N-1; i >= 0; i--)
    {
        int v = numbers[i];
        total += query(v);
        update_tree(v, +1LL);
    }
    return total;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    while (cin >> N >> K)
    {
        SQRSize = sqrt(N) + 1;
        for (int i = 0; i <= SQRSize; i++)
            blocks[i].clear();

        for (int i = 0; i < N; i++)
        {
            cin >> value;
            numbers[i] = value;
            position[value] = i;
            blocks[i / SQRSize].push_back(value);
            removed[i] = false;
            tree[i + 1] = 0;
        }

        // ordering blocks
        for (int i = 0; i <= SQRSize; i++)
            sort(blocks[i].begin(), blocks[i].end());

        ll total = inversions();
        // processing queries
        while (K--)
        {
            cin >> value;
            cout << total << "\n";
            total -= update(value);
        }
    }
    return 0;
}
