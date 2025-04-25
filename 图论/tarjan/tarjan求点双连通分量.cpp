vector<int> G[N];  // 原图
vector<int> T[N];  // 新图（圆方树）
void tarjan(int u, int fa)
{
    int son = 0;
    dfn[u] = low[u] = ++tim;
    st.push(u);
    for (int v : G[u]) {
        if (!dfn[v]) {
            son++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                scc++;
                while (st.top() != v) {
                    ans[scc].push_back(st.top());
                    T[scc].push_back(st.top()); // 将当前联通分量中的点连到 scc 对应的方点上
                    T[st.top()].push_back(scc);
                    st.pop();
                }
                ans[scc].push_back(st.top());
                T[scc].push_back(st.top());
                T[st.top()].push_back(scc);
                st.pop();
                ans[scc].push_back(u);
                T[scc].push_back(u);
                T[u].push_back(scc);
            }
        }
        else if (v != fa)  // 返祖边
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (fa == 0 && son == 0) ans[++scc].push_back(u);  // 特判孤立点
}