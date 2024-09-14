struct DSU {
    vector<int> p, sz, d;
    DSU(int n)
    {
        p.resize(n + 1);
        sz.resize(n + 1, 1);
        d.resize(n + 1, 0);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x)
    {
        if (p[x] != x) {
            int u = find(p[x]);
            d[x] += d[p[x]];
            p[x] = u;
        }
        return p[x];
    }

    bool same(int a, int b) { return find(a) == find(b); }

    void merge(int a, int b)
    {
        p[find(a)] = find(b);
        sz[b] += sz[a];
    }

    void merge(int a, int b, int dis)
    {
        p[find(a)] = find(b);
        sz[b] += sz[a];
        d[find(a)] = dis;  // 根据具体问题，初始化find(a)的偏移量
    }

    int get_sz(int a) { return sz[find(a)]; }
};