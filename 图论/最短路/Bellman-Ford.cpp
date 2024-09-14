struct EDGE  // for bellman-ford
{
    int u, int v, int w;
};

vector<EDGE> edges;

bool Bellman_ford(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    bool flag;
    for (int i = 1; i <= n; i++) {
        flag = false;
        for (auto [u, v, w] : edges) {
            if (dis[u] == 0x3f3f3f3f) continue;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                flag = true;
            }
        }
        if (!flag) break;
    }
    return flag;  // 第n轮循环仍可以松弛说明存在负环
}