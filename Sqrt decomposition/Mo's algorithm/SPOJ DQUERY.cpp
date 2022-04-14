//============================================================================
// Name        : SPOJ D-QUERY 
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Mo's Algorithm
//============================================================================

#include <bits/stdc++.h>

using namespace std;
#define MAX 30005
#define MAXBLOCK 320
#define MAXQUERIES 200005
#define MAXVALUE 1000005

struct query
{
    int left, right, idx;
    query(int l = 0, int r = 0, int index = 0)
    {
        left = l;
        right = r;
        idx = index;
    }

    bool operator <(const query& y) const
    {
        if (left / MAXBLOCK != y.left / MAXBLOCK)
            return left / MAXBLOCK < y.left / MAXBLOCK;

        return right < y.right;
    }
};

int N, K, a, b;
int freq[MAXVALUE];
int A[MAX], ans;
int sol[MAXQUERIES];
query q[MAXQUERIES];

void add(int pos)
{
    freq[A[pos]]++;
    if (freq[A[pos]] == 1)
        ans++;
}

void remove(int pos)
{
    freq[A[pos]]--;
    if (freq[A[pos]] == 0)
        ans--;
}

void solve()
{
    // ordering queries for blocks
    sort(q + 1, q + K + 1);

    int currLeft = 0, currRight = 0;
    ans = 0;
    for (int i = 1; i <= K; i++)
    {
        int left  = q[i].left;
        int right = q[i].right;

        while (currLeft > left)
        {
            currLeft--;
            add(currLeft);
        }

        while (currLeft < left)
        {
            remove(currLeft);
            currLeft++;
        }

        while (currRight < right)
        {
            currRight++;
            add(currRight);
        }

        while (currRight > right)
        {
            remove(currRight);
            currRight--;
        }

        sol[q[i].idx] = ans;
    }

    for (int i = 1; i <= K; i++)
        printf("%d\n", sol[i]);
}

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &A[i]);

    scanf("%d", &K);
    for (int i = 1; i <= K; i++)
    {
        scanf("%d%d", &a, &b);
        q[i] = query(a, b, i);
    }

    solve();
    return 0;
}
