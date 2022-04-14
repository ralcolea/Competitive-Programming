//==================================================================================
// Name        : SPOJ PT07Z - Longest path in a tree
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Two dfs to find the diameter of the tree
//==================================================================================
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAXN 10005
 
int casos, n, a, b;
int farthest = 1;
int dist[MAXN], weight;
int last_edge[MAXN << 1], destination_edge[MAXN << 1], next_edge[MAXN << 1], edges;
 
void dfs(int curr_node, int prev_node, int curr_length)
{
	// Actualizando el arreglo de distancia mÃ¡xima a un nodo
	dist[curr_node] = max(dist[curr_node], curr_length);
 
	if (dist[curr_node] > weight) {
		weight = dist[curr_node];
		farthest = curr_node;
	}
 
	for (auto next = last_edge[curr_node]; next != 0; next = next_edge[next])
		if (destination_edge[next] != prev_node) {
			dfs(destination_edge[next], curr_node, curr_length + 1);
	}
}
 
void add_edge(int v1, int v2)
{
	destination_edge[++edges] = v2;
	next_edge[edges] = last_edge[v1];
	last_edge[v1] = edges;
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
		// Inicializando lista de adyacencia
		last_edge[i] = destination_edge[i] = next_edge[i] = 0;
		// Inicializando arreglo de distancias
		dist[i] = 0;
	}
 
	edges = 0;
	for (int i = 1; i < n; i++) {
		cin >> a >> b;
		add_edge(a, b);
		add_edge(b, a);
	}
 
	weight = 0;
	dfs(farthest = 1, 0, 0);
	dfs(farthest, 0, 0);
 
	cout << weight << "\n";
	return 0;
}
 