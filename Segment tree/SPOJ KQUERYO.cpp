//============================================================================
// Name        : SPOJ KQUERYO - K-Query Online
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Segment Tree with vectors
//============================================================================

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
#define MAX 30005

int N, Q, x, y, value, ans;
vector<int> tree[MAX << 2];

void build(int node = 1, int start = 1, int end = N)
{
    if (start == end)
    {
        scanf("%d", &value);
        tree[node].push_back(value);
        return;
    }

    int middle = (start + end) / 2;
    build(2 * node, start, middle);
    build(2 * node + 1, middle + 1, end);

    merge(tree[2 * node].begin(), tree[2 * node].end(),
          tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
            back_inserter(tree[node]));
}

int query(int a, int b, int value, int node = 1, int start = 1, int end = N)
{
    // if [start,end] is outside of [a,b]
    if (start > b || end < a)
        return 0;

    // if [start,end] is inside of [a,b]
    if (start >= a && end <= b)
        return tree[node].size() -
               (upper_bound(tree[node].begin(), tree[node].end(), value) - tree[node].begin());

    // otherwise, we split the interval
    int middle = (start + end) / 2;
    return query(a, b, value, 2 * node, start, middle) +
           query(a, b, value, 2 * node + 1, middle + 1, end);
}

int main()
{
    //freopen("../build-ACM/entrada.txt", "r", stdin);
    scanf("%d", &N);
    build();
    scanf("%d", &Q);
    ans = 0;
    while (Q--)
    {
        scanf("%d%d%d", &x, &y, &value);
        x = x ^ ans;  if (x < 1) x = 1;
        y = y ^ ans;  if (y > N) y = N;
        value = value ^ ans;
        if (x > y) ans = 0;
        else
            ans = query(x, y, value);
        printf("%d\n", ans);
    }
    return 0;
}
