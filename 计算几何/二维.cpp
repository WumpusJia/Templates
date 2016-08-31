//极角排序
typedef long long LL;

struct Point
{
    LL x,y;
    Point(LL x = 0,LL y = 0):x(x),y(y) {}
};
typedef Point Vector;
Vector operator + (Vector A,Vector B)
    { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Point A,Point B)
    { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A,LL p)
    { return Vector(A.x*p,A.y*p); }
Vector operator / (Vector A,LL p)
    { return Vector(A.x/p,A.y/p); }
bool operator < (const Point& A,const Point& B)
    { return A.x < B.x || (A.x == B.x && A.y < B.y); }

LL Dot(Vector A,Vector B) { return A.x*B.x + A.y*B.y; }
LL Cross(Vector A,Vector B) { return A.x*B.y - A.y*B.x; }


int getQuadrant(const Point& A) //从左下到左上
{
    if(A.x <= 0 && A.y < 0) return 1;
    else if(A.x > 0 && A.y <= 0) return 2;
    else if(A.x >= 0 && A.y > 0) return 3;
    else if(A.x < 0 && A.y >= 0) return 4;
}


bool cmpang(const Point& A,const Point& B)
{
    int qA = getQuadrant(A);
    int qB = getQuadrant(B);
    if(qA == qB)
    {
            return Cross(A,B) > 0;
    }
    else
        return qA < qB;
}


int pn = 0;
for(int j = 0;j < n;++j)
    if(x != j)
        p[pn++] = save[j]-save[x];

sort(p,p+pn,cmpang);


//////////////////////
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps = 1e-10;
const double PI = acos(-1.0);

int dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    else return x > 0? 1:-1;
}

/////////////////点和直线部分//////////////
struct Point
{
    double x,y;
    Point(double x = 0,double y = 0):x(x),y(y) {}
};
typedef Point Vector;
Vector operator + (Vector A,Vector B)
    { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Point A,Point B)
    { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A,double p)
    { return Vector(A.x*p,A.y*p); }
Vector operator / (Vector A,double p)
    { return Vector(A.x/p,A.y/p); }
bool operator == (const Point& A,const Point& B)
    { return dcmp(A.x-B.x) == 0 && dcmp(A.y-B.y) == 0; }
bool operator < (const Point& A,const Point& B)
    { return A.x < B.x || (A.x == B.x && A.y < B.y); }
double Dist(Point A,Point B)
{
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}
double Dot(Vector A,Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector A,Vector B) { return A.x*B.y - A.y*B.x; }
double Length(Vector A) { return sqrt(Dot(A,A)); }
double Angle(Vector A,Vector B)
    { return acos(Dot(A,B) / Length(A) / Length(B)); } //A,B所成角
double Angle(Vector A)
    { return atan2(A.y,A.x); } //向量与x轴正方向所成角
double Area2(Point A,Point B,Point C)
    { return fabs(Cross(B-A,C-A)); } //求AB,AC向量所成平行四边形面积
