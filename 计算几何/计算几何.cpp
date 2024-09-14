#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define double long double
#define PII pair<int, int>
#define pi acos(-1.0)
const int N = 1e5 + 10;

#define eps 1e-8
inline int sgn(double x) { return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1); }  // 判断正负

struct Point {
    double x, y;
    Point(double nx = 0, double ny = 0) : x(nx), y(ny) {}
    void read() { cin >> this->x >> this->y; }
    inline bool operator<(Point A)
    {
        if (sgn(this->x - A.x) == 0) return this->y < A.y - eps;
        return this->x < A.x - eps;
    }
    inline Point operator+(Point A) { return Point(A.x + this->x, A.y + this->y); }
    inline Point operator-(Point A) { return Point(this->x - A.x, this->y - A.y); }
    inline Point operator*(double x) { return Point(this->x * x, this->y * x); }
    inline Point operator/(double x) { return Point(this->x / x, this->y / x); }
    inline bool operator==(Point A) { return sgn(this->x - A.x) == 0 && sgn(this->y - A.y) == 0; }
    inline double operator*(Point A) { return this->x * A.x + this->y * A.y; }  // 点乘
    inline double operator^(Point A) { return this->x * A.y - this->y * A.x; }  // 叉积（注意先后顺序）
    inline double len() { return sqrt((*this) * (*this)); }
    inline double len2() { return (*this) * (*this); }
    inline double dis2(Point A) { return (*this - A).len2(); }
    inline double dis(Point A) { return sqrt(this->dis2(A)); }
    inline Point unit() { return Point(this->x / this->len(), this->y / this->len()); }
    inline int toleft(Point A)
    {
        double t = (*this) ^ A;
        return (t > eps) - (t < -eps);
    }
    inline Point Normal() { return Point(-this->y / this->len(), this->x / this->len()); }  // 与A正交的单位向量
    inline Point rotate(double rad) { return Point(this->x * cos(rad) - this->y * sin(rad), this->x * sin(rad) + this->y * cos(rad)); }
    inline Point rotate(double costh, double sinth) { return Point(this->x * costh - this->y * sinth, this->x * sinth + this->y * costh); }
};
typedef Point Vector;

inline double Len(Vector A) { return sqrt(A * A); }
inline double Ang(Vector A, Vector B) { return acos(A * B) / A.len() / B.len(); }  // 两个向量夹角
inline double Area(Vector A, Vector B) { return (A ^ B) / 2; }                     // 两个向量组成的三角形的面积
inline int toleft(Vector A, Vector B)                                              // toleft测试: B在A左边为1, 右边为-1, 方向相同为0
{
    double t = A ^ B;
    return (t > eps) - (t < -eps);
}

bool argcmp(Point a, Point b)
{
    auto quad = [](Point& a) {
        if (a.y < -eps) return 1;
        if (a.y > eps) return 4;
        if (a.x < -eps) return 5;
        if (a.x > eps) return 3;
        return 2;
    };
    int qa = quad(a), qb = quad(b);
    if (qa != qb) return qa < qb;
    auto t = a ^ b;
    // if (abs(t) <= eps) return a * a < b * b - eps;  // 不同长度的向量需要分开
    return t > eps;
}

struct Line {
    Point A, B;
    Line(Point x = Point(0, 0), Point y = Point(0, 0)) : A(x), B(y) {}
    void read() { cin >> this->A.x >> this->A.y >> this->B.x >> this->B.y; }
    double dis(Point p) { return fabs((p - this->A) ^ (this->A - this->B)) / Len(this->A - this->B); }  // 点到直线的距离
    Point projection(Point P)
    {
        double res = (B - A) * (P - A) / (B - A).len();
        return A + (B - A) / ((B - A).len()) * res;
    }
};

struct Seg {
    Point A, B;
    Seg(Point x = Point(0, 0), Point y = Point(0, 0)) : A(x), B(y) {}
    void read() { cin >> this->A.x >> this->A.y >> this->B.x >> this->B.y; }
    double dis(Point p)  // 点到线段距离
    {
        if ((p - this->A) * (this->B - this->A) < -eps || (p - this->B) * (this->A - this->B) < -eps) return min(Len(p - this->A), Len(p - this->B));
        return Line{A, B}.dis(p);
    }
    int on(Point p)  // -1表示在端点，1表示在线段上，0表示不在线段上
    {
        if (p == this->A || p == this->B) return -1;
        return (toleft(p - this->A, p - this->B) == 0 && (p - this->A) * (p - this->B) < -eps);
    }
};

inline bool IsIntersect(Seg S1, Seg S2)  // 两个线段是否相交
{
    double f1 = (S1.B - S1.A) ^ (S2.A - S1.A), f2 = (S1.B - S1.A) ^ (S2.B - S1.A);
    double g1 = (S2.B - S2.A) ^ (S1.A - S2.A), g2 = (S2.B - S2.A) ^ (S1.B - S2.A);
    return ((f1 < 0) ^ (f2 < 0)) && ((g1 < 0) ^ (g2 < 0));
}
inline Point LineIntersection(Line L1, Line L2) { return L1.A + (L1.B - L1.A) * ((L2.B - L2.A) ^ (L1.A - L2.A)) / ((L1.B - L1.A) ^ (L2.B - L2.A)); }  // 两条直线求交点

