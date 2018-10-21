#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define IL inline

const int maxN=201000;
const int inf=2147483647;

class Point
{
public:
	ld x,y;
};

int n;
Point P[maxN],Bp[maxN];

ld Solve(int l,int r);
IL ld Dist(Point A,Point B);
IL bool cmpx(Point A,Point B);
IL bool cmpy(Point A,Point B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lf%lf",&P[i].x,&P[i].y);
	sort(&P[1],&P[n+1],cmpx);
	printf("%.6lf\n",Solve(1,n));
	return 0;
}

ld Solve(int l,int r){
	if (r-l+1<=2) return inf;
	if (r-l+1==3) return Dist(P[l],P[l+1])+Dist(P[l],P[l+2])+Dist(P[l+1],P[l+2]);
	int mid=(l+r)>>1;
	ld ret=min(Solve(l,mid),Solve(mid+1,r));
	int bcnt=0;
	for (int i=l;i<=r;i++) if (fabs(P[i].x-P[mid].x)*2<=ret) Bp[++bcnt]=P[i];
	sort(&Bp[1],&Bp[bcnt+1],cmpy);
	for (int i=1;i<=bcnt;i++)
		for (int j=i+1;(j<=bcnt)&&(Dist(Bp[i],Bp[j])*2<=ret);j++)
			for (int k=j+1;k<=bcnt;k++)
				ret=min(ret,Dist(Bp[i],Bp[j])+Dist(Bp[i],Bp[k])+Dist(Bp[j],Bp[k]));
	return ret;
}

IL ld Dist(Point A,Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

IL bool cmpx(Point A,Point B){
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}

IL bool cmpy(Point A,Point B){
	if (A.y!=B.y) return A.y<B.y;
	return A.x<B.x;
}

