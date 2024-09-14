std::cin >> n >> p;
for (int i = 1; i <= n; i++) {  // 读入增广矩阵
    for (int j = 1; j <= n + 1; j++) {
        std::cin >> a[i][j];
        a[i][j] %= p;
    }
}
int cnt = 1;
for (int i = 1; i <= n; i++) {
    int r = cnt;
    for (int j = cnt; j <= n; j++) {
        if (abs(a[j][i]) > abs(a[r][i])) {
            r = j;
        }
    }
    if (a[r][i] == 0) continue;
    if (r != cnt) std::swap(a[cnt], a[r]);
    ll inv = qpow(a[cnt][i], p - 2);
    for (int j = n + 1; j >= i; j--) {
        a[cnt][j] = (a[cnt][j] * inv) % p;
    }
    for (int j = cnt + 1; j <= n; j++) {
        if (a[j][i]) {
            for (int k = n + 1; k >= i; k--) {
                a[j][k] = (a[j][k] - (a[j][i] * a[cnt][k]) % p + p) % p;
            }
        }
    }
    cnt++;
}
if (cnt < n + 1) {
    for (int i = cnt; i <= n; i++) {
        if (a[i][n + 1]) {
            std::cout << -1 << "\n";  // 无解
            return 0;
        }
    }
    std::cout << 0 << "\n";  // 多解
    return 0;
}
for (int i = n; i >= 1; i--) {
    for (int j = i + 1; j <= n; j++) {
        a[i][n + 1] = (a[i][n + 1] - (a[i][j] * a[j][n + 1]) % p + p) % p;
    }
}
for (int i = 1; i <= n; i++) {
    std::cout << "x" << i << "=" << a[i][n + 1] << "\n";
}
return 0;