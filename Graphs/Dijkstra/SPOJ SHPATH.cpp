//==================================================================================
// Name        : SPOJ SHPATH - The Shortest Path
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Dijkstra's algorithm with priority queue to find single shortest path
//==================================================================================
#define Max 10003
#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
 
typedef pair<int, int> par;
 
struct camino
{
	int origen, destino, costo;
};
 
int i, j, p1, p2, total;
int k, l, casos, n, m, costo;
int distancia[Max];
string ciudad, origen, destino;
map<string, int> ciudades;
vector<camino> conexion[10005];
camino conex;
bool mark[Max];
char cad[50];
 
int Dijkstra(int origen, int destino)
{
	memset(mark, 0, sizeof(mark));
	memset(distancia, 0x7f, sizeof(distancia));
	priority_queue<par, vector<par>, greater<par> > cola;
	cola.push(make_pair(0, origen));
	distancia[origen] = 0;
	int d, v = 0;
	while (cola.size() && v != p2)
	{
		par x = cola.top(); cola.pop();
		d = x.first, v = x.second;
		if (mark[v]) continue;
		mark[v] = true;
 
		int tam = conexion[v].size();
		for (int i = 0; i < tam; i++)
		{
			int w = conexion[v][i].destino, wt = conexion[v][i].costo;
			if (d + wt < distancia[w])
				distancia[w] = d + wt, cola.push(make_pair(d + wt, w));
		}
	}
	return distancia[p2];
}
 
int main()
{
	scanf("%d", &casos);
	while (casos--)
	{
		scanf("%d", &n);
		for (int l = 1; l <= n; l++)
		{
			scanf("%s", &cad);
			ciudad = cad;
			ciudades[ciudad] = l;
			scanf("%d", &total);
 
			conexion[l].clear();
 
			for (j = 1; j <= total; j++)
			{
				scanf("%d %d", &conex.destino, &conex.costo);
				conexion[l].push_back(conex);
			}
		}
		memset(mark, 0, sizeof(mark));
		scanf("%d", &m);
		for (k = 1; k <= m; k++)
		{
			scanf("%s", &cad);
			origen = cad;
			scanf("%s", &cad);
			destino = cad;
			p1 = ciudades[origen];    p2 = ciudades[destino];
			printf("%d\n", Dijkstra(p1, p2));
		}
		ciudades.clear();
	}
	return 0;
} 