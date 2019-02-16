#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;
const ll INF=1e18;

int n,m;
ll Ht[maxN];
int size,Bl[maxN],L[maxN],R[maxN];
ll Slope[maxN],Mx[maxN],Mxp[maxN],pls[maxN],frt[maxN];

void Reset(int bk);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&Ht[i]);
	size=sqrt(n);
	for (int i=1;i<=n;i++){
		Bl[i]=i/size+1;
		if (L[Bl[i]]==0) L[Bl[i]]=i;
		R[Bl[i]]=i;
	}
	for (int i=1;i<=size;i++) Reset(i);
	while (m--){
		int opt,l,r;scanf("%d%d%d",&opt,&l,&r);
		if (opt==1){
			ll Ans=0;
			int bl=Bl[l],br=Bl[r];
			if (bl!=br){
				for (int i=l;i<=R[bl];i++) Ans=max(Ans,Ht[i]+pls[bl]*i-frt[bl]);
				for (int i=L[br];i<=r;i++) Ans=max(Ans,Ht[i]+pls[br]*i-frt[br]);
				for (int i=bl+1;i<=br-1;i++){
					if (pls[i]>Slope[i]) Reset(i);
					Ans=max(Ans,Mx[i]+pls[i]*Mxp[i]-frt[i]);
				}
			}
			else{
				Reset(bl);
				for (int i=l;i<=r;i++) Ans=max(Ans,Ht[i]+pls[bl]*i-frt[bl]);
			}
			printf("%lld\n",max(0ll,Ans-(Ht[1]+pls[1]-frt[1])));
		}
		if (opt==2){
			Reset(Bl[l]);Reset(Bl[r]);
			swap(Ht[l],Ht[r]);
			Reset(Bl[l]);Reset(Bl[r]);
		}
		if (opt==3){
			ll t;scanf("%lld",&t);
			int bl=Bl[l],br=Bl[r];
			if (bl!=br){
				Reset(bl);Reset(br);
				for (int i=l;i<=R[bl];i++) Ht[i]=Ht[i]+t*(i-l+1);
				for (int i=L[br];i<=r;i++) Ht[i]=Ht[i]+t*(i-l+1);
				Reset(bl);Reset(br);
				for (int i=bl+1;i<=br-1;i++){
					pls[i]+=t;frt[i]-=t*(l-1);
				}
			}
			else{
				Reset(bl);
				for (int i=l;i<=r;i++) Ht[i]=Ht[i]+t*(i-l+1);
				Reset(bl);
			}
		}
	}
	return 0;
}

void Reset(int id){
	Slope[id]=INF;Mx[id]=0;Mxp[id]=0;
	for (int i=L[id];i<=R[id];i++)
		Ht[i]=Ht[i]+pls[id]*i-frt[id];
	pls[id]=frt[id]=0;
	for (int i=L[id];i<=R[id];i++)
		if (Ht[i]>=Mx[id]) Mx[id]=Ht[i],Mxp[id]=i,Slope[id]=INF;
		else Slope[id]=min(Slope[id],(Mx[id]-Ht[i])/(Mxp[id]-i));
	return;
}
