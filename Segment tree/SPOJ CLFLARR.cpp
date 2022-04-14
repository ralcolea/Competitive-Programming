//============================================================================
// Name        : SPOJ CLFLARR - COLORFUL ARRAY
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Ad Hoc
//============================================================================
#include <bits/stdc++.h>

using namespace std;
#define MAXN 200000 + 5

int n, queries, a, b, c;
int color[MAXN];
int tree[4 * MAXN];
int lazy[4 * MAXN];

void update(int node, int value)
{
    tree[node] = value;
    lazy[node] = value;
}

void push(int node)
{
    if (lazy[node]) {
        update(2 * node + 0, lazy[node]);
        update(2 * node + 1, lazy[node]);
        lazy[node] = 0;
    }
}

void set_color(int a, int b, int value, int node = 1, int start = 1, int end = n)
{
    // range outside
    if (start > b || end < a) return;

    // range completely inside
    if (start >= a && end <= b) {
        update(node, value);
        return;
    }

    // pushing lazy propagation
    push(node);

    // otherwise we split the interval
    int middle = (start + end) >> 1;
    set_color(a, b, value, 2 * node + 0, start, middle);
    set_color(a, b, value, 2 * node + 1, middle + 1, end);
}

void get_colors(int node, int start, int end)
{
    if (start == end) {
        color[start] = tree[node];
        return;
    }

    // pushing lazy propagation
    push(node);

    int middle = (start + end) >> 1;
    get_colors(2 * node + 0, start, middle);
    get_colors(2 * node + 1, middle + 1, end);
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> queries;
    while (queries--) {
        cin >> a >> b >> c;
        set_color(a, b, c);
    }

    get_colors(1, 1, n);
    for (int i = 1; i <= n; i++)
        cout << color[i] << "\n";
    return 0;
}