struct Polygon {
    vector<Point> p;

    double circ()  // 周长
    {
        double sum = 0;
        for (int i = 0; i < p.size(); i++) {
            sum += Len(p[i] - p[i + 1 == p.size() ? 0 : i + 1]);
        }
        return sum;
    }

    double area()  // 逆时针存储时为正
    {
        double sum = 0;
        for (int i = 0; i < p.size(); i++) {
            sum += p[i] ^ p[(i + 1) % p.size()];
        }
        return sum * 0.5;
    }

    int in_polyon(Point a)  // -1表示在边上，0在多边形外，1在多边形内
    {
        int cnt = 0;
        for (int i = 0; i < p.size(); i++) {
            Seg s(p[i], p[i + 1 == p.size() ? 0 : i + 1]);
            if (s.on(a)) return -1;
            double d1 = a.y - s.A.y, d2 = a.y - s.B.y;
            double det = (s.A - a) ^ (s.B - a);
            if ((sgn(det) >= 0 && sgn(d1) < 0 && sgn(d2) >= 0) || (sgn(det) <= 0 && sgn(d2) < 0 && sgn(d1) >= 0)) cnt++;
        }
        return cnt & 1;
    }
};

struct Convex : Polygon {

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

    double diameter()
    {
        double ans = 0;
        auto area = [](Point u, Point v, Point w) -> double { return (w - u) ^ (w - v); };  // 要求逆时针存点
        for (int i = 0, j = 1; i < p.size(); i++) {
            int nxt = i + 1 == p.size() ? 0 : i + 1;
            while (sgn(area(p[i], p[nxt], p[j]) - area(p[i], p[nxt], p[j + 1 == p.size() ? 0 : j + 1])) <= 0) j = j + 1 == p.size() ? 0 : j + 1;
            ans = max({ans, p[i].dis(p[j]), p[nxt].dis(p[j])});
        }
        return ans;
    }
};

