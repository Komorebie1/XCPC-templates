template <typename T> struct ST {
    const int B = 30;
    int n;
    vector<vector<T>> a;
    ST(int n) : n(n) { a.resize(n + 1, vector<T>(B)); }
    ST(vector<T> nums)
    {
        this->n = nums.size() - 1;
        a.resize(n + 1, vector<T>(B));
        for (int i = 1; i <= n; i++) a[i][0] = nums[i];
        build();
    }
    ST(T nums[], int n)
    {
        this->n = n;
        a.resize(n + 1, vector<T>(B));
        for (int i = 1; i <= n; i++) a[i][0] = nums[i];
        build();
    }
    T calc(T x, T y) { return max(x, y); }
    void build()
    {
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++) a[i][j] = calc(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
    }
    T query(int l, int r)
    {
        if (r < l) return 0;
        int k = log2(r - l + 1);
        return calc(a[l][k], a[r - (1 << k) + 1][k]);
    }
};