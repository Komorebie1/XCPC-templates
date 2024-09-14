#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define PII pair<int, int>
#define pi acos(-1.0)
const int N = 1e5 + 10;

#define eps 1e-8
inline int sgn(double x) { return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1); }  // 判断正负

struct Point {
    double x, y;
    Point(double nx = 0, double ny = 0) : x(nx), y(ny) {}
    void read() { cin >> this->x >> this->y; }
    inline Point operator+(Point A) { return Point(A.x + this->x, A.y + this->y); }
    inline Point operator-(Point A) { return Point(this->x - A.x, this->y - A.y); }
    inline Point operator*(double x) { return Point(this->x * x, this->y * x); }
    inline Point operator/(double x) { return Point(this->x / x, this->y / x); }
    inline bool operator==(Point A) { return this->x == A.x && this->y == A.y; }
    inline double operator*(Point A) { return this->x * A.x + this->y * A.y; }  // 点乘
    inline double operator^(Point A) { return this->x * A.y - this->y * A.x; }  // 叉积（注意先后顺序）
    inline double len() { return sqrt((*this) * (*this)); }
    inline Point rotate(double rad) { return Point(this->x * cos(rad) - this->y * sin(rad), this->x * sin(rad) + this->y * cos(rad)); }
};
Point projection(Point A, Point B, Point P) { return A + (B - A) / ((B - A).len()) * ((B - A) * (P - A)) / (B - A).len(); }// 求P在向量AB上的投影点

typedef Point Vector;
inline double Len(Vector A) { return sqrt(A * A); }
inline double Ang(Vector A, Vector B) { return acos(A * B) / A.len() / B.len(); }  // 两个向量夹角
inline double Area(Vector A, Vector B) { return (A ^ B) / 2; }                     // 两个向量组成的三角形的面积
inline Vector Normal(Vector A)                                                     // 与A正交的单位向量
{
    double len = A.len();
    return Vector(-A.y / len, A.x / len);
}
inline int toleft(Vector A, Vector B)  // toleft测试: B在A左边为1, 右边为-1, 方向相同为0
{
    double t = A ^ B;
    return (t > eps) - (t < -eps);
}

bool argcmp(Point a, Point b)  // 极角排序
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
    // if (abs(t)<=eps) return a*a<b*b-eps;  // 不同长度的向量需要分开
    return t > eps;
}