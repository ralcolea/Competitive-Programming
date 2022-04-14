//==================================================================================
// Contest     : SPOJ Online Judge
// Problem     : QTREE2 - Query on a tree II
// Author      : Rubén Alcolea Núñez
// Description : Lowest Common Ancestor - Binary Lifting
//==================================================================================
 
#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 10005;
const int MAXLOG = 20;
 
int casos, a, b, n, l, value;
vector<int> adj[MAX], weight[MAX];
 
int up[MAX][MAXLOG], dist[MAX], depth[MAX];
 
int timer, queries, root;
int tin[MAX], tout[MAX];
string query;
 
void dfs(int v, int p)
{
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i = 1; i <= l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
 
	for (size_t next = 0; next < adj[v].size(); next++)
	{
		if (adj[v][next] != p) {
			dist[adj[v][next]] = dist[v] + weight[v][next];
			depth[adj[v][next]] = depth[v] + 1;
			dfs(adj[v][next], v);
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
	dist[root] = 0;
	depth[root] = 0;
	dfs(root, root);
}
 
int compute(int u, int v, int k)
{
	int LCA = lca(u, v);
 
	// The kth vertex is on the path from u to LCA
	if (depth[u] - depth[LCA] + 1 >= k) {
		for (int i = l; i >= 0; i--) {
			if (is_ancestor(LCA, up[u][i]) && k - (1 << i) > 0) {
				u = up[u][i];
				k -= (1 << i);
			}
		}
		return u;
	}
 
	// The kth vertex is on the path from LCA to v
	// update kth value removing the vertexes going from u to LCA
	k -= depth[u] - depth[LCA] + 1;
	k = depth[v] - depth[LCA] + 1 - k;
	for (int i = l; i >= 0; i--) {
		if (is_ancestor(LCA, up[v][i]) && k - (1 << i) > 0) {
			v = up[v][i];
			k -= (1 << i);
		}
	}
	return v;
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
		cin >> n;
		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			weight[i].clear();
		}
 
		// reading edges info
		for (int i = 1; i < n; i++) {
			cin >> a >> b >> value;
			adj[a].push_back(b);    weight[a].push_back(value);
			adj[b].push_back(a);    weight[b].push_back(value);
		}
 
		preprocess(root = 1);
		cin >> query;
		while (query != "DONE")
		{
			if (query == "DIST") {
				cin >> a >> b;
 
				int LCA = lca(a, b);
				cout << dist[a] + dist[b] - 2 * dist[LCA] << "\n";
			}
			else if (query == "KTH") {
				cin >> a >> b >> value;
				cout << compute(a, b, value) << "\n";
			}
			cin >> query;
		}
		cout << "\n";
	}
	return 0;
}