//============================================================================
// Name        : SPOJ GIVEAWAY Problem with SQRT Decomposition
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAXN 500005
#define MAXSQR 750

int N, K, a, b, idx, curr, value;
int A[MAXN], SQRSize, type;
vector<int> sqr[MAXSQR];

int process(int idx, int value)
{
    int size = sqr[idx].size();

    if (sqr[idx][size - 1] < value)
        return 0;

    int lower = lower_bound(sqr[idx].begin(), sqr[idx].end(), value) - sqr[idx].begin();
    return size - lower;
}

void update(int pos, int value)
{
    int idx = pos / SQRSize;
    int size = sqr[idx].size();

    curr = lower_bound(sqr[idx].begin(), sqr[idx].end(), A[pos]) - sqr[idx].begin();

    sqr[idx][curr] = value;

    int j = curr;
    while (sqr[idx][j] < sqr[idx][j-1] && j > 0)
    {
        swap(sqr[idx][j], sqr[idx][j-1]);
        j--;
    }

    j = curr;
    while (sqr[idx][j] > sqr[idx][j+1] && j < size - 1)
    {
        swap(sqr[idx][j], sqr[idx][j+1]);
        j++;
    }

    // updating array value
    A[pos] = value;
}

void solve()
{
    // ordering blocks
    for (int i = 0; i <= SQRSize; i++)
        sort(sqr[i].begin(), sqr[i].end());

    // processing queries
    scanf("%d", &K);
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &type);
        if (type == 0)
        {
            scanf("%d%d%d", &a, &b, &value);
            a--;  b--;

            int total = 0;

            int x = a / SQRSize;
            int y = b / SQRSize;

            if (x == y)
            {
                for (int val = a; val <= b; val++)
                {
                    if (A[val] >= value)
                        total++;
                }
            }
            else
            {
                // processing first block
                for (int val = a; val < (x + 1) * SQRSize; val++)
                    if (A[val] >= value)
                        total++;

                // processing middle blocks
                for (int val = x + 1; val < y; val++)
                    total += process(val, value);

                // processing last block
                for (int val = y * SQRSize; val <= b; val++)
                    if (A[val] >= value)
                        total++;
            }

            printf("%d\n", total);
        }
        else if (type == 1)
        {
            scanf("%d%d", &a, &value);
            update(a - 1, value);
        }
    }
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d", &N);
    SQRSize = sqrt(N) + 1;
    idx = curr = 0;

    for (int i = 0; i <= SQRSize; i++)
        sqr[i].clear();

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
        if (idx == SQRSize)
        {
            idx = 0;
            curr++;
        }

        sqr[curr].push_back(A[i]);
        idx++;
    }

    solve();
    return 0;
}
