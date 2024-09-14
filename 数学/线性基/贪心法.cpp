int n;
ll a[N];

void insert(ll x)
{
    for (int i = 63; i >= 0; i--) {
        if ((x >> i) & 1) {
            if (a[i])
                x ^= a[i];
            else {
                a[i] = x;
                break;
            }
        }
    }
}