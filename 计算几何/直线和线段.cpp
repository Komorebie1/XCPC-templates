struct Line {
    Point A, B; //A为方向向量, B为直线上一点
    Line(Point x = Point(0, 0), Point y = Point(0, 0)) : A(x), B(y) {}
    void read() { cin >> this->A.x >> this->A.y >> this->B.x >> this->B.y; }
    double dis(Point p) { return fabs((p - this->A) ^ (this->A - this->B)) / Len(this->A - this->B); }  // 点到直线的距离
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