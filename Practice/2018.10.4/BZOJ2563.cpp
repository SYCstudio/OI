#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int inf=2147483647;

int n,m;
ll W[maxN];

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&W[i]),W[i]*=2ll;
	for (int i=1;i<=m;i++){
		int u,v;ll w;scanf("%d%d%lld",&u,&v,&w);
		W[u]+=w;W[v]+=w;
	}
	sort(&W[1],&W[n+1]);reverse(&W[1],&W[n+1]);
	ll Ans=0;
	for (int i=1,opt=1;i<=n;i++,opt*=-1) Ans=Ans+W[i]*opt;
	printf("%lld\n",Ans/2);
	return 0;
}
/*
4 4
6
4
-1
-2
1 2 1
2 3 6
3 4 3
1 4 5
//*/
