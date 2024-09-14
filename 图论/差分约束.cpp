#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, m;
int h[N], e[N], ne[N], we[N], idx;
int dis[N], cnt[N], vis[N];

struct node {
    int v, w;
};

vector<node> G[N];

void add(int u, int v, int w) { ne[++idx] = h[u], h[u] = idx, e[idx] = v, we[idx] = w; }

bool spfa(int num, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    vis[s] = 1;
    queue<int> q;
    q.push(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto it : G[u]) {
            int v = it.v, w = it.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;  // 记录经过了多少点
                if (cnt[v] > num)     // 存在负环
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c == '>') {
                G[i].push_back({n + j, -1});
            }
            else if (c == '<') {
                G[n + j].push_back({i, -1});
            }
            else {
                G[i].push_back({n + j, 0});
                G[n + j].push_back({i, 0});
            }
        }
    }
    for (int i = 1; i <= n + m; i++) {
        G[0].push_back({i, 0});
    }
    if (spfa(n + m + 1, 0)) {
        cout << "Yes" << endl;
        int minn = 0x3f3f3f3f, d = 0;
        for (int i = 1; i <= n + m; i++) {
            minn = min(minn, dis[i]);
        }
        if (minn <= 0) {
            d = -minn + 1;
        }
        for (int i = 1; i <= n; i++) {
            cout << dis[i] + d << " \n"[i == n];
        }
        cout << dis[n] + d << endl;
        for (int i = 1; i <= m; i++) {
            cout << dis[n + i] + d << " \n"[i == m];
        }
        cout << dis[n + m] + d;
    }
    else
        cout << "No";
    return 0;
}