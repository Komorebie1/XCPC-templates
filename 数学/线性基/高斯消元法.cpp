int n, k;
ll a[N];

void gauss()
{
    for (int i = 63; i >= 0; i--) {
        for (int j = k; j < n; j++) {
            if (a[i] >> i & 1) {
                swap(a[i], a[k]);
                break;
            }
        }
        if ((a[k] >> i & 1) == 0) continue;
        for (int j = 0; j < n; j++) {
            if (j != k && (a[j] >> i & 1)) a[j] ^= a[k];
        }
        k++;
        if (k == n) break;
    }
}