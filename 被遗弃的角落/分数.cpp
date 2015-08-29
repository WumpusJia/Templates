typedef long long LL;
LL gcd(LL a,LL b) { return !b?a:gcd(b,a%b); }
LL lcm(LL a,LL b) { return a / gcd(a,b)*b; }

struct Rat
{
    LL a, b;
    Rat(LL a=0):a(a),b(1) { }
    Rat(LL x, LL y):a(x),b(y) {
    if(b < 0) a = -a, b = -b;
    LL d = gcd(a, b); if(d < 0) d = -d;
    a /= d; b /= d;
  }
};

Rat operator + (const Rat& A,const Rat& B)
{
    LL x = lcm(A.b,B.b);
    return Rat(A.a*(x/A.b) + B.a*(x/B.b),x);
}
Rat operator - (const Rat& A,const Rat& B)
    { return A + Rat(-B.a,B.b); }
Rat operator * (const Rat& A,const Rat& B)
{
    LL t1 = gcd(A.a,B.b),t2 = gcd(A.b,B.a);
    return Rat((A.a/t1)*(B.a/t2),(A.b/t2)*(B.b/t1));
}
