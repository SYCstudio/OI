#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const int maxM=100100;
const int inf=2147483647;

class Edge
{
public:
	int u,v,w,opt;
};

int n,m,K;
Edge E[maxM];
int UFS[maxN];
int mst;

int Calc(int val);
int Find(int x);
bool cmp(Edge A,Edge B);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	int mxW=0;
	for (int i=1;i<=m;i++) scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].w,&E[i].opt),mxW=max(mxW,E[i].w),E[i].u++,E[i].v++;
	int L=-mxW,R=mxW,Ans=-1;
	do{
		int mid=(L+R)>>1;
		if (Calc(mid)>=K) Ans=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);

	Calc(Ans);
	printf("%d\n",mst-K*Ans);

	return 0;
}

int Calc(int val){
	for (int i=1;i<=m;i++) if (E[i].opt==0) E[i].w+=val;
	for (int i=1;i<=n;i++) UFS[i]=i;
	sort(&E[1],&E[m+1],cmp);mst=0;
	int cnt=0;
	for (int i=1;i<=m;i++)
		if (Find(E[i].u)!=Find(E[i].v)){
			mst+=E[i].w;cnt+=(E[i].opt==0);
			UFS[Find(E[i].u)]=Find(E[i].v);
		}
	for (int i=1;i<=m;i++) if (E[i].opt==0) E[i].w-=val;
	return cnt;
}

int Find(int x){
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}

bool cmp(Edge A,Edge B){
	if (A.w!=B.w) return A.w<B.w;
	else return A.opt<B.opt;
}
