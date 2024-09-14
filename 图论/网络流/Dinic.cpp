struct Dinic {
    const int n, S, T;
    vector<int> h, e, ne, cur, f, d;

    Dinic(int n, int S, int T) : n(n), S(S), T(T)  // 点数，源点，汇点
    {
        h.resize(n + 1, -1);
        d.resize(n + 1);
        cur.resize(n + 1);
    }

    void addedge(int a, int b, int c)
    {
        e.push_back(b), ne.push_back(h[a]), f.push_back(c), h[a] = e.size() - 1;
        e.push_back(a), ne.push_back(h[b]), f.push_back(0), h[b] = e.size() - 1;
    }

    bool bfs()
    {
        d.assign(n + 1, -1);
        queue<int> q;
        q.push(S);
        d[S] = 0;
        cur[S] = h[S];
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i = h[u]; ~i; i = ne[i]) {
                int v = e[i];
                if (d[v] == -1 && f[i] > 0) {
                    d[v] = d[u] + 1;
                    cur[v] = h[v];
                    if (v == T) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }

    int find(int u, int limit)
    {
        if (u == T) return limit;
        int flow = 0;
        for (int i = cur[u]; ~i; i = ne[i]) {
            cur[u] = i;
            int v = e[i];
            if (d[v] == d[u] + 1 && f[i]) {
                int t = find(v, min(limit - flow, f[i]));
                if (!t) d[v] = -1;  // important!!!!!!!!!!!!!!!!!!!!!!!!!!
                f[i] -= t, f[i ^ 1] += t;
                flow += t;
            }
        }
        return flow;
    }

    int dinic()
    {
        int r = 0, flow;
        while (bfs()) {
            while (flow = find(S, 0x3f3f3f3f)) {
                r += flow;
            }
        }
        return r;
    }
};