int tr[N];

int lowbit(int x) { return x & -x; }

void add(int x, int c)  // 第x位加上c
{
    for (int i = x; i <= n; i += lowbit(i)) {
        tr[i] += c;
    }
}

int sum(int x)  // 求前x位的和
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += tr[i];
    }
    return res;
}