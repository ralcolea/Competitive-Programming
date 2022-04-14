//============================================================================
// Name        : Codeforces CROC 2013 - Problem E Copying Data: Segment Tree + Lazy Propagation
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;
#define MAX 100005

struct node
{
    bool lazy;
    bool copied;

    int ini;
    int fin;

    int x, a;

    node()
    {
        copied = 0;
        ini = fin = 0;
        lazy = 0;
    }
};

node merge(node a, node b)
{
    node res;
    if (a.copied == b.copied)
        res.copied = a.copied;

    if (a.fin + 1 == b.ini)
    {
        res.ini = a.ini;
        res.fin = b.fin;
    }

    return res;
}

int N, Q, x, y, c, value, k;
int A[MAX], B[MAX];
node tree[MAX << 2];

void build(int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        scanf("%d", &B[start]);
        tree[node].copied = 0;
        tree[node].lazy = 0;
        tree[node].ini = tree[node].fin = start;
        return;
    }

    int middle = (start + end) / 2;
    build(2 * node, start, middle);
    build(2 * node + 1, middle + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int x, int a)
{
    tree[node].ini = x + start - a;
    tree[node].fin = x + end - a;

    if (start < end)
    {
        tree[node].lazy = true;
        tree[node].a = a;
        tree[node].x = x;
    }

    tree[node].copied = true;
}

void shift(int node, int start, int end)
{
    if (tree[node].lazy)
    {
        int middle = (start + end) / 2;
        update(2 * node, start, middle, tree[node].x, tree[node].a);
        update(2 * node + 1, middle + 1, end, tree[node].x, tree[node].a);
        tree[node].lazy = 0; // passing is done
    }
}

void modify(int a, int b, int x, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
    {
        update(node, start, end, x, a);
        return;
    }

    // pushing lazy propagation
    shift(node, start, end);

    //otherwise, we split the interval
    int middle = (start + end) / 2;
    modify(a, b, x, 2 * node, start, middle);
    modify(a, b, x, 2 * node + 1, middle + 1, end);

    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

int query(int pos, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is inside of [a,b]
    if (start == end)
    {
        return tree[node].copied ? A[tree[node].ini] : B[tree[node].ini];
    }

    // pushing lazy propagation
    shift(node, start, end);

    // otherwise, we split the interval
    int middle = (start + end) / 2;

    if (pos <= middle)
        return query(pos, 2 * node, start, middle);
    else
        return query(pos, 2 * node + 1, middle + 1, end);
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d%d", &N, &Q);

    for (int i = 1; i <= N; i++)
        scanf("%d", &A[i]);

    build();

    while (Q--)
    {
        scanf("%d", &c);
        if (c == 1)
        {
            scanf("%d%d%d", &x, &y, &k);
            modify(y, y + k - 1, x);
        }
        else if (c == 2)
        {
            scanf("%d", &x);
            printf("%d\n", query(x));
        }
    }
    return 0;
}
