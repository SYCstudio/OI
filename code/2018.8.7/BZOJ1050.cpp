#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int maxM=5010;
const int inf=2147483647;

class Edge
{
public:
	int u,v,w;
};

int n,m,S,T;
Edge E[maxM];
int UFS[maxN];

bool cmp(Edge A,Edge B);
int Find(int u);
ll gcd(ll a,ll b);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	scanf("%d%d",&S,&T);
	sort(&E[1],&E[m+1],cmp);

	ld Ans=inf;
	ll fm,fz;
	for (int i=1;i<=m;i++){
		for (int j=1;j<=n;j++) UFS[j]=j;
		int p;
		for (p=i;p<=m;p++){
			if (Find(E[p].u)!=Find(E[p].v)){
				UFS[Find(E[p].u)]=Find(E[p].v);
			}
			if (Find(S)==Find(T)) break;
		}
		if (Find(S)==Find(T)){
			if (Ans>(ld)E[p].w/(ld)E[i].w){
				Ans=(ld)E[p].w/(ld)E[i].w;
				fz=E[p].w;fm=E[i].w;
			}
		}
		else break;
	}

	if (Ans==inf) printf("IMPOSSIBLE\n");
	else{
		int d=gcd(fm,fz);
		fm/=d;fz/=d;
		if (fm==1) printf("%lld\n",fz);
		else printf("%lld/%lld\n",fz,fm);
	}

	return 0;
}

bool cmp(Edge A,Edge B){
	return A.w<B.w;
}

int Find(int u){
	if (UFS[u]!=u) UFS[u]=Find(UFS[u]);
	return UFS[u];
}

ll gcd(ll a,ll b){
	ll t;
	while (a) t=a,a=b%a,b=t;
	return b;
}
