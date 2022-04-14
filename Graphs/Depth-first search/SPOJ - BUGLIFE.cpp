//============================================================================
// Name        : SPOJ - Bug Life
// Author      : Rubén Alcolea Núñez
// Version     : Qt 5.8
// Description : Depth First Search + Bi-coloring graph
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

#define endl "\n"

const int MAXN = 2005;

int n, m, scenarios = 1;
vector<int> adj[MAXN];
int colors[MAXN], casos;

bool color(int node, int curr_color, int next_color)
{
    colors[node] = curr_color;

    bool flag = true;
    for (auto adj_node : adj[node])
    {
        if (colors[adj_node] == next_color) continue;

        if (colors[adj_node == curr_color])
            return false;

        flag &= color(adj_node, next_color, curr_color);
    }

    return flag;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> casos;
    while (casos--)
    {
        cin >> n >> m;

        // initialization
        for (int i = 1; i <= n; i++)
        {
            colors[i] = 0;
            adj[i].clear();
        }

        // reading input
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        bool suspicious = true;
        for (int i = 1; i <= n; i++)
        {
            if (colors[i] == 0)
                suspicious &= color(i, 1, 2);

            if (suspicious == false)
                break;
        }

        cout << "Scenario #" << scenarios++ << ":\n";
        if (suspicious)
            cout << "No suspicious bugs found!" << endl;
        else
            cout << "Suspicious bugs found!" << endl;
    }
    return 0;
}
