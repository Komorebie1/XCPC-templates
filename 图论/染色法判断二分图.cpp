int n;         // n表示点数
int color[N];  // 表示每个点的颜色，-1表示为染色，0表示白色，1表示黑色

// 参数：u表示当前节点，c表示当前点的颜色
bool dfs(int u, int c)
{
    color[u] = c;
    for (int v : G[u]) {
        if (color[v] == -1) {
            if (!dfs(v, !c)) return false;
        }
        else if (color[v] == c)
            return false;
    }

    return true;
}

bool check()
{
    memset(color, -1, sizeof color);
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (color[i] == -1)
            if (!dfs(i, 0)) {
                flag = false;
                break;
            }
    return flag;
}