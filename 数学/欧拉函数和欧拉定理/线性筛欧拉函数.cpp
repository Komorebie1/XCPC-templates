int phi[N], st[N];
vector<int>primes;
void sieve(int n)
{
    st[1] = phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes.push_back(i), phi[i] = i - 1;
        for (int j = 1; j < primes.size() && i * primes[j] <= n; j++) {
            st[i * primes[j]] = 1;
            if (i % primes[j])
                phi[i * primes[j]] = phi[i] * phi[primes[j]];
            else {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
        }
    }
}