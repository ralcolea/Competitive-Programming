//==================================================================================
// Name        : SPOJ EAGLE1 - Eagle and Dogs
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Dfs and diameter
//==================================================================================
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAXN 100000 + 5
typedef long long ll;
 
int casos, n, a, b;
int farthest = 1;
ll dist[MAXN], weight;
vector<pair<int, ll>> adjacency[MAXN];
 
void dfs(int curr_node, int prev_node, ll curr_dist)
{
	// Actualizando el arreglo de distancia máxima a un nodo
	dist[curr_node] = max(dist[curr_node], curr_dist);
 
	if (dist[curr_node] > weight) {
		weight = dist[curr_node];
		farthest = curr_node;
	}
 
	for (auto next : adjacency[curr_node])
		if (next.first != prev_node) {
			dfs(next.first, curr_node, curr_dist + next.second);
	}
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
			// Inicializando lista de adyacencia
			adjacency[i].clear();
			// Inicializando arreglo de distancias
			dist[i] = 0;
		}
 
		for (int i = 1; i < n; i++) {
			cin >> a >> b >> weight;
			adjacency[a].push_back(make_pair(b, weight));
			adjacency[b].push_back(make_pair(a, weight));
		}
 
		weight = 0;
		dfs(farthest = 1, 0, 0LL);
		dfs(farthest, 0, 0LL);
		dfs(farthest, 0, 0LL);
 
		cout << dist[1];
		for (int i = 2; i <= n; i++)
			cout << " " << dist[i];
		cout << "\n";
	}
	return 0;
}