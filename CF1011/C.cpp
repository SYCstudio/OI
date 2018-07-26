#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const ld eps=1e-8;
const int inf=2147483647;

int n,m;
int A[maxN],B[maxN];

bool Check(ld fuel);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]);
	for (int i=1;i<=n;i++) scanf("%d",&B[i]);

	ld L=0,R=1e9,Ans=-1;
	do{
		ld mid=(L+R)/2.0;
		if (Check(mid)) Ans=mid,R=mid-eps;
		else L=mid+eps;
	}
	while (L+eps<R);

	if (Ans==-1) printf("-1\n");
	else printf("%.10LF\n",Ans);
	return 0;
}

bool Check(ld fuel){
	//printf("%.10LF\n",fuel);
	fuel=fuel-(fuel+m)/(ld)A[1];
	if (fuel<0) return 0;
	for (int i=2;i<=n;i++){
		fuel=fuel-(fuel+m)/(ld)B[i];
		if (fuel<0) return 0;
		fuel=fuel-(fuel+m)/(ld)A[i];
		if (fuel<0) return 0;
	}
	fuel=fuel-(fuel+m)/(ld)B[1];
	if (fuel<0) return 0;
	return 1;
}