Vector Normal(Vector A) //求A向量单位法相量　向左侧
{
    double L = Length(A);
    return Vector(-A.y/L,A.x/L);
}
Vector Rotate(Vector A,double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
//求P+tv和Q+tw的交点  ,使用前需要判断是否存在唯一交点(Cross(v,w) != 0)
Point TwoLinePoint(Point P,Vector v,Point Q,Vector w)
{
    Vector u = P-Q;
    double t = Cross(w,u)/Cross(v,w);
    return P+v*t;
}
double PointToLine(Point P,Point A,Point B) //点P到AB直线距离
{
    Vector v1 = B-A,v2 = P-A;
    return fabs(Cross(v1,v2))/Length(v1);
}
double PointToSegment(Point P,Point A,Point B) //点P到线段AB距离
{
    if(A == B) return Length(P-A);
    Vector v = B-A,v1 = P-A,v2 = P-B;
    if(dcmp(Dot(v,v1)) < 0) return Length(v1);
    else if(dcmp(Dot(v,v2)) > 0) return Length(v2);
    else   return fabs(Cross(v,v1)) / Length(v);
}
Point LineProjection(Point P,Point A,Point B) //点P在直线AB上的投影点
{
    Vector v = B-A;
    return A+v*(Dot(v,P-A) / Dot(v,v));
}
 //判断２线段是否相交（规范相交：只有１个交点且交点不在线段端点）
bool IsSegmentProperIntersection(Point a1,Point a2,Point b1,Point b2)
{
    double c1 = Cross(a2-a1,b1-a1),c2 = Cross(a2-a1,b2-a1),
        c3 = Cross(b2-b1,a1-b1),c4 = Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}
bool IsPointOnSegment(Point P,Point A,Point B) //判断点是否在线段上
{
    return dcmp(Cross(A-P,B-P)) == 0
        && dcmp(Dot(A-P,B-P)) <= 0; //如果可以允许在端点上就改成 <=
}
//判断２线段是否相交(非规范）
bool IsSegmentInproperIntersection(Point a1,Point a2,Point b1,Point b2)
{
     if(IsPointOnSegment(a1,b1,b2) || IsPointOnSegment(a2,b1,b2) ||
        IsPointOnSegment(b1,a1,a2) || IsPointOnSegment(b2,a1,a2))
            return true;
    return IsSegmentProperIntersection(a1,a2,b1,b2);
}

double PolygonArea(const vector<Point>& P)//求多边形面积
{
    int n = P.size();
    double area = 0;
    for(int i = 1;i < n-1;++i)
        area += Area2(P[0],P[i],P[i+1]);
    return area/2;
}


////////////////////////直线和圆////////////////////////

struct Line
{
    Point p;
    Vector v;
    Line(Point p,Vector v): p(p),v(v) {}
    Point getPoint(double t) { return p+v*t; } //获得直线上一点
    Line move(double d) { return Line(p+Normal(v)*d,v); }
        //直线沿法相量平移d
};
struct Circle
{
    Point c;
    double r;
    Circle(Point c,double r):c(c),r(r) {}
    Point getPoint(double rad) //获得圆上一点(rad为逆时针角)
    {
        return Point(c.x+cos(rad)*r,c.y+sin(rad)*r);
    }
};
//求直线与圆的交点，返回交点数
int LineCirclePoint(Line L,Circle C,vector<Point>& res)
{
    double a = L.v.x,b = L.p.x-C.c.x,c = L.v.y,d = L.p.y-C.c.y;
    double e = a*a+c*c,f = 2*(a*b + c*d),g = b*b+d*d-C.r*C.r;
    double delta = f*f-4*e*g;
    double t1,t2;
    if(dcmp(delta) < 0) return 0;
    if(dcmp(delta) == 0)
    {
        t1 = t2 = -f / (2*e);
        res.push_back(L.getPoint(t1));
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2*e);
    res.push_back(L.getPoint(t1));
    t2 = (-f + sqrt(delta)) / (2*e);
    res.push_back(L.getPoint(t2));
    return 2;
}
//求２圆交点，返回交点数（特别的－１表示２圆重合，无穷个交点)
int TwoCirclePoint(Circle C1,Circle C2,vector<Point>& res)
{
    double d = Length(C1.c-C2.c);
    if(dcmp(d) == 0)
    {
        if(dcmp(C1.r-C2.r) == 0) return -1;
        return 0;
    }
    if(dcmp(C1.r + C2.r - d) < 0) return 0;
    if(dcmp(fabs(C1.r-C2.r) - d) > 0) return 0;

    double a = Angle(C2.c-C1.c);
    double da = acos((C1.r*C1.r+d*d-C2.r*C2.r) / (2*C1.r*d));
    Point p1 = C1.getPoint(a-da),p2 = C1.getPoint(a+da);

    res.push_back(p1);
    if(p1 == p2) return 1;
    res.push_back(p2);
    return 2;
}
//过顶点球圆的切线，返回切线条数
int PointCircleTangents(Point p,Circle C,vector<Line>& res)
{
    Vector u = C.c - p;
    double dist = Length(u);
    if(dist < C.r) return 0;
    else if(dcmp(dist - C.r) == 0)
    {
        res.push_back(Line(p,Rotate(u,PI/2)));
        return 1;
    }
    else
    {
        double ang = asin(C.r/dist);
        res.push_back(Line(p,Rotate(u,-ang)));
        res.push_back(Line(p,Rotate(u,+ang)));
        return 2;
    }
}
 //返回切线条数，-1表示无穷条切线，a,b表示i条切线咋A，B上的切点
int TwoCircleTangents(Circle A,Circle B,
            vector<Point>& a,vector<Point>& b)
{
    int cnt = 0;
    if(A.r < B.r) { swap(A,B); swap(a,b); }
    int d2 = (A.c.x-B.c.x)*(A.c.x-B.c.x) +
        (A.c.y-B.c.y)*(A.c.y-B.c.y);
    int rdiff = A.r-B.r;
    int rsum = A.r+B.r;
    if(d2 < rdiff*rdiff) return 0;

    double base = atan2(B.c.y-A.c.y,B.c.x-A.c.x);
    if(d2 == 0 && A.r == B.r) return -1;
    if(d2 == rdiff*rdiff)
    {
        a.push_back(A.getPoint(base));
        b.push_back(B.getPoint(base)); cnt++;
        return 1;
    }
    double ang = acos((A.r-B.r) / sqrt(d2));
    a.push_back(A.getPoint(base+ang));
    b.push_back(B.getPoint(base+ang)); cnt++;
    a.push_back(A.getPoint(base-ang));
     b.push_back(B.getPoint(base-ang)); cnt++;
    if(d2 == rsum*rsum)
    {
        a.push_back(A.getPoint(base));
        b.push_back(B.getPoint(PI+base)); cnt++;
    }
    else if(d2 > rsum*rsum)
    {
        double ang = acos((A.r+B.r) / sqrt(d2));
        a.push_back(A.getPoint(base+ang));
        b.push_back(B.getPoint(PI+base+ang)); cnt++;
        a.push_back(A.getPoint(base-ang));
        b.push_back(B.getPoint(PI+base-ang)); cnt++;
    }
    return cnt;
}

/////////////////////////点和多边形///////////////////////////////////
 //判断点p是否在多边形内　-1表示在边界上，1在内部，０在外部
int IsPointInPolygon(Point p,vector<Point>& poly)
{
    int wn = 0;
    int n=poly.size();
    for(int i = 0; i < n; i++)
    {
        if(IsPointOnSegment(p, poly[i], poly[(i+1)%n])) return -1;
//这里注意!，需要将IsPointInSegment中的小于改成小于等于，表示允许在端点上
        int k = dcmp(Cross(poly[(i+1)%n]-poly[i], p-poly[i]));
        int d1 = dcmp(poly[i].y-p.y);
        int d2 = dcmp(poly[(i+1)%n].y-p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) wn++;
        if(k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if (wn != 0) return 1;
    return 0;
}


/////////////////////点群///////////////////////////

//计算凸包
//输入点顺序不会被破坏
//如果希望在凸包的边上有点，把２个<=改成< ?
//精度较高时候使用dcmp比较


//最后res中的凸包点 按逆时针顺序(好像是的)
vector<Point> ConvexHull(vector<Point>& p)
{
  // 预处理，删除重复点
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());

  int n = p.size();
  int m = 0;
  vector<Point> ch(n+1);
  for(int i = 0;i < n;++i)
    {
        while(m > 1
            && dcmp(Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2;i >= 0;--i)
    {
        while(m > k
            && dcmp(Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])) <= 0) m--;
        ch[m++] = p[i];
    }
  if(n > 1) m--;
  ch.resize(m);
  return ch;
}



//分治求最近２点距离　nlognlogn
Point p[maxn];

bool cmpy(const Point& A,const Point& B)
{
    return A.y < B.y || (A.y == B.y && A.x < B.x);
}

 Point tmp[maxn];

double dfs(int L,int R)
{
    if(L == R) return INF;
    if(R-L == 1)
        return Dist(p[L],p[R]);
    int m = (L+R)/2;
    double d1 = dfs(L,m);
    double d2 = dfs(m+1,R);

    double d = min(d1,d2);


    int idx = 0;
    for(int i = L;i <= R;++i)
        if(Dist(p[m],p[i]) <= d)
            tmp[idx++] = p[i];
    sort(tmp,tmp+idx,cmpy);  //这里可以进行归并?　使得复杂度降为nlogn

    double res = d;
    for(int i = 0;i < idx;++i)
    {
        for(int j = i+1;j < idx;++j)
        {
            if( fabs(tmp[i].y-tmp[j].y) > d)
                break;
            res = min(res,Dist(tmp[j],tmp[i]));
        }
    }
    return res;

}

double MinTwoPointDist(int n)
{
    //小心重复点
    sort(p,p+n);
    return dfs(0,n-1);

}



//旋转卡壳求最大２点距离
double RotatingCalipers(vector<Point>& p)
{
    vector<Point> p = ConvexHull(p);
    int n = p.size();
    if(n == 1) return 0;
    if(n == 2) return Dist(p[0], p[1]);
    p.push_back(p[0]); // 免得取模
    double ans = 0;
    for(int u = 0, v = 1; u < n; u++)
    {
        // 一条直线贴住边p[u]-p[u+1]
        for(;;)
        {
// 当Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])时停止旋转
// 即Cross(p[u+1]-p[u], p[v+1]-p[u])-Cross(p[u+1]-p[u], p[v]-p[u])<=0
// 根据Cross(A,B) - Cross(A,C) = Cross(A,B-C)
// 化简得Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
            double diff = Cross(p[u+1]-p[u],p[v+1]-p[v]);
            if(dcmp(diff) <= 0)
            {
                ans = max(ans,Dist(p[u],p[v]));
                if(dcmp(diff) == 0) ans = max(ans,Dist(p[u],p[v+1]));
                break;
            }
            v = (v + 1) % n;
        }
    }
  return ans;
}

// 半平面交最小过程
struct Point
{
    double x,y;
    Point(double x = 0,double y = 0):x(x),y(y) {}
};
typedef Point Vector;

Vector operator + (Vector A,Vector B)
    { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Point A,Point B)
    { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A,double p)
    { return Vector(A.x*p,A.y*p); }
Vector operator / (Vector A,double p)
    { return Vector(A.x/p,A.y/p); }


double Dot(Vector A,Vector B) { return A.x*B.x+A.y*B.y; }
double Cross(Vector A,Vector B) { return A.x*B.y-A.y*B.x; }

struct Line
{
    Point P;
    Vector v;
    double ang;
    Line() {}
    Line(Point P,Vector v):P(P),v(v) { ang = atan2(v.y,v.x); }
    bool operator < (const Line& rhs) const {
        return ang < rhs.ang;
    }
};

bool IsOnLeft(Line L,Point p) //判断点p是否在L的左侧
{
    return Cross(L.v,p-L.P) > 0; //如果半平面交算边线上的话，就改成 >=
}

Point TwoLinePoint(Line a,Line b)
{
    Vector u = a.P-b.P;
    double t = Cross(b.v,u) / Cross(a.v,b.v);
    return a.P + a.v*t;
}

int HalfPlaneIntersection(Line L[],int n,Point poly[])
{
    sort(L,L+n);
    int first = 0,last = 0;
    Point *p = new Point[n];
    Line *q = new Line[n];
    q[first] = L[0];
    for(int i = 1;i < n;++i)
    {
        while(first < last && !IsOnLeft(L[i],p[last-1])) last--;
        while(first < last && !IsOnLeft(L[i],p[first])) first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v,q[last-1].v)) < eps)
        {
            last--;
            if(IsOnLeft(q[last],L[i].P)) q[last] = L[i];
        }
        if(first < last) p[last-1] = TwoLinePoint(q[last-1],q[last]);
    }
    while(first < last && !IsOnLeft(q[first],p[last-1])) last--;
    if(last-first <= 1)  return 0;
    p[last] = TwoLinePoint(q[last],q[first]);

    int m = 0;
    for(int i = first;i <= last;++i) poly[m++] = p[i];
    return m;
}

