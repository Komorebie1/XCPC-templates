void dfs(int u, int fa)  // 树形dp法 一个数组实现 存的是到子树中的最长路径
{
    for (int v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        diameter = max(diameter, d1[u] + d1[v] + 1);
        d1[u] = max(d1[u], d1[v] + 1);
    }
}