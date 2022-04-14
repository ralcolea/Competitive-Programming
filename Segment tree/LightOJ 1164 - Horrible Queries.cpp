//============================================================================
// Name        : 1164 - Horrible Queries
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
    long long value;
    long long lazy;
 
    node()
    {
        value = 0;
        lazy = 0;
    }
};
 
int Q, casos, x, y, c, v;
int N, number = 1;
node tree[MAX << 2];
 
void initialize(int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        tree[node].value = 0;
        tree[node].lazy = 0;
        return;
    }
 
    int middle = (start + end) / 2;
    initialize(2 * node, start, middle);
    initialize(2 * node + 1, middle + 1, end);
    tree[node].value = tree[2 * node].value + tree[2 * node + 1].value;
    tree[node].lazy = 0;
}
 
void update(int node, int start, int end, int value)
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
        tree[node].lazy = 0; // passing is done
    }
}
 
void increase(int a, int b, int value, int node = 1, int start = 1, int end = N)
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
 
    //otherwise, we split the interval
    shift(node, start, end);
    int middle = (start + end) / 2;
    increase(a, b, value, 2 * node, start, middle);
    increase(a, b, value, 2 * node + 1, middle + 1, end);
    tree[node].value = tree[2 * node].value + tree[2 * node + 1].value;
}
 
long long query(int a, int b, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a) return 0;
 
    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b) return tree[node].value;
 
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
        initialize();
 
        printf("Case %d:\n", number++);
        while (Q--)
        {
            scanf("%d", &c);
            if (c == 0)
            {
                scanf("%d%d%d", &x, &y, &v);
                increase(x + 1, y + 1, v);
            }
            else if (c == 1)
            {
                scanf("%d%d", &x, &y);
                printf("%lld\n", query(x + 1, y + 1));
            }
        }
    }
    return 0;
}
