struct LCA {
    vector<vector<int>> G;
    vector<vector<int>> fa;
    vector<int> dep;
    LCA(int n)
    {
        G.resize(n + 1);
        fa.resize(n + 1, vector<int>(31, 0));
        dep.resize(n + 1, 0);
    }

    void work() { dfs(1, 0); }

    void dfs(int u, int f)
    {
        fa[u][0] = f;
        dep[u] = dep[f] + 1;
        for (int i = 1; i < 31; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int v : G[u]) {
            if (v != f) {
                dfs(v, u);
            }
        }
    }

    int lca(int x, int y)
    {
        if (dep[x] < dep[y]) {
            swap(x, y);
        }
        int d = dep[x] - dep[y];
        for (int i = 0; (1 << i) <= d; i++) {
            if ((d >> i) & 1) x = fa[x][i];
        }
        if (x == y) return x;
        for (int i = log2(dep[y]); i >= 0; i--) {
            if (fa[x][i] != fa[y][i]) {
                x = fa[x][i];
                y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    bool isAncester(int x, int y) { return lca(x, y) == x; }

    int dist(int x, int y) { return dep[x] + dep[y] - 2 * dep[lca(x, y)]; }
};