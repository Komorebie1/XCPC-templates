struct ACAM {
    int n;
    int trie_size = 10;
    vector<string> T;
    vector<vector<int>> trie;
    vector<int> pos, fail, cnt, id, q, end;

    void init()
    {
        trie.resize(trie_size, vector<int>(26, 0));
        pos.resize(n, 0);
        fail.resize(trie_size, 0);
        cnt.resize(trie_size, 0);
        id.resize(trie_size, -1);
        end.resize(trie_size, 0);
    }
    void build()
    {
        int idx = 1;  // trie树
        for (int i = 0; i < n; i++) {
            int p = 1;
            for (auto c : T[i]) {
                int cur = c - 'a';
                if (!trie[p][cur]) trie[p][cur] = ++idx;
                p = trie[p][cur];
            }
            pos[i] = p;
            id[p] = i;
            end[p]++;  // 统计以该节点结尾的模式串个数
        }
        auto& q = this->q;  // 处理根节点的回跳
        int ql = 0;
        for (auto& c : trie[1]) {
            if (c) {
                fail[c] = 1;
                q.push_back(c);
            }
            else
                c = 1;
        }
        while (ql < q.size())  // BFS
        {
            int u = q[ql++];
            for (int c = 0; c < 26; c++) {
                if (trie[u][c])  // 有儿子存在时
                {
                    fail[trie[u][c]] = trie[fail[u]][c];  // 回跳边（四边形）
                    q.push_back(trie[u][c]);
                }
                else {
                    trie[u][c] = trie[fail[u]][c];  // 转移边（三角形）
                }
            }
            end[u] += end[fail[u]];
        }
    }

    void count(string S)  // 统计每个结点在文本串中出现次数
    {
        auto& q = this->q;
        for (int cur = 1, i = 0; i < S.size(); i++) {
            int nxt = trie[cur][S[i] - 'a'];
            cnt[cur = nxt]++;
        }

        reverse(q.begin(), q.end());
        for (auto cur : q) {
            cnt[fail[cur]] += cnt[cur];
        }
    }
};
