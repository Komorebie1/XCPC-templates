int d[N], a[N], st[N];
vector<int>primes;
void sieve(int n)
{
    st[1] = d[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes.push_back(i), d[i] = 2, a[i] = 1;
        for (int j = 1; j < primes.size() && i * primes[j] <= n; j++) {
            st[i * primes[j]] = 1;
            if (i % primes[j])
                d[i * primes[j]] = d[i] * d[primes[j]], a[i * primes[j]] = 1;
            else {
                d[i * primes[j]] = d[i] / (a[i] + 1) * (a[i] + 2);
                a[i * primes[j]] = a[i] + 1;
                break;
            }
        }
    }
}