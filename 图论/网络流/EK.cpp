memset(h, -1, sizeof(h));  // 将h初始化为-1，因为边的标号从0开始。

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx++;
}

bool bfs()
{
    queue<int> q;
    memset(st, false, sizeof(st));
    q.push(S);
    st[S] = true;
    d[S] = inf;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (!st[v] && f[i]) {
                st[v] = true;
                d[v] = min(d[u], f[i]);
                pre[v] = i;
                if (v == T) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int EK()
{
    int r = 0;
    while (bfs()) {
        r += d[T];
        for (int i = T; i != S; i = e[pre[i ^ 1]]) {
            f[pre[i]] -= d[T];
            f[pre[i ^ 1]] += d[T];
        }
    }
    return r;
}

struct EK {
    const int n, S, T;
    vector<int> h, e, ne, cur, f, d, pre, st;

    EK(int n, int S, int T) : n(n), S(S), T(T)  // 点数，源点，汇点
    {
        h.resize(n + 1, -1);
        d.resize(n + 1);
        cur.resize(n + 1);
        pre.resize(n + 1);
        st.resize(n + 1);
    }

    void addedge(int a, int b, int c)
    {
        e.push_back(b), ne.push_back(h[a]), f.push_back(c), h[a] = e.size() - 1;
        e.push_back(a), ne.push_back(h[b]), f.push_back(0), h[b] = e.size() - 1;
    }

    bool bfs()
    {
        queue<int> q;
        st.assign(n + 1, false);
        q.push(S);
        st[S] = true;
        d[S] = 0x3f3f3f3f;
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i = h[u]; i != -1; i = ne[i]) {
                int v = e[i];
                if (!st[v] && f[i]) {
                    st[v] = true;
                    d[v] = min(d[u], f[i]);
                    pre[v] = i;
                    if (v == T) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }

    int maxflow()
    {
        int r = 0;
        while (bfs()) {
            r += d[T];
            for (int i = T; i != S; i = e[pre[i ^ 1]]) {
                f[pre[i]] -= d[T];
                f[pre[i ^ 1]] += d[T];
            }
        }
        return r;
    }
};