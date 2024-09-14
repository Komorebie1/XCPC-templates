void exgcd(ll a, ll b, ll& x, ll& y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    ll tmp = x;
    x = y;
    y = tmp - a / b * y;
}
ll getinv(int a, int mod)  // 求a在mod下的逆元，不存在逆元返回-1
{
    ll x, y, d = exgcd(a, mod, x, y);
    return d == 1 ? (x % mod + mod) % mod : -1;
}