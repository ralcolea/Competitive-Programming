//============================================================================
// Name        : SPOJ - Longest path in a tree
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Solution 1: DFS with dynamic programming on tree
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

#define endl "\n"

const int MAXN = 10005;

int n, diameter = 0;
vector<int> adj[MAXN];
int dist_to_leaf[MAXN];
int max_length[MAXN];

void dfs(int node, int last)
{
    dist_to_leaf[node] = max_length[node] = 0;

    int max_leaf1 = 0, max_leaf2 = 0;
    for (auto adj_node : adj[node])
    {
        if (adj_node == last) continue;
        dfs(adj_node, node);

        if (dist_to_leaf[adj_node] + 1 > max_leaf1)
        {
            max_leaf2 = max_leaf1;
            max_leaf1 = dist_to_leaf[adj_node] + 1;
        }
        else if (dist_to_leaf[adj_node] + 1 > max_leaf2)
            max_leaf2 = dist_to_leaf[adj_node] + 1;

        // computing dp[node]
        dist_to_leaf[node] = max_leaf1;
        max_length[node]   = max_leaf1 + max_leaf2;
    }

    diameter = max(diameter, max_length[node]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        adj[i].clear();

    // reading input
    int x, y;
    for (int i = 1; i < n; i++)
    {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    // dfs to compute dynamic programming
    dfs(1, 0);

    cout << diameter << endl;
    return 0;
}
