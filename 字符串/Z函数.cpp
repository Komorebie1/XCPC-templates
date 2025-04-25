vector<int> get_z(string s)
{
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0; i < n; i++)
    {
        if (i <= l + z[l] - 1) z[i] = min(z[i - l], l + z[l] - i);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] > l + z[l]) l = i;
    }
    return z;
} // 最后需要修改z[0] = n;