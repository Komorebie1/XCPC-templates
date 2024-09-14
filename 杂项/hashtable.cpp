struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1,T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ h2; // 哈希组合
    }
};

unordered_map<pair<int, int>, int, pair_hash>mp;  // 使用方法