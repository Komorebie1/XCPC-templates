int dfn[N], low[N], tim, vis[N], flag[N];
int ans;
vector<int> G[N];

void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++tim;
    vis[u] = 1;
    int children = 0;
    for (int v : G[u]) {
        if (!vis[v]) {
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (u != fa && low[v] >= dfn[u] && !flag[u]) {
                flag[u] = 1;
                ans++;
            }
        }
        else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (u == fa && children >= 2 && !flag[u]) {
        flag[u] = 1;
        ans++;
    }
}