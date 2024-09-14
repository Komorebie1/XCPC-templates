int mu[N], st[N];
vector<int>primes;
void sieve(int n)
{
    st[1] = mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes.push_back(i), mu[i] = -1;
        for (int j = 1; j < primes.size() && i * primes[j] <= n; j++) {
            st[i * primes[j]] = 1;
            if (i % primes[j])
                mu[i * primes[j]] = -mu[i];
            else {
                mu[i * primes[j]] = 0;
                break;
            }
        }
    }
}