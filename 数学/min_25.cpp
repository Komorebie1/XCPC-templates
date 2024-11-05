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
            sp2[cnt] = (sp2[cnt - 1] + 1ll * i * i % mod) % mod;
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
        g2[tot] = s2(w[tot]);
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
        }
    }

    cout << (S(n, 0) + 1) % mod << endl;

    return 0;
}