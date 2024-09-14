int qpow(int x, int k, int Mod) {
    int res = 1;
    while(k) {
        if(k & 1)
            res = 1ll * res * x % Mod;
        x = 1ll * x * x % Mod;
        k >>= 1;
    }
    return res;
}