struct query {
    int l, r, pos, id;
    bool operator<(query a)
    {
        if (a.pos == this->pos) return a.pos & 1 ? this->r < a.r : this->r > a.r; // 右端点奇偶波浪排序
        return this->pos < a.pos;
    }
} q[N];

int len = sqrt(n);
for (int i = 1; i <= m; i++)
{
    cin >> q[i].l >> q[i].r;
    q[i].id = i;
    q[i].pos = q[i].l / len;
}
sort(q + 1, q + 1 + m, cmp1);
for (int i = 1, l = 1, r = 0; i <= m; i++)
{
    while (l > q[i].l) add(--l);
    while (r < q[i].r) add(++r);
    while (l < q[i].l) sub(l++);
    while (r > q[i].r) sub(r--);
    ans[q[i].id] = res;
}