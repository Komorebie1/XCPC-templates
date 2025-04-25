stack<int> st;
int in_stack[N];

void tarjan(int u)
{
    low[u] = dfn[u] = ++idx;
    st.push(u);
    in_stack[u] = 1;
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        // 栈中 u 及其上方的结点构成一个 SCC
        ++sc;
        while (st.top() != u) {
            scc[st.top()] = sc;
            in_stack[st.top()] = 0;
            st.pop();
            sz[sc]++;
        }
        scc[st.top()] = sc;
        in_stack[st.top()] = 0;
        st.pop();
        sz[sc]++;
    }
}