#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;
const int F[]={0,1,-1};
const ll INF=1e17;

int n;
int X[maxN],Y[maxN],A[maxN],B[maxN];

ll Calc(int x,int y);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&X[i],&Y[i]);
		A[i]=X[i]+Y[i];B[i]=X[i]-Y[i];
	}
	sort(&A[1],&A[n+1]);sort(&B[1],&B[n+1]);
	int x=A[(n>>1)+1],y=B[(n>>1)+1];
	ll Ans=INF;
	for (int f1=0;f1<3;f1++)
		for (int f2=0;f2<3;f2++)
			if ((((x+F[f1])^(y+F[f2]))&1)==0)
				Ans=min(Ans,Calc(x+F[f1],y+F[f2])/2);
	printf("%lld\n",Ans);
	return 0;
}

ll Calc(int x,int y)
{
	ll Ret=0;
	for (int i=1;i<=n;i++) Ret=Ret+(ll)abs(A[i]-x)+(ll)abs(B[i]-y);
	return Ret;
}
