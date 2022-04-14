//============================================================================
// Name        : SPOJ RACETIME Problem with SQRT Decomposition
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <bits/stdc++.h>

using namespace std;
#define MAX 100005
#define MAXSQR 320

int N, K, a, b, pos, value;
int SQRSize, A[MAX];
vector<int> RMQ[MAXSQR];
char op;

void update(int pos, int value)
{
    int idx = pos / SQRSize;
    int curr = lower_bound(RMQ[idx].begin(), RMQ[idx].end(), A[pos]) - RMQ[idx].begin();

    RMQ[idx][curr] = value;
    sort(RMQ[idx].begin(), RMQ[idx].end());

    // updating value
    A[pos] = value;
}

int query(int a, int b)
{
    int x = a / SQRSize;
    int y = b / SQRSize;

    int total = 0;

    if (x == y)
    {   // same block
        for (int j = a; j <= b; j++)
            if (A[j] <= value) total++;
    }
    else
    {
        // processing first block
        for (int j = a; j < (x + 1) * SQRSize; j++)
            if (A[j] <= value) total++;

        // processing middle blocks
        for (int j = x + 1; j < y; j++)
            total += upper_bound(RMQ[j].begin(), RMQ[j].end(), value) - RMQ[j].begin();

        // processing last block
        for (int j = y * SQRSize; j <= b; j++)
            if (A[j] <= value) total++;
    }
    return total;
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d%d\n", &N, &K);
    SQRSize = sqrt(N) + 1;

    for (int i = 0; i <= SQRSize; i++)
        RMQ[i].clear();

    // initialize
    for (int i = 0; i < N; i++)
    {
        scanf("%d\n", &A[i]);
        RMQ[i / SQRSize].push_back(A[i]);
    }

    // sorting every block
    for (int i = 0; i <= SQRSize; i++)
        sort(RMQ[i].begin(), RMQ[i].end());

    // solving queries
    for (int j = 0; j < K; j++)
    {
        scanf("%c ", &op);
        if (op == 'M')
        {   // update
            scanf("%d%d\n", &pos, &value);
            update(pos - 1, value);
        }
        else if (op == 'C')
        {   // query
            scanf("%d%d%d\n", &a, &b, &value);
            printf("%d\n", query(a - 1, b - 1));
        }
    }
    return 0;
}
