//============================================================================
// Name          : UVA 12436 - Rip Van Winkle's Code
// Author        : Rubén Alcolea Núñez
// Classification: Data Structures
// Description   : Segment Tree + Linear functions
//============================================================================
#include <bits/stdc++.h>
using namespace std;

#define MAXN 262144
#define MAXM 1048576 + 10
#define ll long long

int queries, x, y;
char type;
ll sum[MAXM], lazyA[MAXM], lazyB[MAXM];
ll lambdaA[MAXM], lambdaB[MAXM], value[MAXM];
bool set_lazy[MAXM];
ll v;

void update_interval_A(int node, int start, int end, ll lambda, ll operations)
{
    ll k = end - start + 1;
    ll s = (k * (k + 1)) / 2;
    sum[node] += k * lambda + operations * s;
    lambdaA[node] += lambda;
    lazyA[node] += operations;
}

void update_interval_B(int node, int start, int end, ll lambda, ll operations)
{
    ll k = end - start + 1;
    ll s = (k * (k + 1)) / 2;
    sum[node] += k * lambda + operations * s;
    lambdaB[node] += lambda;
    lazyB[node] += operations;
}

void set_interval(int node, int start, int end, ll v)
{
    sum[node] = (end - start + 1) * v;
    set_lazy[node] = true;
    value[node] = v;
    lambdaA[node] = lambdaB[node] = 0;
    lazyA[node] = lazyB[node] = 0;
}

void shift(int node, int start, int end)
{   // lazy propagation
    int middle = (start + end) / 2;

    if (set_lazy[node])
    {
        set_interval(2 * node, start, middle, value[node]);
        set_interval(2 * node + 1, middle + 1, end, value[node]);
        set_lazy[node] = false;
    }

    if (lazyA[node])
    {
        ll change = (middle + 1 - start) * lazyA[node];
        update_interval_A(2 * node, start, middle, lambdaA[node], lazyA[node]);
        update_interval_A(2 * node + 1, middle + 1, end, lambdaA[node] + change, lazyA[node]);
        lambdaA[node] = lazyA[node] = 0; // lazy is pushed
    }

    if (lazyB[node])
    {
        ll change = (middle + 1 - start) * lazyB[node];
        update_interval_B(2 * node, start, middle, lambdaB[node] + change, lazyB[node]);
        update_interval_B(2 * node + 1, middle + 1, end, lambdaB[node], lazyB[node]);
        lambdaB[node] = lazyB[node] = 0; // lazy is pushed
    }
}

void updateA(int a, int b, int node, int start, int end)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
    {
        ll k = end - start + 1;
        ll s = (k * (k + 1)) / 2;
        sum[node] += k * (start - a) + s;
        lambdaA[node] += start - a;
        lazyA[node]++;
        return;
    }

    // pushing lazy propagation
    shift(node, start, end);

    //otherwise, we split the interval
    int middle = (start + end) / 2;
    updateA(a, b, 2 * node, start, middle);
    updateA(a, b, 2 * node + 1, middle + 1, end);
    sum[node] = sum[2 * node] + sum[2 * node + 1];
}

void updateB(int a, int b, int node, int start, int end)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
    {
        ll k = end - start + 1;
        ll s = (k * (k + 1)) / 2;
        sum[node] += k * (b - end) + s;
        lambdaB[node] += b - end;
        lazyB[node]++;
        return;
    }

    // pushing lazy propagation
    shift(node, start, end);

    //otherwise, we split the interval
    int middle = (start + end) / 2;
    updateB(a, b, 2 * node, start, middle);
    updateB(a, b, 2 * node + 1, middle + 1, end);
    sum[node] = sum[2 * node] + sum[2 * node + 1];
}

void set_range(int a, int b, ll v, int node, int start, int end)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
    {
        sum[node] = (end - start + 1) * v;
        set_lazy[node] = true;
        value[node] = v;
        lambdaA[node] = lambdaB[node] = 0;
        lazyA[node] = lazyB[node] = 0;
        return;
    }

    // pushing lazy propagation
    shift(node, start, end);

    //otherwise, we split the interval
    int middle = (start + end) / 2;
    set_range(a, b, v, 2 * node, start, middle);
    set_range(a, b, v, 2 * node + 1, middle + 1, end);
    sum[node] = sum[2 * node] + sum[2 * node + 1];
}

ll query(int a, int b, int node, int start, int end)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return 0;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
        return sum[node];

    // pushing lazy propagation
    shift(node, start, end);

    // otherwise, we split the interval
    int middle = (start + end) / 2;
    return query(a, b, 2 * node, start, middle) +
           query(a, b, 2 * node + 1, middle + 1, end);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //freopen("../build-ACM/entrada.txt", "r", stdin);
    // initialize
    memset(sum, 0, sizeof(sum));
    memset(lazyA, 0, sizeof(lazyA));
    memset(lazyB, 0, sizeof(lazyB));
    memset(lambdaA, 0, sizeof(lambdaA));
    memset(lambdaB, 0, sizeof(lambdaB));
    memset(value, 0, sizeof(value));
    memset(set_lazy, 0, sizeof(set_lazy));

    cin >> queries;
    while (queries--)
    {
        cin >> type >> x >> y;
        if (type == 'C')
        {
            cin >> v;
            set_range(x, y, v, 1, 1, MAXN);
        }
        else if (type == 'A')
        {
            updateA(x, y, 1, 1, MAXN);
        }
        else if (type == 'B')
        {
            updateB(x, y, 1, 1, MAXN);
        }
        else if (type == 'S')
        {
            cout << query(x, y, 1, 1, MAXN) << "\n";
        }
    }
    return 0;
}
