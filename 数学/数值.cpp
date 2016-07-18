//数值积分
//F为被积分函数
double simpson(double a,double b)
{
    double c = a+(b-a)/2;
    return (F(a)+4*F(c)+F(b))*(b-a)/6;
}

double asr(double a,double b,double eps,double A)
{
    double c = a + (b-a)/2;
    double L = simpson(a,c), R = simpson(c,b);
    if(fabs(L+R-A) <= 15*eps) return L+R+(L+R-A)/15.0;
    return asr(a,c,eps/2,L) + asr(c,b,eps/2,R);
}

double asr(double a,double b,double eps)
{
    return asr(a,b,eps,simpson(a,b));
}

//////////三分/////////////

double high,low,mid,midmid;
while(high - low > eps)
{
    mid = (low + high)/2;
    midmid = (mid + high)/2;
    double fmid = f(mid) , fmidmid = f(midmid);
    if( fmid > fmidmid)
        high = midmid;
    else
        low = mid;
}

return low;
////////////////////////////////////////
int high,low,mid,midmid,res;
while(low <= high)
{
    mid = (high + low)/2;
    midmid = (mid + high)/2;
    int cmid = cal(mid) , cmidmid = cal(midmid);
    if( cmid >= cmidmid )
    {
        res = mid;
        high = midmid-1;
    }
    else
    {
        res = midmid;
        low = mid+1;
    }
}

return res;

