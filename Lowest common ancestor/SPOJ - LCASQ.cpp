//==================================================================================
// Contest     : SPOJ Online Judge
// Problem     : LCASQ - Lowest Common Ancestor
// Author      : Rubén Alcolea Núñez
// Description : Lowest Common Ancestor - Binary Lifting
//==================================================================================
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAX 10005
#define MAXLOG 20
 
int casos, a, b, n, m, l, v;
vector<int> adj[MAX];
 
int up[MAX][MAXLOG];
 
int timer, queries;
int tin[MAX], tout[MAX];
 
void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
 
    for (int u : adj[v])
    {
        if (u != p)
            dfs(u, v);
    }
 
    tout[v] = ++timer;
}
 
bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
 
int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}
 
void preprocess(int root)
{
    timer = 0;
    l = ceil(log2(n));
    dfs(root, root);
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("../build-ACM-Debug/entrada.txt", "r", stdin);
#endif
    cin.sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m;
        for (int j = 0; j < m; j++) {
            cin >> v;
            adj[i].push_back(v + 1);
        }
    }
    preprocess(1);
    cin >> queries;
    while (queries--)
    {
        cin >> a >> b;
        a++;   b++;
        cout << lca(a, b) - 1 << "\n";
    }
    return 0;
}