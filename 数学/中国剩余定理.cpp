ll CRT(int n, ll a[], ll b[])  // a为模数，b为余数
{
    ll ans = 0;
    ll s = 1;
    for (int i = 1; i <= n; i++) {
        s *= a[i];
    }
    for (int i = 1; i <= n; i++) {
        ll m = s / a[i];
        ll x, y;
        exgcd(m, a[i], x, y);                      // x为m在模a[i]下的逆元
        ans = (ans + (m * x * b[i]) % s + s) % s;  // m*x不要对a[i]取模
    }
    return ans;
}