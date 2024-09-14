void dfs(int u, int f)  // 与重链剖分相同的写法找重儿子
{
    siz[u] = 1;
    for (int i = Head[u]; ~i; i = Edge[i].next) {
        int v = Edge[i].to;
        if (v == f) continue;
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
int col[maxn], cnt[maxn];  // col存放某结点的颜色，cnt存放某颜色在“当前”子树中的数量
long long ans[maxn], sum;  // ans是答案数组，sum用于累加计算出“当前”子树的答案
int flag, maxc;            // flag用于标记重儿子，maxc用于更新最大值
// TODO 统计某结点及其所有轻儿子的贡献
void count(int u, int f, int val)
{
    cnt[col[u]] += val;      // val为正为负可以控制是增加贡献还是删除贡献
    if (cnt[col[u]] > maxc)  // 找最大值，基操吧
    {
        maxc = cnt[col[u]];
        sum = col[u];
    }
    else if (cnt[col[u]] == maxc)  // 这样做是因为如果两个颜色数量相同那都得算
        sum += col[u];
    for (int i = Head[u]; ~i; i = Edge[i].next)  // 排除被标记的重儿子，统计其它儿子子树信息
    {
        int v = Edge[i].to;
        if (v == f || v == flag) continue;  // 不能写if(v==f||v==son[u]) continue;
        count(v, u, val);
    }
}
// dsu on tree的板子
void dfs(int u, int f, bool keep)
{
    // 第一步：搞轻儿子及其子树算其答案删贡献
    for (int i = Head[u]; ~i; i = Edge[i].next) {
        int v = Edge[i].to;
        if (v == f || v == son[u]) continue;
        dfs(v, u, false);
    }
    // 第二步：搞重儿子及其子树算其答案不删贡献
    if (son[u]) {
        dfs(son[u], u, true);
        flag = son[u];
    }
    // 第三步：暴力统计u及其所有轻儿子的贡献合并到刚算出的重儿子信息里
    count(u, f, 1);
    flag = 0;
    ans[u] = sum;
    // 把需要删除贡献的删一删
    if (!keep) {
        count(u, f, -1);
        sum = maxc = 0;  // 这是因为count函数中会改变这两个变量值
    }
}
/********************** 另一种写法 **********************/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define PII pair<int, int>
#define pi acos(-1.0)
const int N = 1e5 + 10;
int n;
int a[N];
ll ans = 0;
vector<int> G[N];
vector<int> path;
int son[N], sz[N];
int cnt[22][2][(int)1e6 + 10];
int lca;

void dfs(int u, int fa)
{
    sz[u] = 1;
    for (int v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void calc(int u, int fa)
{
    path.push_back(u);
    if ((a[u] ^ lca) < (int)1e6 + 10)
        for (int j = 0; j <= 20; j++) ans += 1ll * cnt[j][((u >> j) & 1) ^ 1][a[u] ^ lca] * (1 << j);
    for (int v : G[u]) {
        if (v == fa) continue;
        calc(v, u);
    }
}

void insert(int u, int fa)
{
    for (int j = 0; j <= 20; j++) cnt[j][(u >> j) & 1][a[u]]++;
    for (int v : G[u]) {
        if (v == fa) continue;
        insert(v, u);
    }
}

void del(int u, int fa)
{
    for (int j = 0; j <= 20; j++) cnt[j][(u >> j) & 1][a[u]]--;
    for (int v : G[u]) {
        if (v == fa) continue;
        del(v, u);
    }
}

void dfs(int u, int fa, bool keep)
{
    for (int v : G[u]) {
        if (v == fa || v == son[u]) continue;
        dfs(v, u, false);
    }
    if (son[u]) {
        dfs(son[u], u, true);
    }
    lca = a[u];
    for (int v : G[u]) {
        if (v == fa || v == son[u]) continue;
        calc(v, u);
        for (auto vv : path)
            for (int j = 0; j <= 20; j++) cnt[j][(vv >> j) & 1][a[vv]]++;
        path.clear();
    }
    for (int j = 0; j <= 20; j++) cnt[j][(u >> j) & 1][a[u]]++;
    if (!keep) {
        del(u, fa);
    }
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(nullptr);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 0);
    dfs(1, 0, true);
    printf("%lld\n", ans);
    return 0;
}