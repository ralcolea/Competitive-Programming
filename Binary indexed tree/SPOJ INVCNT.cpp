//============================================================================
// Name        : SPOJ INVCNT - Inversion Count
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Binary Indexed Tree
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define MAX 200005
#define ll long long

int casos, N;
long long fenwick[MAX];
int A[MAX], B[MAX];

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
        scanf("%d", &N);
        for (int i = 1; i <= N; i++)
        {
            scanf("%d", &A[i]);
            B[i] = A[i];
            fenwick[i] = 0;
        }

        sort(A + 1, A + N + 1);
        ll total = 0;
        for (int i = N; i >= 1; i--)
        {
            ll index = lower_bound(A + 1, A + N + 1, B[i]) - A;
            total += read(index - 1, fenwick);

            // updating fenwick tree
            update(+1, index, fenwick);
        }

        printf("%lld\n", total);
    }

    return 0;
}
