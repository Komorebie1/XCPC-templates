int getsg(int x) {
    if (sg[x] != -1) return sg[x];
    
    unordered_set<int> S;
    for (int v:G[x]) // 可能的转移
        if(x >= v) 
            S.insert(sg(x - v));
    
    for (int i = 0; ; ++ i)
        if (S.count(i) == 0)
            return sg[x] = i;
}