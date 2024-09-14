int n1, n2;        // n1表示第一个集合中的点数，n2表示第二个集合中的点数
vector<int> G[N];  // 匈牙利算法中只会用到从第二个集合指向第一个集合的边，所以这里只用存一个方向的边
int match[N];      // 存储第二个集合中的每个点当前匹配的第一个集合中的点是哪个
bool st[N];        // 表示第二个集合中的每个点是否已经被遍历过

bool find(int u)
{
    for (int v : G[u]) {
        if (!st[v]) {
            st[v] = true;
            if (match[v] == 0 || find(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int res = 0;
for (int i = 1; i <= n1; i++)  // 求最大匹配数，依次枚举第一个集合中的每个点能否匹配第二个集合中的点
{
    memset(st, false, sizeof st);
    if (find(i)) res++;
}