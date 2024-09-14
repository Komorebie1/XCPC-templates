int low[N], sum[N], sigma[N], st[N];
vector<int> primes;
void sieve(int n)
{
    st[1] = low[1] = sum[1] = sigma[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes.push_back(i), low[i] = i, sum[i] = sigma[i] = i + 1;
        for (int j = 1; j < primes.size() && i * primes[j] <= n; j++) {
            st[i * primes[j]] = 1;
            if (i % primes[j] == 0) {
                low[i * primes[j]] = low[i] * primes[j];
                sum[i * primes[j]] = sum[i] + low[i * primes[j]];
                sigma[i * primes[j]] = sigma[i] / sum[i] * sum[i * primes[j]];
                break;
            }
            low[i * primes[j]] = primes[j];
            sum[i * primes[j]] = primes[j] + 1;
            sigma[i * primes[j]] = sigma[i] * sigma[primes[j]];
        }
    }
}