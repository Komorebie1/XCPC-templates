int sa[N], rk_base[2][N], *rk = rk_base[0], *rk2 = rk_base[1], sa2[N], cnt[N], height[N];

void get_sa(const char* s, int n)
{
    int m = 122;
    for (int i = 0; i <= m; ++i) cnt[i] = 0;
    for (int i = 1; i <= n; ++i) cnt[rk[i] = s[i]] += 1;
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = 1; i <= n; ++i) sa[cnt[rk[i]]--] = i;
    for (int d = 1; d <= n; d <<= 1)
    {
        // 按第二关键字排序
        int p = 0;
        for (int i = n - d + 1; i <= n; i++) sa2[++p] = i;
        for (int i = 1; i <= n; ++i)
            if (sa[i] > d) sa2[++p] = sa[i] - d;
        // 按第一关键字排序
        for (int i = 0; i <= m; ++i) cnt[i] = 0;
        for (int i = 1; i <= n; ++i) cnt[rk[i]] += 1;
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (int i = n; i; --i) sa[cnt[rk[sa2[i]]]--] = sa2[i];

        rk2[sa[1]] = 1;
        for (int i = 2; i <= n; ++i) rk2[sa[i]] = rk2[sa[i - 1]] + (rk[sa[i]] != rk[sa[i - 1]] || rk[sa[i] + d] != rk[sa[i - 1] + d]);

        std::swap(rk, rk2);

        m = rk[sa[n]];
        if (m == n) break;
    }
}

void get_height()
{
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++)
    {
        if (rk[i] == 1) continue;
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (s[i + k] == s[j + k]) k++;
        height[rk[i]] = k;
    }
}