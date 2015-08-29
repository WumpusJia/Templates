#include<cstdio>
#include<cstring>

const int DAYS = 365;
const int MON[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
const char WEEK[][10] = {"\0","monday","tuesday"
    ,"wednesday","thursday","friday","saturday","sunday"};

inline bool Isleap(int y)
{
	return (y%400 == 0 || y%100 && y%4 == 0);
}

inline int leap(int y)	// 1 - y 之间有多少个闰年
{
	if(!y) return 0;
	return y/4 - y/100 + y/400;
}

//year 	[1,]
//mon 	[1,12]
//day 	[1,31]
struct Date{
	int y,m,d;
	Date(int y=0,int m=0,int d=0):y(y),m(m),d(d) {}

	void print()
	{
	//	printf("%d.%d.%d\n",y,m,d);
		printf("%04d/%02d/%02d",y,m,d);
	}

	bool Islegal()
	{
		if(y<1) return false;
		if(m<1 || m>12) return false;
		if(d<1 || d > (MON[m]+ ((Isleap(y) && m==2)?1:0)))
            return false;
		return true;
	}

	int toDay()		//将日期转化为天数
	{
		int res = (y-1) * DAYS + leap(y-1);
		for(int i=1;i<m;++i)
			res += MON[i];
		if(Isleap(y) && m>2) ++res;
		res += d;
		return res;
	}

	bool operator<(const Date& rhs) const
	{
		return (y < rhs.y || m < rhs.m || d < rhs.d);
	}

	int operator-(Date rhs)
	{
		return this->toDay() - rhs.toDay() ;
	}

	Date operator+(const int day);
	Date operator-(const int day);

	int Weekday()	//返回今天为星期几
	{
		Date temp = *(this);
		int ans ;
		if(m == 1 || m == 2) m+=12 , --y;
		if((y < 1752 ) || (y ==1752 && m<9) ||
            (y==1752 && m==9 && d<3))
			ans = (d + 2*m + 3*(m+1)/5 + y + y/4 + 5)%7;
		else
			ans = (d + 2*m + 3*(m+1)/5+y+y/4-y/100+y/400)%7;
		*(this) = temp;
		return ans+1;
	}

};

Date toDate(int day)
{
	Date res(day/(DAYS+1)+1,0,0);
	day -= res.toDay();
	while((!Isleap(res.y) && day > DAYS) ||
        (Isleap(res.y) && day > DAYS+1))
	{
		day -= DAYS + Isleap(res.y) ;
		res.y++;
	}
	res.m = 1;
	while(day - (MON[res.m]+((Isleap(res.y) && res.m==2)?1:0))>0)
	{
	   	day -= MON[res.m] + ((Isleap(res.y) && res.m==2)?1:0);
		++res.m;
	}
	res.d = day;
	return res;
}

Date Date::operator+(const int day)
{
	return toDate(this->toDay() + day);
}

Date Date::operator-(const int day)
{
	return toDate(this->toDay() - day);
}

int main()
{
	int y,m,d;
	//freopen("test.txt","r",stdin);

	return 0;
}
