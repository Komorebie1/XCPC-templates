std::vector<int> manacher(std::string s)  // 最后减一才是半径(奇偶都是)
{
    std::string t = "#";
    for (auto c : s) {
        t += c, t += '#';
    }
    int n = t.size();
    std::vector<int> r(n);
    for (int i = 0, j = 0; i < n; i++) {
        if (2 * j - i >= 0 && j + r[j] > i) {
            r[i] = std::min(r[2 * j - i], j + r[j] - i);
        }
        while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]]) {
            r[i] += 1;
        }
        if (i + r[i] > j + r[j]) {
            j = i;
        }
    }
    return r;
}
/*
例如：aaa -> #a#a#a#
return: {1 2 3 4 3 2 1}
*/