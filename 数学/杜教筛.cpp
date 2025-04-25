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

/* 以下是 luguo P4213 【模板】杜教筛 完整的代码
给定一个正整数，求
$$ans_1=\sum_{i=1}^n\varphi(i)$$
$$ans_2=\sum_{i=1}^n \mu(i)$$
*/

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define PII pair<int, int>
#define pi acos(-1.0)
const int N = 2e6 + 10;
vector<ll> primes;
ll mu[N], phi[N], st[N];

unordered_map<ll, ll> mp1, mp2;

void sieve()
{
    phi[1] = mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!st[i]) primes.push_back(i), mu[i] = -1, phi[i] = i - 1;
        for (int p : primes) {
            if (i * p >= N) break;
            st[i * p] = true;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            mu[i * p] = -mu[i];
            phi[i * p] = phi[i] * phi[p];
        }
    }
    for (int i = 1; i < N; i++) mu[i] += mu[i - 1], phi[i] += phi[i - 1];
}

ll s1(ll n)
{
    if (n < N) return phi[n];
    if (mp1[n]) return mp1[n];
    ll ans = 1ll * n * (n + 1) / 2;
    for (ll l = 2, r; l <= n; l = r + 1) {
        r = min(n, n / (n / l));
        ans -= s1(n / l) * (r - l + 1);
    }
    mp1[n] = ans;
    return mp1[n];
}

ll s2(ll n)
{
    if (n < N) return mu[n];
    if (mp2[n]) return mp2[n];
    ll ans = 1;
    for (ll l = 2, r; l <= n; l = r + 1) {
        r = min(n, n / (n / l));
        ans -= s2(n / l) * (r - l + 1);
    }
    mp2[n] = ans;
    return mp2[n];
}

void solve()
{
    ll n;
    cin >> n;
    cout << s1(n) << " " << s2(n) << endl;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int tt;
    cin >> tt;
    sieve();
    while (tt--) {
        solve();
    }
    return 0;
}