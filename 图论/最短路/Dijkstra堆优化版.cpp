int dist[N];        // 存储所有点到1号点的距离
bool st[N];     // 存储每个点的最短距离是否已确定
// 求1号点到n号点的最短距离，如果不存在，则返回-1
int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});  // first存储距离，second存储节点编号
    while (heap.size())
    {
        auto [d, u] = heap.top();
        heap.pop();
        if (st[u]) continue;
        st[u] = true;

        for (auto [v, w] : G[u])
        {
            if (dist[v] > distance + w)
            {
                dist[v] = distance + w;
                heap.push({dist[v], v});
            }
        }
    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}