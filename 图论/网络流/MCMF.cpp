struct MCMF {
    vector<long long> ne, h, e, f, w, dis, incf, vis, pre;
    int idx, n, S, T;
    MCMF(int n, int m, int s, int t)  // 点数，边数
    {
        this->S = s, this->T = t, this->n = n, this->idx = 0;
        ne.resize(m, 0);
        e.resize(m, 0);
        f.resize(m, 0);
        w.resize(m, 0);
        pre.resize(m, 0);
        vis.resize(n + 1, 0);
        h.resize(n + 1, -1);
    };

    void addedge(int a, int b, int c, int d)
    {
        int& idx = this->idx;
        ne[idx] = h[a], e[idx] = b, f[idx] = c, w[idx] = d, h[a] = idx++;
        ne[idx] = h[b], e[idx] = a, f[idx] = 0, w[idx] = -d, h[b] = idx++;
    }

    bool spfa()
    {
        queue<int> q;
        dis.assign(n + 1, 0x3f3f3f3f);
        incf.assign(n + 1, 0);
        q.push(S);
        dis[S] = 0, incf[S] = 0x3f3f3f3f;
        while (q.size()) {
            int u = q.front();
            q.pop(), vis[u] = 0;
            for (int i = h[u]; ~i; i = ne[i]) {
                int v = e[i];
                if (f[i] && dis[v] > dis[u] + w[i]) {
                    dis[v] = dis[u] + w[i];
                    pre[v] = i;
                    incf[v] = min(f[i], incf[u]);
                    if (vis[v] == 0) {
                        q.push(v), vis[v] = 1;
                        
                    }
                }
            }
        }
        return incf[T] > 0;
    }

    pair<long long, long long> EK()
    {
        long long flow = 0, cost = 0;
        while (spfa()) {
            int t = incf[T];
            flow += t, cost += t * dis[T];
            for (int i = T; i != S; i = e[pre[i] ^ 1]) {
                f[pre[i]] -= t;
                f[pre[i] ^ 1] += t;
            }
        }
        return make_pair(flow, cost);
    }
};