#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n,d;
ld X[maxN],Y[maxN];
int A[maxN],Dist[maxN];

ld Cross(ld x1,ld y1,ld x2,ld y2);
ld Slope(int id,ld x,ld y);

int main(){
	scanf("%d%d",&n,&d);
	for (int i=1;i<=n;i++) scanf("%d%d",&A[i],&Dist[i]),A[i]+=A[i-1];
	ld Ans=(ld)A[1]/(ld)Dist[1];
	int top=1;X[1]=d;Y[1]=A[1];
	for (int i=2;i<=n;i++){
		ld x=(ld)1.0*i*d,y=A[i];
		while ((top>=2)&&(Cross(x-X[top-1],y-Y[top-1],X[top]-X[top-1],Y[top]-Y[top-1]))>=0) top--;
		++top;X[top]=x;Y[top]=y;
		x=x+Dist[i];
		int l=2,r=top;
		do{
			int mid=(l+r)>>1;
			if (Slope(mid-1,x,y)<Slope(mid,x,y)) l=mid;
			else r=mid-1;
		}
		while (l+1<r);
		Ans=Ans+Slope(l,x,y);
	}
	printf("%.0LF\n",Ans);return 0;
}

ld Cross(ld x1,ld y1,ld x2,ld y2){
	return x1*y2-x2*y1;
}

ld Slope(int id,ld x,ld y){
	return (Y[id]-y)/(X[id]-x);
}
