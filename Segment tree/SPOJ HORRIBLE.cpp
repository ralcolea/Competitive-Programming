//============================================================================
// Name        : SPOJ HORRIBLE - Horrible Queries
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Segment Tree + Lazy Propagation
//============================================================================

#include <bits/stdc++.h>
using namespace std;
#define MAX 100005

#define ll long long

struct node
{
    ll value;
    ll lazy;

    node()
    {
        value = 0;
        lazy = 0;
    }
};

ll v;
int N, Q, casos, x, y, c;
node tree[MAX << 2];

void build(int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        tree[node].value = tree[node].lazy = 0;
        return;
    }

    int middle = (start + end) / 2;
    build(2 * node, start, middle);
    build(2 * node + 1, middle + 1, end);
    tree[node].value = tree[node].lazy = 0;
}

void update(int node, int start, int end, ll value)
{
    tree[node].lazy  += value;
    tree[node].value += (end - start + 1) * value;
}

void shift(int node, int start, int end)
{
    if (tree[node].lazy)
    {
        int middle = (start + end) / 2;
        update(2 * node, start, middle, tree[node].lazy);
        update(2 * node + 1, middle + 1, end, tree[node].lazy);
        tree[node].lazy = 0; // lazy is pushed
    }
}

void increase(int a, int b, ll value, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
    {
        update(node, start, end, value);
        return;
    }

    // pushing lazy propagation
    shift(node, start, end);

    //otherwise, we split the interval
    int middle = (start + end) / 2;
    increase(a, b, value, 2 * node, start, middle);
    increase(a, b, value, 2 * node + 1, middle + 1, end);
    tree[node].value = tree[2 * node].value + tree[2 * node + 1].value;
}

ll query(int a, int b, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return 0;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
        return tree[node].value;

    // pushing lazy propagation
    shift(node, start, end);

    int middle = (start + end) / 2;
    return query(a, b, 2 * node, start, middle) +
           query(a, b, 2 * node + 1, middle + 1, end);
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d", &casos);
    while (casos--)
    {
        scanf("%d%d", &N, &Q);
        build();

        while (Q--)
        {
            scanf("%d", &c);
            if (c == 0)
            {
                scanf("%d%d%lld", &x, &y, &v);
                increase(x, y, v);
            }
            else if (c == 1)
            {
                scanf("%d%d", &x, &y);
                printf("%lld\n", query(x, y));
            }
        }
    }
    return 0;
}
