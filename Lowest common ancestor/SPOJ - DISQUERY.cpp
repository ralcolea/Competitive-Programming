//==================================================================================
// Contest     : SPOJ Online Judge
// Problem     : DISQUERY - Distance Query
// Author      : RubÃ©n Alcolea NÃºÃ±ez
// Description : Lowest Common Ancestor - Binary Lifting
//==================================================================================
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAX 100005
#define MAXLOG 20
 
struct node
{
	int parent;
	int max_edge;
	int min_edge;
	node(int p = 0, int mn = 0, int mx = 1e9)
	{
		parent = p;
		max_edge = mx;
		min_edge = mn;
	}
};
 
int a, b, n, l, cost;
vector<pair<int, int>> adj[MAX];
node up[MAX][MAXLOG];
 
int timer, queries;
int tin[MAX], tout[MAX];
 
void dfs(int v, int p, int min_cost, int max_cost)
{
	tin[v] = ++timer;
	up[v][0].parent = p;
	up[v][0].max_edge = max_cost;
	up[v][0].min_edge = min_cost;
 
	for (int i = 1; i <= l; ++i) {
		node p = up[v][i-1];
		up[v][i].parent = up[p.parent][i-1].parent;
		up[v][i].min_edge = min(p.min_edge, up[p.parent][i-1].min_edge);
		up[v][i].max_edge = max(p.max_edge, up[p.parent][i-1].max_edge);
	}
 
	for (pair<int, int> u : adj[v]) {
		if (u.first != p)
			dfs(u.first, v, u.second, u.second);
	}
 
	tout[v] = ++timer;
}
 
bool is_ancestor(int u, int v)
{
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}
 
int LCA(int u, int v)
{
	if (is_ancestor(u, v))
		return u;
	if (is_ancestor(v, u))
		return v;
	for (int i = l; i >= 0; --i) {
		if (!is_ancestor(up[u][i].parent, v))
			u = up[u][i].parent;
	}
	return up[u][0].parent;
}
 
void preprocess(int root) {
	timer = 0;
	l = ceil(log2(n));
	dfs(root, root, 1e9, 0);
}
 
pair<int, int> compute(int u, int v)
{
	int lca = LCA(u, v);
 
	int min_edge = 1e9;
	int max_edge = 0;
 
	for (int i = l; i >= 0; i--)
		if (is_ancestor(lca, up[u][i].parent)) {
			min_edge = min(min_edge, up[u][i].min_edge);
			max_edge = max(max_edge, up[u][i].max_edge);
			u = up[u][i].parent;
		}
 
	for (int i = l; i >= 0; i--)
		if (is_ancestor(lca, up[v][i].parent)) {
			min_edge = min(min_edge, up[v][i].min_edge);
			max_edge = max(max_edge, up[v][i].max_edge);
			v = up[v][i].parent;
		}
 
	return make_pair(min_edge, max_edge);
}
 
int main()
{
#ifndef ONLINE_JUDGE
	freopen("../build-ACM-Debug/entrada.txt", "r", stdin);
#endif
	cin.sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		cin >> a >> b >> cost;
		adj[a].push_back(make_pair(b, cost));
		adj[b].push_back(make_pair(a, cost));
	}
	preprocess(1);
	cin >> queries;
	while (queries--)
	{
		cin >> a >> b;
		auto sol = compute(a, b);
		cout << sol.first << " " << sol.second << "\n";
	}
	return 0;
}
 