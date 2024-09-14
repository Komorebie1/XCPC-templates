vector<int> centroid;
int sz[N], weight[N];  // weight记录子树大小最大值

void dfs(int u, int fa)
{
    sz[u] = 1, weight[u] = 0;
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        weight[u] = max(weight[u], sz[v]);
    }
    weight[u] = max(n - weight[u], weight[u]);
    if (weight[u] <= n / 2)  // 所有子树大小都不超过n/2
    {
        centroid.push_back(u);
    }
}