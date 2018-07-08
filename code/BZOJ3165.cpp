#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxNum=40010;
const int Mod=39989;
const int Num=40000;
const int inf=2147483647;

class Line
{
public:
	ld k,b;
	ld calc(ll x){
		return k*x+b;
	}
};

class SegmentData
{
	ll x;ld y;
	Line L;
};

int n;
SegmentData S[maxNum<<4];

int main()
{
	scanf("%d",&n);
	int linecnt=0,lastans=0;
	for (int i=1;i<=n;i++)
	{
		int opt;scanf("%d",&opt);
		if (opt==0)
		{
			int k;scanf("%d",&k);
			k=(k+lastans-1)%Mod+1;
			printf("%d\n",lastans=Query(1,1,Num,k));
		}
		if (opt==1)
		{
			int x0,y0,x1,y1;scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
			x0=(x0+lastans-1)%Mod+1;y0=(y0+lastans-1)%Mod+1;x1=(x1+lastans-1)%Mod+1;y1=(y1+lastans-1)%Mod+1;
		}
	}
}
