//============================================================================
// Name        : SPOJ BRCKTS - Brackets
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Segment Tree
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define MAX 30005
#define ll long long

struct node
{
    int open;
    int closed;

    node()
    {
        open = closed = 0;
    }
};

node merge(node a, node b)
{
    node res;

    if (a.open && b.closed)
    {
        int m = min(a.open, b.closed);
        a.open -= m;
        b.closed -= m;
    }

    res.open   = a.open + b.open;
    res.closed = a.closed + b.closed;
    return res;
}

int N, M, value;
node tree[MAX << 2];
char x[MAX];

void build(int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        if (x[start] == '(')
        {
            tree[node].open = 1;
            tree[node].closed = 0;
        }
        else if (x[start] == ')')
        {
            tree[node].closed = 1;
            tree[node].open = 0;
        }
        return;
    }

    int middle = (start + end) / 2;
    build(2 * node, start, middle);
    build(2 * node + 1, middle + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

void update(int pos, int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        swap(tree[node].open, tree[node].closed);
        return;
    }

    //we split the interval
    int middle = (start + end) / 2;

    if (pos <= middle)
        update(pos, 2 * node, start, middle);
    else
        update(pos, 2 * node + 1, middle + 1, end);

    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

int query(int node = 1)
{
    return tree[node].open + tree[node].closed;
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    for (int i = 1; i <= 10; i++)
    {
        scanf("%d", &N);
        scanf("%s", x + 1);

        build();

        printf("Test %d:\n", i);

        scanf("%d", &M);
        for (int j = 1; j <= M; j++)
        {
            scanf("%d", &value);
            if (value)
                update(value);
            else
            {
                if (query() == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
            }
        }
    }
    return 0;
}
