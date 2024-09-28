unordered_map<ll, ll> mp;

ll s(ll n)
{
    if (n < N) return mu[n];  // 注意这里的 mu 数组存的是莫比乌斯函数的前缀和
    if (mp[n]) return mp[n];
    ll ans = 1;
    for (ll l = 2, r; l <= n; l = r + 1) {
        r = min(n, n / (n / l));
        ans -= s(n / l) * (r - l + 1);
    }
    mp[n] = ans;
    return mp[n];
}