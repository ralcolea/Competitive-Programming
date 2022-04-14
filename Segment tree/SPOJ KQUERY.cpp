//============================================================================
// Name        : SPOJ KQUERY - K-Query
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Segment Tree
//============================================================================

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
#define MAXN 30005

struct query
{
    int i, j, k, pos;
    query(int x = 0, int y = 0, int kk = 0, int p = 0)
    {
        i = x;
        j = y;
        k = kk;
        pos = p;
    }
    bool operator <(const query other) const
    {
        return k < other.k;
    }
};

int N, Q, x, y, value;
int tree[MAXN << 2];
pair<int, int> a[MAXN];
vector<query> queries;
vector<int> ans;

void build(int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        scanf("%d", &value);
        a[start - 1].first  = value;
        a[start - 1].second = start;
        tree[node] = 1;
        return;
    }

    int middle = (start + end) / 2;
    build(2 * node, start, middle);
    build(2 * node + 1, middle + 1, end);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int pos, int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        tree[node] = 0;
        return;
    }

    //we split the interval
    int middle = (start + end) / 2;
    if (pos <= middle)
        update(pos, 2 * node, start, middle);
    else
        update(pos, 2 * node + 1, middle + 1, end);

    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int get_query(int a, int b, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return 0;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
        return tree[node];

    // otherwise, we split the interval
    int middle = (start + end) / 2;
    return get_query(a, b, 2 * node, start, middle) +
           get_query(a, b, 2 * node + 1, middle + 1, end);
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d", &N);
    build();
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++)
    {
        scanf("%d%d%d", &x, &y, &value);
        queries.push_back(query(x, y, value, i));
    }
    sort(a, a + N);
    sort(queries.begin(), queries.end());
    ans.reserve(Q + 1);
    int p = 0;
    for (int i = 0; i < Q; i++)
    {
        while (p < N && a[p].first <= queries[i].k)
            update(a[p++].second);

        ans[queries[i].pos] = get_query(queries[i].i, queries[i].j);
    }

    for (int i = 0; i < Q; i++)
        printf("%d\n", ans[i]);
    return 0;
}
