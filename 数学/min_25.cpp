#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define PII pair<int, int>
#define pi acos(-1.0)
constexpr int N = 1e6 + 10;
constexpr int mod = 1e9 + 7;
ll n, sq;
ll primes[N], st[N], cnt, sp1[N], sp2[N];
ll g1[N], g2[N], w[N], tot, id1[N], id2[N];

ll qpow(ll aa, int bb = mod - 2)
{
    ll res = 1;
    while (bb) {
        if (bb & 1) res = (res * aa) % mod;
        aa = (aa * aa) % mod;
        bb >>= 1;
    }
    return res;
}

ll inv2 = qpow(2), inv6 = qpow(6);

void sieve(int n)
{
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[++cnt] = i;
            sp1[cnt] = (sp1[cnt - 1] + i) % mod;
            sp2[cnt] = (sp2[cnt - 1] + 1ll * i * i % mod) % mod;// 质数点值的前缀和
        }
        for (int j = 1; j <= cnt && primes[j] * i < N; j++) {
            st[i * primes[j]] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

ll s1(ll x)
{
    x %= mod;
    return ((x * (x + 1) % mod) * inv2 % mod - 1 + mod) % mod;
}

ll s2(ll x)
{
    x %= mod;
    return (((x * (x + 1) % mod) * (2 * x + 1) % mod) * inv6 % mod - 1 + mod) % mod;
}

ll S(ll i, ll j)
{
    if (primes[j] >= i) return 0;

    ll p = i <= sq ? id1[i] : id2[n / i];

    ll ans = ((g2[p] - g1[p] + mod) % mod - (sp2[j] - sp1[j] + mod) % mod + mod) % mod;
    for (int k = j + 1; k <= cnt && primes[k] * primes[k] <= i; k++) {
        ll pe = primes[k];
        for (int e = 1; pe <= i; e++, pe = pe * primes[k]) {
            ll x = pe % mod;
            ans = (ans + (x * (x - 1) % mod) * ((S(i / pe, k) + (e > 1)) % mod) % mod) % mod;
            // 多项式的点值
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    sq = sqrt(n);
    sieve(sq);
    for (ll l = 1, r; l <= n; l = r + 1) {
        r = min(n, n / (n / l));
        w[++tot] = n / l;
        g1[tot] = s1(w[tot]);
        g2[tot] = s2(w[tot]);// 各单项式的前缀和
        if (w[tot] <= sq) {
            id1[w[tot]] = tot;
        }
        else
            id2[n / w[tot]] = tot;
    }

    for (int j = 1; j <= cnt; j++) {  // g(i, j) 存储的是 [1, w[i]] 中的质数或者最小质因子大于 primes[j] 的数
        for (int i = 1; i <= tot && primes[j] * primes[j] <= w[i]; i++) {
            ll tmp = w[i] / primes[j];
            ll p = tmp <= sq ? id1[tmp] : id2[n / tmp];
            g1[i] = (g1[i] - primes[j] * (g1[p] - sp1[j - 1] + mod) % mod + mod) % mod;
            g2[i] = (g2[i] - (primes[j] * primes[j] % mod) * (g2[p] - sp2[j - 1] + mod) % mod + mod) % mod;
            // 质数的幂的点值
        }
    }

    cout << (S(n, 0) + 1) % mod << endl;

    return 0;
}


//------------------ooo-----------------//

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define PII pair<int, int>
#define pi acos(-1.0)
constexpr int N = 1e6 + 10;
constexpr int mod = 1e9 + 7;

ll qpow(ll aa, int bb)
{
    ll res = 1;
    while (bb) {
        if (bb & 1) res = (res * aa) % mod;
        aa = (aa * aa) % mod;
        bb >>= 1;
    }
    return res;
}

ll inv2 = qpow(2, mod - 2), inv6 = qpow(6, mod - 2);

struct min_25 {
    int B, cnt, tot;
    ll n, sq;
    vector<ll> w, id1, id2, primes;
    vector<bool> st;
    vector<vector<ll>> g, sum;
    vector<ll> coef;
    vector<function<ll(ll)>> f;
    vector<function<ll(ll)>> pre;
    min_25(ll _n, vector<ll> _coef, vector<function<ll(ll)>> _f, vector<function<ll(ll)>> _pre) : n(_n)
    {
        B = _coef.size();
        cnt = tot = 0;
        coef = _coef, f = _f, pre = _pre;
        sq = sqrt(n);
        w.resize(2 * sq + 10, 0), id1.resize(sq + 10, 0), id2.resize(sq + 10, 0), primes.resize(sq + 10, 0);
        st.resize(sq + 10, false);
        g.resize(2 * sq + 10, vector<ll>(B)), sum.resize(sq + 10, vector<ll>(B));
        sieve(sq);
        get_w();
        get_g();
    }

    ll at(ll x)  // 点值
    {
        ll res = 0;
        for (int i = 0; i < B; i++) {
            res = (res + f[i](x) * coef[i] % mod + mod) % mod;
        }
        return res;
    }

    void sieve(int _n)
    {
        for (int i = 2; i <= _n; i++) {
            if (!st[i]) {
                primes[++cnt] = i;
                for (int j = 0; j < B; j++) {
                    sum[cnt][j] = (sum[cnt - 1][j] + f[j](i)) % mod;
                }
            }
            for (int j = 1; j <= cnt && i * primes[j] <= _n; j++) {
                st[i * primes[j]] = true;
                if (i % primes[j] == 0) break;
            }
        }
    }

    void get_w()
    {
        for (ll l = 1, r; l <= n; l = r + 1) {
            r = min(n, n / (n / l));
            w[++tot] = n / l;
            ll x = w[tot] % mod;
            for (int i = 0; i < B; i++) {
                g[tot][i] = pre[i](x);
            }
            if (w[tot] <= sq)
                id1[w[tot]] = tot;
            else
                id2[n / w[tot]] = tot;
        }
    }

    void get_g()
    {
        for (int j = 1; j <= cnt; j++) {
            for (int i = 1; i <= tot && primes[j] * primes[j] <= w[i]; i++) {
                ll tmp = w[i] / primes[j];
                int p = tmp <= sq ? id1[tmp] : id2[n / tmp];
                for (int k = 0; k < B; k++) {
                    g[i][k] = (g[i][k] - (f[k](primes[j]) % mod) * (g[p][k] - sum[j - 1][k] + mod) % mod + mod) % mod;
                }
            }
        }
    }

    ll S(ll i, ll j)
    {
        if (i <= primes[j]) return 0;
        ll p = i <= sq ? id1[i] : id2[n / i];
        ll ans = 0;
        for (int k = 0; k < B; k++) {
            ans = (ans + g[p][k] * coef[k] % mod - sum[j][k] * coef[k] % mod + mod) % mod;
        }
        for (int k = j + 1; k <= cnt && primes[k] * primes[k] <= i; k++) {
            ll pe = primes[k];
            for (int e = 1; pe <= i; e++, pe *= primes[k]) {
                ll x = pe % mod;
                ans = (ans + at(x) * (S(i / pe, k) + (e > 1)) % mod) % mod;
            }
        }
        return ans;
    }
};

ll f1(ll x) { return x; }
ll f2(ll x) { return x * x % mod; };
ll s1(ll x)
{
    x %= mod;
    return ((x * (x + 1) % mod) * inv2 % mod - 1 + mod) % mod;
}
ll s2(ll x)
{
    x %= mod;
    return (((x * (x + 1) % mod) * (2 * x + 1) % mod) * inv6 % mod - 1 + mod) % mod;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    ll n;
    cin >> n;
    vector<function<ll(ll)>> f = {f2, f1};
    vector<function<ll(ll)>> pre = {s2, s1};
    vector<ll> coef = {1, -1};
    min_25 T(n, coef, f, pre);
    cout << (T.S(n, 0) + 1) % mod << endl;
    return 0;
}