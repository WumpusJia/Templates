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
