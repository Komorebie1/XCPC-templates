#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 10;
int n, m;
int a[N];

struct PresidentTree {
    static constexpr int N = 2e5 + 10;
    int ls[N * 25], rs[N * 25], idx = 0, cnt[N * 25], root[N * 25];

    void modify(int& cur, int past, int x, int l, int r)
    {
        cur = ++idx;
        ls[cur] = ls[past];
        rs[cur] = rs[past];
        cnt[cur] = cnt[past] + 1;
        if (l == r) return;
        int mid = l + r >> 1;
        if (x <= mid)
            modify(ls[cur], ls[past], x, l, mid);
        else
            modify(rs[cur], rs[past], x, mid + 1, r);
    }

    int query(int lx, int rx, int l, int r, double v)  // [l, r] 中第一个出现次数严格大于 v 的数, 不存在则输出-1
    {
        if (l == r) return l - 1;
        int mid = l + r >> 1;
        int res = -1;
        if ((double)(cnt[ls[rx]]) - (double)(cnt[ls[lx]]) > v) res = query(ls[lx], ls[rx], l, mid, v);
        if (res == -1 && (double)(cnt[rs[rx]]) - (double)(cnt[rs[lx]]) > v) res = query(rs[lx], rs[rx], mid + 1, r, v);
        return res;
    }

    int kth(int lx, int rx, int l, int r, int k)  // [l, r] 中第k小的数
    {
        if (l == r) return l - 1;
        int res = cnt[ls[rx]] - cnt[ls[lx]];
        int mid = l + r >> 1;
        if (k <= res)
            return kth(ls[lx], ls[rx], l, mid, k);
        else
            return kth(rs[lx], rs[rx], mid + 1, r, k - res);
    }
} T;

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    vector<int> t;
    for (int i = 1; i <= n; i++) cin >> a[i], t.push_back(a[i]);
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());

    auto find = [&](int x) { return lower_bound(t.begin(), t.end(), x) - t.begin(); };

    for (int i = 1; i <= n; i++) {
        T.modify(T.root[i], T.root[i - 1], find(a[i]) + 1, 1, t.size());
    }

    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << t[T.kth(T.root[l - 1], T.root[r], 1, t.size(), k)] << "\n";
    }
    return 0;
}