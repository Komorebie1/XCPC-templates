struct Seg_tree {
    struct node {
        int l, r;
        ll sum, add;
    };
    vector<node> tr;
    vector<int> a;
    Seg_tree(int n)
    {
        tr.resize((n << 2) + 1);
        a.resize(n + 1);
        build(1, 1, n);
    }
    Seg_tree(vector<int> nums)
    {
        int n = nums.size() - 1;
        a.assign(nums.begin(), nums.end());
        tr.resize((n << 2) + 1);
        build(1, 1, n);
    }

    void pushup(int u) { tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum; }

    void pushdown(int u)
    {
        auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
        if (root.add) {
            left.add += root.add, right.add += root.add;
            left.sum += (left.r - left.l + 1) * root.add, right.sum += (right.r - right.l + 1) * root.add;
            root.add = 0;
        }
    }

    void build(int u, int l, int r)
    {
        if (l == r)
            tr[u] = {l, r, a[l], 0};
        else {
            tr[u] = {l, r};
            int mid = l + r >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            pushup(u);
        }
    }

    void modify(int u, int l, int r, ll v)
    {
        if (tr[u].l >= l && tr[u].r <= r) {
            tr[u].sum += 1ll * (tr[u].r - tr[u].l + 1) * v;
            tr[u].add += v;
        }
        else {
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            if (l <= mid) modify(u << 1, l, r, v);
            if (r > mid) modify(u << 1 | 1, l, r, v);
            pushup(u);
        }
    }

    ll query(int u, int l, int r)
    {
        if (tr[u].l >= l && tr[u].r <= r)
            return tr[u].sum;
        else {
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            ll sum = 0;
            if (l <= mid) sum += query(u << 1, l, r);
            if (r > mid) sum += query(u << 1 | 1, l, r);
            return sum;
        }
    }
};