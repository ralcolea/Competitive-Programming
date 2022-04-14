//==================================================================================
// Contest     : SPOJ Online Judge
// Problem     : ADAORANG - Ada and Orange Tree
// Author      : Rubén Alcolea Núñez
// Description : Lowest Common Ancestor - Binary Lifting
//==================================================================================
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAX 5 * 100000
#define MAXLOG 20
 
int casos, a, b, n, m, l, v;
vector<int> adj[MAX];
bitset<255> shades[MAX];
 
int up[MAX][MAXLOG];
 
int timer, queries, root;
int tin[MAX], tout[MAX];
 
void dfs(int v, int p)
{
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i = 1; i <= l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
 
	for (int u : adj[v])
	{
		if (u != p) {
			dfs(u, v);
			shades[v] |= shades[u];
		}
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
 
int compute(int u, int v)
{
	if (u == v)
		return shades[u].count();
 
	return shades[lca(u, v)].count();
}
 
int main()
{
#ifndef ONLINE_JUDGE
	freopen("../build-ACM-Debug/entrada.txt", "r", stdin);
#endif
	cin.sync_with_stdio(0);
	cin.tie(0);
 
	cin >> casos;
	while (casos--)
	{
		cin >> n >> queries >> root;
		// reading shades
		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			shades[i].reset();
 
			cin >> v;
			shades[i].set(v, true);
		}
 
		// reading edges info
		for (int i = 1; i < n; i++) {
			cin >> a >> b;
			a++;   b++;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
 
		preprocess(root + 1);
		while (queries--)
		{
			cin >> a >> b;
			a++;   b++;
			cout << compute(a, b) << "\n";
		}
	}
	return 0;
}