ll BSGS(ll x, ll y, ll mod)  // y是x的多少次方（模意义下）
{
    x %= mod, y %= mod;
    if (x == 0) return y == 0 ? 1 : -1;
    if (y == 1) return 0;
    ll m = ceil(sqrt(mod));
    ll t = y;
    unordered_map<ll, ll> mp;
    mp[y] = 0;
    for (int i = 1; i < m; i++) {
        t = (t * x) % mod;
        mp[t] = i;
    }
    ll res = 1;
    t = 1;
    for (int i = 1; i <= m; i++) res = (res * x) % mod;
    for (int i = 1; i <= m; i++) {
        t = (res * t) % mod;
        if (mp.count(t)) {
            return (m * i - mp[t]) % mod;
        }
    }
    return -1;
}