int vis[N], cnt[N];
vector<PII> G[N];

bool spfa(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    queue<int> q;
    while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w] : G[u]) {
            if (dis[v] >= dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;  // 记录经过了多少点
                if (cnt[v] >= n)      // 存在负环
                    return false;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return true;
}