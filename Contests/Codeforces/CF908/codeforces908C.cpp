#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))

const int maxN=1010;
const int inf=2147483647;
const ld eps=1e-12;

int n;
ld R;
ld X[maxN];
ld Y[maxN];

bool Check(ld mid,int id);

int main()
{
	scanf("%d%LF",&n,&R);
	for (int i=1;i<=n;i++) scanf("%LF",&X[i]);
	Y[1]=R;
	//cout<<"2r:"<<2*r<<endl;
	for (int i=2;i<=n;i++)
	{
		ld l=0,r=3000000;
		for (int j=1;j<i;j++)
			if (abs(X[i]-X[j])<=2*R)
				l=max(l,Y[j]);
		ld Ans;
		do
		{
			ld mid=(l+r)/2;
			if (Check(mid,i))
			{
				r=mid-eps;
				Ans=mid;
			}
			else l=mid+eps;
		}
		while (l<=r);
		Y[i]=Ans;
		//cout<<"Ans:"<<Ans<<endl;
	}
	for (int i=1;i<=n;i++) printf("%.10LF ",Y[i]);
	printf("\n");
	return 0;
}

bool Check(ld mid,int id)
{
	for (int i=1;i<id;i++)
		if (sqr(X[i]-X[id])+sqr(Y[i]-mid)<=sqr(R*2.0)) return 0;
	return 1;
}
