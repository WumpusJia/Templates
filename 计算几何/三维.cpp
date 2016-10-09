#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<vector>
using namespace std;

const double eps = 1e-10;

struct Point3
{
    double x,y,z;
    Point3(double x = 0,double y = 0,double z = 0):x(x),y(y),z(z) {}
};
typedef Point3 Vector3;

Vector3 operator + (Vector3 A,Vector3 B)
{
    return Vector3(A.x+B.x,A.y+B.y,A.z+B.z);
}
Vector3 operator - (Point3 A,Point3 B)
{
    return Vector3(A.x-B.x,A.y-B.y,A.z-B.z);
}
Vector3 operator * (Vector3 A,double p)
{
    return Vector3(A.x*p,A.y*p,A.z*p);
}
Vector3 operator / (Vector3 A,double p)
{
    return Vector3(A.x/p,A.y/p,A.z/p);
}

double Dot(Vector3 A,Vector3 B) { return A.x*B.x+A.y*B.y+A.z*B.z; }
double Length(Vector3 A) { return sqrt(Dot(A,A)); }
double Angle(Vector3 A,Vector3 B)
    { return acos(Dot(A,B) / Length(A) / Length(B)); }
double dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    else return x<0?-1:1;
}
bool operator == (const Point3& a,const Point3& b)
{
    return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0 && dcmp(a.z-b.z) == 0;
}
 //p到面(p0,n)的距离,n需为单位向量
double PointToPlane(Point3 p,Point3 p0,Vector3 n)
{
    return fabs(Dot(p-p0,n));
}
//p在(p0,n)的投影，n须为单位向量
Point3 PlaneProjection(Point3 p,Point3 p0,Vector3 n)
{
    return p-n*Dot(p-p0,n);
}
//p1-p2和(p0,n)的交点（假定存在）
Point3 LinePlanePoint(Point3 p1,Point3 p2,Point3 p0,Vector3 n)
{
    Vector3 v = p2-p1;
    double t = (Dot(n,p0-p1) / Dot(n,p2-p1));
    return p1+v*t;
}

Vector3 Cross(Vector3 A,Vector3 B)
{
    return Vector3(A.y*B.z-A.z*B.y,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x);
}
double Area2(Point3 A,Point3 B,Point3 C)
{
    return Length(Cross(B-A,C-A));
}

//判断P是否在三角形P0P1P2中(假设P在平面P0,P1,P2上)
bool IsPointInTriangle(Point3 P,Point3 P0,Point3 P1,Point3 P2)
{
    double area1 = Area2(P,P0,P1);
    double area2 = Area2(P,P1,P2);
    double area3 = Area2(P,P2,P0);
    return dcmp(area1+area2+area3 - Area2(P0,P1,P2)) == 0;
}
 //判断三角形P0P1P2是否和线段AB相交
bool IsSegmentTriangleIntersection(Point3 P0,Point3 P1,
    Point3 P2,Point3 A,Point3 B,Point3& P)
{
    Vector3 n = Cross(P1-P0,P2-P0);
    if(dcmp(Dot(n,B-A)) == 0) return false;
    else
    {
        double t = Dot(n,P0-A) / Dot(n,B-A);
        if(dcmp(t) < 0 || dcmp(t-1) > 0) return false;
        P = A + (B-A)*t;
        return IsPointInTriangle(P,P0,P1,P2);
    }
}

double PointToLine(Point3 P,Point3 A,Point3 B) //P到AB距离
{
    Vector3 v1 = B-A,v2 = P-A;
    return Length(Cross(v1,v2) / Length(v1));
}
double PointToSegment(Point3 P,Point3 A,Point3 B)//P到线段AB距离
{
    if(A == B) return Length(P-A);
    Vector3 v1 = B-A,v2 = P-A,v3 = P-B;
    if(dcmp(Dot(v1,v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1,v3)) > 0) return Length(v3);
    else return Length(Cross(v1,v2)) / Length(v1);
}
 //四面体ABCD有向面积的６倍
double Volume6(Point3 A,Point3 B,Point3 C,Point3 D)
{
    return Dot(D-A,Cross(B-A,C-A));
}

/*

//三维凸包
struct Face {
  int v[3];
  Face(int a, int b, int c) { v[0] = a; v[1] = b; v[2] = c; }
  Vector3 Normal(const vector<Point3>& P) const {
    return Cross(P[v[1]]-P[v[0]], P[v[2]]-P[v[0]]);
  }
  // f是否能看见P[i]
  int CanSee(const vector<Point3>& P, int i) const {
    return Dot(P[i]-P[v[0]], Normal(P)) > 0;
  }
};

double rand01() { return rand()/(double)RAND_MAX; }
double randeps() { return (rand01() - 0.5)*eps; }
Point3 add_noise(Point3 p)
{
    return Point3(p.x+randeps(),p.y+randeps(),p.z+randeps());
}


//调用前需要对点进行判重和用上述函数进行微小扰动
vector<Face> CH3D(const vector<Point3>& P) {
  int n = P.size();
  vector<vector<int> > vis(n);
  for(int i = 0; i < n; i++) vis[i].resize(n);

  vector<Face> cur;
  cur.push_back(Face(0, 1, 2)); // 由于已经进行扰动，前三个点不共线
  cur.push_back(Face(2, 1, 0));
  for(int i = 3; i < n; i++) {
    vector<Face> next;
    // 计算每条边的“左面”的可见性
    for(int j = 0; j < cur.size(); j++) {
      Face& f = cur[j];
      int res = f.CanSee(P, i);
      if(!res) next.push_back(f);
      for(int k = 0; k < 3; k++) vis[f.v[k]][f.v[(k+1)%3]] = res;
    }
    for(int j = 0; j < cur.size(); j++)
      for(int k = 0; k < 3; k++) {
        int a = cur[j].v[k], b = cur[j].v[(k+1)%3];
        if(vis[a][b] != vis[b][a] && vis[a][b])
        // (a,b)是分界线，左边对P[i]可见
          next.push_back(Face(a, b, i));
      }
    cur = next;
  }
  return cur;
}

*/

