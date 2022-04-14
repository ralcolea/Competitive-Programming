//============================================================================
// Name        : SPOJ LITE - Light Switching
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Segment Tree + Lazy Propagation
//============================================================================

#include <bits/stdc++.h>
using namespace std;
#define MAX 100005

struct node
{
    int lazy;
    int lightsOn;
    int lightsOff;

    node()
    {
        lazy = 0;
        lightsOn = lightsOff = 0;
    }
};

node merge(node a, node b)
{
    node res;
    res.lightsOff = a.lightsOff + b.lightsOff;
    res.lightsOn  = a.lightsOn + b.lightsOn;
    return res;
}

int N, Q, x, y, c;
node tree[MAX << 2];

void build(int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        tree[node].lightsOff = 1;
        tree[node].lightsOn = 0;
        tree[node].lazy = 0;
        return;
    }

    int middle = (start + end) / 2;
    build(2 * node, start, middle);
    build(2 * node + 1, middle + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    tree[node].lazy = 0;
}

void update(int node, int value)
{
    tree[node].lazy += value;

    // changing lamps after toggling a switch
    if (value % 2)
        swap(tree[node].lightsOff, tree[node].lightsOn);
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

void modify(int a, int b, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
    {
        update(node, +1);
        return;
    }

    // pushing lazy propagation
    shift(node);

    //otherwise, we split the interval
    int middle = (start + end) / 2;
    modify(a, b, 2 * node, start, middle);
    modify(a, b, 2 * node + 1, middle + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

int query(int a, int b, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return 0;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
        return tree[node].lightsOn;

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
            modify(x, y);
        }
        else if (c == 1)
        {
            scanf("%d%d", &x, &y);
            printf("%d\n", query(x, y));
        }
    }
    return 0;
}
