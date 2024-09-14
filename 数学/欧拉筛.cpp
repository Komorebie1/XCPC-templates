vector<ll> primes;  // primes[]存储所有素数

void get_primes(int n)
{
    vector<bool> st(n + 1);  // st[x]存储x是否被筛掉
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes.push_back(i);
        for (int j = 0; j < primes.size() && primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}