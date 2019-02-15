#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=101000;
const int inf=2147483647;
const ll INF=1e18;

int n,m;
ll Ht[maxN];
int size,Bl[maxN],L[maxN],R[maxN];
ll Slope[maxN],Mx[maxN],Mxp[maxN],pls[maxN],frt[maxN];

IL void Reset(RG int id,RG int opt);

int main(){
	//freopen("1.in","r",stdin);freopen("out","w",stdout);
	RG int i,opt,l,r,bl,br;
	RG ll Ans,t;
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;++i) scanf("%lld",&Ht[i]);
	size=sqrt(n);
	for (i=1;i<=n;++i){
		Bl[i]=i/size+1;
		if (L[Bl[i]]==0) L[Bl[i]]=i;
		R[Bl[i]]=i;
	}
	for (i=1;i<=size;++i) Reset(i,0);
	while (m--){
		scanf("%d%d%d",&opt,&l,&r);
		if (opt==1){
			Ans=0;bl=Bl[l];br=Bl[r];
			if (bl!=br){
				Reset(bl,1);Reset(br,1);
				for (i=l;i<=R[bl];i+=4){
					Ans=max(Ans,Ht[i]+pls[bl]*i-frt[bl]);
					if (i+1<=R[bl]) Ans=max(Ans,Ht[i+1]+pls[bl]*(i+1)-frt[bl]);
					if (i+2<=R[bl]) Ans=max(Ans,Ht[i+2]+pls[bl]*(i+2)-frt[bl]);
					if (i+3<=R[bl]) Ans=max(Ans,Ht[i+3]+pls[bl]*(i+3)-frt[bl]);
				}
				for (i=L[br];i<=r;i+=4){
					Ans=max(Ans,Ht[i]+pls[br]*i-frt[br]);
					if (i+1<=r) Ans=max(Ans,Ht[i+1]+pls[br]*(i+1)-frt[br]);
					if (i+2<=r) Ans=max(Ans,Ht[i+2]+pls[br]*(i+2)-frt[br]);
					if (i+3<=r) Ans=max(Ans,Ht[i+3]+pls[br]*(i+3)-frt[br]);
				}
				for (i=bl+1;i<=br-1;++i){
					if (pls[i]>Slope[i]) Reset(i,0);
					Ans=max(Ans,Mx[i]+pls[i]*Mxp[i]-frt[i]);
				}
			}
			else{
				Reset(bl,1);
				for (i=l;i<=r;++i) Ans=max(Ans,Ht[i]+pls[bl]*i-frt[bl]);
			}
			printf("%lld\n",max(0ll,Ans-(Ht[1]+pls[1]-frt[1])));
		}
		if (opt==2){
			Reset(Bl[l],1);Reset(Bl[r],1);
			swap(Ht[l],Ht[r]);
			Reset(Bl[l],0);Reset(Bl[r],0);
		}
		if (opt==3){
			scanf("%lld",&t);bl=Bl[l];br=Bl[r];
			if (bl!=br){
				for (i=l;i<=R[bl];++i) Ht[i]=Ht[i]+t*(i-l+1);
				for (i=L[br];i<=r;++i) Ht[i]=Ht[i]+t*(i-l+1);
				Reset(bl,0);Reset(br,0);
				for (i=bl+1;i<=br-1;++i){
					pls[i]+=t;frt[i]+=t*(l-1);
				}
			}
			else{
				for (i=l;i<=r;++i) Ht[i]=Ht[i]+t*(i-l+1);
				Reset(bl,0);
			}
		}
	}
	return 0;
}

IL void Reset(RG int id,RG int opt){
	if ((opt)&&(pls[id]==0)&&(frt[id]==0)) return;
	RG int i;
	Slope[id]=INF;Mx[id]=0;Mxp[id]=0;
	for (i=L[id];i<=R[id];i+=4){
		Ht[i]=Ht[i]+pls[id]*i-frt[id];
		if (i+1<=R[id]) Ht[i+1]=Ht[i+1]+pls[id]*(i+1)-frt[id];
		if (i+2<=R[id]) Ht[i+2]=Ht[i+2]+pls[id]*(i+2)-frt[id];
		if (i+3<=R[id]) Ht[i+3]=Ht[i+3]+pls[id]*(i+3)-frt[id];
	}
	pls[id]=frt[id]=0;
	for (i=L[id];i<=R[id];++i)
		if (Ht[i]>=Mx[id]) Mx[id]=Ht[i],Mxp[id]=i,Slope[id]=INF;
		else Slope[id]=min(Slope[id],(Mx[id]-Ht[i])/(i-Mxp[id]));
	return;
}
