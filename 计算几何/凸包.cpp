struct Convex {
    vector<Point> p;

    int in(Point a)  // -1表示在边上，0在凸多边形外，1在凸多边形内
    {
        auto& p = this->p;
        if (p.size() == 1) return a == p[0] ? -1 : 0;
        if (p.size() == 2) return Seg{p[0], p[1]}.on(a) ? -1 : 0;
        if (a == p[0]) return -1;
        if (toleft(p[1] - p[0], a - p[0]) == -1 || toleft(p.back() - p[0], a - p[0]) == 1) return 0;
        auto cmp = [&](Point u, Point v) { return toleft(u - p[0], v - p[0]) == 1; };
        int l = lower_bound(p.begin() + 1, p.end(), a, cmp) - p.begin();
        if (l == 1) return Seg{p[0], p[l]}.on(a) ? -1 : 0;
        if (l == p.size() - 1 && Seg{p[0], p[l]}.on(a)) return -1;
        if (Seg{p[l - 1], p[l]}.on(a)) return -1;
        return (toleft(p[l] - p[l - 1], a - p[l - 1]) > 0);
    }

    double circ()  // 周长
    {
        double sum = 0;
        for (int i = 0; i < p.size(); i++) {
            sum += Len(p[i] - p[i + 1 == p.size() ? 0 : i + 1]);
        }
        return sum;
    }

    double area()
    {
        double sum = 0;
        for (int i = 0; i < p.size(); i++) {
            sum += p[i] ^ p[(i + 1) % p.size()];
        }
        return sum;
    }

    Convex operator+(Convex& c)  // 闵可夫斯基和
    {
        auto& p = this->p;
        vector<Point> res;
        vector<Seg> e1(p.size()), e2(c.p.size()), edge(p.size() + c.p.size());
        res.reserve(p.size() + c.p.size());
        auto cmp = [](Seg& u, Seg& v) { return argcmp(u.B - u.A, v.B - v.A); };
        for (int i = 0; i < p.size(); i++) e1[i] = {p[i], p[i + 1 == p.size() ? 0 : i + 1]};
        for (int i = 0; i < c.p.size(); i++) e2[i] = {c.p[i], c.p[i + 1 == c.p.size() ? 0 : i + 1]};
        rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
        rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
        merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);
        auto check = [&](Point& u) {
            auto last = res.back(), last2 = res[res.size() - 2];
            return toleft(last - last2, u - last) == 0 && (last - last2) * (u - last) >= -eps;
        };
        auto u = e1[0].A + e2[0].A;
        for (auto v : edge) {
            while (res.size() > 1 && check(u)) res.pop_back();
            res.push_back(u);
            u = u + v.B - v.A;
        }
        if (res.size() > 1 && check(res[0])) res.pop_back();
        return Convex{res};
    }
};

Convex Andrew(vector<Point> p)  // Andrew求凸包O(n\log n)
{
    vector<Point> st;
    if (p.empty()) return Convex{st};
    sort(p.begin(), p.end(), [](Point& A, Point& B) { return fabs(A.x - B.x) > eps ? A.x < B.x : A.y < B.y; });

    auto check = [&](Point cur) {
        auto last = st.back(), last2 = st[st.size() - 2];
        return toleft(last - last2, cur - last) <= 0;
    };

    for (auto cur : p) {
        while (st.size() > 1 && check(cur)) st.pop_back();
        st.push_back(cur);
    }
    int t = st.size();
    p.pop_back();
    reverse(p.begin(), p.end());
    for (auto cur : p) {
        while (st.size() > t && check(cur)) st.pop_back();
        st.push_back(cur);
    }
    st.pop_back();
    return Convex{st};
}