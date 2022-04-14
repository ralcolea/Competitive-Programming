//============================================================================
// Name        : SPOJ MULTQ3 - Multiples of 3: Segment Tree + Lazy Propagation
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
    int lazy;
    int mod3;
    int mod2;
    int mod1;

    node()
    {
        lazy = 0;
        mod3 = mod2 = mod1 = 0;
    }
};

int N, Q, x, y, c;
node tree[MAX << 2];

node create(int value)
{
    node res;
    res.lazy = 0;
    res.mod1 = res.mod2 = res.mod3 = 0;

    value % 3 == 0 ? ++res.mod3 :
    value % 3 == 1 ? ++res.mod1 :
                     ++res.mod2;

    return res;
}

node merge(node a, node b)
{
    node res;
    res.mod1 = a.mod1 + b.mod1;
    res.mod2 = a.mod2 + b.mod2;
    res.mod3 = a.mod3 + b.mod3;

    return res;
}

void build(int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        tree[node] = create(0);
        return;
    }

    int middle = (start + end) / 2;
    build(2 * node, start, middle);
    build(2 * node + 1, middle + 1, end);

    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    tree[node].lazy = 0;
}

void update(int node, long long value)
{
    tree[node].lazy  += value;
    if (value % 3 == 1)
    {
        int x = tree[node].mod2;
        tree[node].mod2 = tree[node].mod1;
        tree[node].mod1 = tree[node].mod3;
        tree[node].mod3 = x;
    }
    else if (value % 3 == 2)
    {
        int x = tree[node].mod2;
        tree[node].mod2 = tree[node].mod3;
        tree[node].mod3 = tree[node].mod1;
        tree[node].mod1 = x;
    }
}

void shift(int node)
{
    if (tree[node].lazy)
    {
        update(2 * node, tree[node].lazy);
        update(2 * node + 1, tree[node].lazy);
        tree[node].lazy = 0; // passing is done
    }
}

void increase(int a, int b, long long value, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
    {
        update(node, value);
        return;
    }

    // pushing lazy propagation
    shift(node);

    //otherwise, we split the interval
    int middle = (start + end) / 2;
    increase(a, b, value, 2 * node, start, middle);
    increase(a, b, value, 2 * node + 1, middle + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

int query(int a, int b, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return 0;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
        return tree[node].mod3;

    // pushing lazy propagation
    shift(node);

    // otherwise, we split the interval
    int middle = (start + end) / 2;
    return query(a, b, 2 * node, start, middle) +
           query(a, b, 2 * node + 1, middle + 1, end);
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d%d", &N, &Q);
    build();

    while (Q--)
    {
        scanf("%d", &c);
        if (c == 0)
        {
            scanf("%d%d", &x, &y);
            increase(x + 1, y + 1, 1);
        }
        else if (c == 1)
        {
            scanf("%d%d", &x, &y);
            printf("%d\n", query(x + 1, y + 1));
        }
    }
    return 0;
}
