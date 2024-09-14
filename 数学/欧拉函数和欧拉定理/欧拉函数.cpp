int phi(int n)  // 求解 phi(n)
{
    int ans = n;
    for (int i = 2; i <= n / i; i++) {  // 注意，这里要写 n / i ，以防止 int 型溢出风险和 sqrt 超时风险
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ans = ans / n * (n - 1);  // 特判 n 为质数的情况
    return ans;
}