Convex Andrew(vector<Point> p)  // Andrew求凸包O(n\log n)
{
    vector<Point> st;
    if (p.empty()) return Convex{st};
    sort(p.begin(), p.end(), [](Point& A, Point& B) { return fabs(A.x - B.x) > eps ? A.x < B.x : A.y < B.y; });

    auto check = [&](Point cur) {
        auto last = st.back(), last2 = st[st.size() - 2];
        return toleft(last - last2, cur - last) < 0;  // <=时会跳过经过的点
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

double ClosestPair(vector<Point> p)  // 平面最近点对 O(n\log n), 调用之前先排序
{
    if (p.size() == 1) return 1e20;
    if (p.size() == 2) {
        return p[0].dis(p[1]);
    }
    int mid = p.size() / 2;
    double d = min(ClosestPair(vector<Point>(p.begin(), p.begin() + mid)), ClosestPair(vector<Point>(p.begin() + mid, p.end())));
    vector<Point> tmp;
    for (int i = 0; i < p.size(); i++) {
        if (fabs(p[i].x - p[mid].x) < d + eps) {
            tmp.push_back(p[i]);
        }
    }
    sort(tmp.begin(), tmp.end(), [&](const Point& a, const Point& b) { return a.y < b.y; });
    for (int i = 0; i < tmp.size(); i++) {
        for (int j = i + 1; j < tmp.size() && tmp[j].y - tmp[i].y < d + eps; j++) {
            d = min(d, tmp[i].dis(tmp[j]));
        }
    }
    return d;
}

struct Circle {
    Point O;
    double r;

    bool operator==(const Circle& A) { return this->O == A.O && sgn(this->r - A.r) == 0; }
    double area() { return r * r * pi; }
    double circ() { return r * pi * 2; }

    int in(Point a)  // -1 圆上 | 0 圆外 | 1 圆内
    {
        if (a.dis(this->O) > r + eps) return 0;
        if (sgn(a.dis(this->O) - r) == 0) return -1;
        return 1;
    }

    int relation(Circle a)  // -1 相同 | 0 相离 | 1 外切 | 2 相交 | 3 内切a | 4 被a内切 | 5 内含于a | 6 被a内含
    {
        double d = a.O.dis(this->O);
        if (*this == a) return -1;
        if (d > a.r + this->r + eps) return 0;
        if (sgn(d - a.r - this->r) == 0) return 1;
        if (sgn(d - a.r + this->r) == 0) return 3;
        if (sgn(d + a.r - this->r) == 0) return 4;
        if (d + this->r < a.r - eps) return 5;
        if (d + a.r < this->r - eps) return 6;
        return 2;
    }

    vector<Point> cross(Line l)
    {
        double d = l.dis(this->O);
        if (d > this->r + eps) return vector<Point>();
        Point p = l.projection(this->O);
        if (sgn(d - this->r) == 0) return vector<Point>{p};
        double k = sqrt(this->r * this->r - d * d);
        Vector v = (l.A - l.B).unit() * k;
        return vector<Point>{p + v, p - v};
    }

    vector<Point> cross(Circle a)
    {
        int t = this->relation(a);
        if (t == -1 || t == 0 || t == 5 || t == 6) return vector<Point>();
        double d = O.dis(a.O);
        Vector dr = (a.O - O).unit() * r;
        if (t == 1 || t == 4) return vector<Point>{O + dr};
        if (t == 3) return vector<Point>{O - dr};
        double costh = (r * r + d * d - a.r * a.r) / (2 * d * r);
        double sinth = sqrt(1 - costh * costh);
        return vector<Point>{O + dr.rotate(costh, sinth), O + dr.rotate(costh, -sinth)};
    }

    double area(Circle a)
    {
        int t = relation(a);
        if (t == -1) return area();
        if (t == 0 || t == 1) return 0;
        if (t >= 3) return min(area(), a.area());
        vector<Point> p = cross(a);
        double d = O.dis(a.O);
        double costh1 = (r * r + d * d - a.r * a.r) / (2 * r * d), costh2 = (a.r * a.r + d * d - r * r) / (2 * a.r * d);
        double sinth1 = sqrt(1 - costh1 * costh1), sinth2 = sqrt(1 - costh2 * costh2);
        double th1 = acos(costh1), th2 = acos(costh2);
        return r * r * (th1 - costh1 * sinth1) + a.r * a.r * (th2 - costh2 * sinth2);
    }

    vector<Point> tangent_points(Point a)
    {
        int t = this->in(a);
        if (t == 1) return vector<Point>();
        double d = O.dis(a);
        Vector dr = (a - O).unit() * r;
        if (t == -1) {
            return vector<Point>{O + dr};
        }
        double costh = r / d;
        double sinth = sqrt(1 - costh * costh);
        return vector<Point>{O + dr.rotate(costh, sinth), O + dr.rotate(costh, -sinth)};
    }

    vector<Point> tangent_points(Circle a)
    {
        int t = relation(a);
        vector<Point> res;
        if (t == -1 || t == 5 || t == 6) return res;
        if (t == 1 || t == 4) {
            res.push_back(O + (a.O - O).unit() * r);
        }
        else if (t == 3) {
            res.push_back(O - (a.O - O).unit() * r);
        }
        double d = O.dis(a.O);
        Vector e = (a.O - O).unit();
        if (t <= 2) {
            double costh = (r - a.r) / d;
            double sinth = sqrt(1 - costh * costh);
            Vector u = e.rotate(costh, sinth), v = e.rotate(costh, -sinth);
            res.push_back(O + u * r), res.push_back(O + u * a.r);
            res.push_back(O + v * r), res.push_back(O + v * a.r);
        }
        if (t == 0) {
            double costh = (r + a.r) / d;
            double sinth = sqrt(1 - costh * costh);
            Vector u = e.rotate(costh, sinth), v = e.rotate(costh, -sinth);
            res.push_back(O + u * r), res.push_back(O - u * a.r);
            res.push_back(O + v * r), res.push_back(O - v * a.r);
        }
        return res;
    }
};

Circle excircle(vector<Point> p)  // 外接圆(1)(尽量用 long double)(推荐写法)
{
    double s = (p[0] - p[1]) ^ (p[0] - p[2]);
    Point O;
    O.x = (p[0].y * (p[1].len2() - p[2].len2()) + p[1].y * (p[2].len2() - p[0].len2()) + p[2].y * (p[0].len2() - p[1].len2())) / (-2 * s);
    O.y = (p[0].x * (p[1].len2() - p[2].len2()) + p[1].x * (p[2].len2() - p[0].len2()) + p[2].x * (p[0].len2() - p[1].len2())) / (2 * s);
    double r = O.dis(p[0]);
    return Circle{O, r};
}

// Circle excircle(vector<Point> p)  // 外接圆(2)(尽量用 long double)
// {
//     auto get_midline = [&](Point a, Point b) {
//         Point mid = (a + b) / 2;
//         Vector v = Vector(-(a - b).y, (a - b).x);
//         return Line(mid, mid + v);
//     };

//     Point O = LineIntersection(get_midline(p[0], p[1]), get_midline(p[0], p[2]));
//     double r = O.dis(p[0]);
//     return Circle{O, r};
// }

Circle incircle(vector<Point> p)  // 内切圆(尽量用 long double)
{
    auto get_angmidline = [&](Point O, Point a, Point b) { return Line(O, O + (a - O).unit() + (b - O).unit()); };

    Point O = LineIntersection(get_angmidline(p[0], p[1], p[2]), get_angmidline(p[1], p[0], p[2]));
    double r = Seg{p[0], p[1]}.dis(O);
    return Circle{O, r};
}