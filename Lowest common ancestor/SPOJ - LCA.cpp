    //==================================================================================
    // Contest     : SPOJ Online Judge
    // Problem     : LCA - Lowest Common Ancestor
    // Author      : Rubén Alcolea Núñez
    // Description : Lowest common ancestor with binary lifting
    //==================================================================================
     
    #include <bits/stdc++.h>
    using namespace std;
     
    #define MAX 1005
    #define MAXLOG 1005
     
    int casos, a, b, n, m, l;
    vector<int> adj[MAX];
    int up[MAX][MAXLOG];
    int parent[MAX];
     
    int timer, testsNumber = 1, queries;
    int tin[MAX], tout[MAX];
     
    void dfs(int v, int p)
    {
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; ++i)
            up[v][i] = up[up[v][i-1]][i-1];
     
        for (int u : adj[v]) {
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
     
    void preprocess(int root) {
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
     
        cin >> casos;
        while (casos--)
        {
            cin >> n;
            for (int i = 1; i <= n; i++)
            {
                adj[i].clear();
                parent[i] = 0;
                tin[i] = tout[i] = 0;
                cin >> m;
                for (int j = 1; j <= m; j++)
                {
                    cin >> a;
                    parent[a] = i;
                    adj[i].push_back(a);
                }
            }
            preprocess(1);
            cin >> queries;
            cout << "Case " << testsNumber++ << ":\n";
            while (queries--)
            {
                cin >> a >> b;
                cout << lca(a, b) << "\n";
            }
        }
        return 0;
    }