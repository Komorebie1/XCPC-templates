struct PAM {
    int len[N], num[N], fail[N], trie[N][26], tot = 1;
    int getfail(int x, int i, string s)
    {
        while (i - len[x] - 1 < 0 || s[i] != s[i - len[x] - 1]) x = fail[x];
        return x;
    }
    void build(string s)
    {
        int cur = 0;
        fail[0] = 1, len[1] = -1;
        for (int i = 0; i < s.size(); i++) {
            int u = s[i] - 'A';
            int pos = getfail(cur, i, s);
            if (!trie[pos][u]) {
                trie[pos][s[i]] = ++tot;
                fail[tot] = trie[getfail(fail[pos], i, s)][u];
                len[tot] = len[pos] + 2;
            }
            cur = trie[pos][u];
            num[cur]++;
        }
        for (int i = tot; i >= 2; i--) num[fail[i]] += num[i];
    }
}

// 用法
void dfs(int u1, int u2)
{
    if (u1 > 1 && u2 > 1) ans += 1ll * A.num[u1] * B.num[u2];
    for (int i = 0; i < 26; i++) {
        if (A.trie[u1][i] && B.trie[u2][i]) dfs(A.trie[u1][i], B.trie[u2][i]);
    }
}
int main()
{
    dfs(0, 0);
    dfs(1, 1);
}