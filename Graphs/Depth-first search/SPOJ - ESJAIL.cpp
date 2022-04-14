//============================================================================
// Name        : SPOJ ESJAIL - Escape from Jail
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Dfs to determine whether is possible to escape from jail
//============================================================================
 
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <string.h>
using namespace std;
#define MAXN 100005
 
int N, K, M, i, j, x, y;
int pred[MAXN], keys[MAXN];
bool mark[MAXN], pending[MAXN], sol;
vector<int> graph[MAXN];
 
void dfs(int node)
{
	mark[node] = true;
 
	int size = graph[node].size();
	for (int i = 0; i < size; i++)
	{
		int v = graph[node][i];
 
		// if the adjacent node is not visited
		if (!mark[v])
		{
			// if the door is not opened
			if (pred[v] && !mark[pred[v]])
				pending[v] = true;
 
			// if I can pass, the I pass
			if (mark[pred[v]] && !pending[v])
				dfs(v);
		}
	}
 
	// if I get a new key, I visit adjacent node
	if (!mark[keys[node]] && pending[keys[node]])
	{
		pending[keys[node]] = false;
		dfs(keys[node]);
	}
 
	if (mark[N])
	{
		sol = true;
		return;
	}
}
 
int main()
{
	//freopen("src/entrada.txt", "r", stdin);
	while (scanf("%d%d%d", &N, &K, &M))
	{
		if (N == -1)
			break;
 
		// cleaning data structures
		for (i = 0; i < N; i++)
			graph[i].clear();
 
		memset(mark, 0, sizeof(mark));
		memset(pred, 0, sizeof(pred));
		memset(keys, 0, sizeof(keys));
		memset(pending, 0, sizeof(pending));
 
		// reading keys relationship
		for (i = 0; i < K; i++)
		{
			scanf("%d%d", &x, &y);
			pred[y] = x;
			keys[x] = y;
		}
 
		// reading adjacency of the graph
		for (i = 0; i < M; i++)
		{
			scanf("%d%d", &x, &y);
			graph[x].push_back(y);
			graph[y].push_back(x);
		}
 
		sol = false;
		mark[0] = true;
		dfs(1);
 
		if (sol)
			printf("Y\n");
		else
			printf("N\n");
	}
	return 0;
}