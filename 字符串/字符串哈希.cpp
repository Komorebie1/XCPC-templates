template <ll mod> struct Hash {
    const int B = 13331;
    int n;
    vector<ll> h, p;
    Hash(string s)  // 传入时下标从 0 开始
    {
        n = s.size();
        h.resize(n + 1), p.resize(n + 1);
        p[0] = 1;
        for (int i = 1; i <= n; i++) {
            h[i] = ((__int128)h[i - 1] * B + s[i - 1]) % mod;
            p[i] = (__int128)p[i - 1] * B % mod;
        }
    }
    ll get(int l, int r) { return (h[r] - (__int128)h[l - 1] * p[r - l + 1] % mod + mod) % mod; }
};