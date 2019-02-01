#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define RG register

const int maxN=18;
const int maxS=14348910;

int n,m,Seq[maxN],apr[maxN];
int F[maxS],pw[maxN];
int vis[maxN],L[maxN];

int main(){
    RG int i,S,Ans=0,iS,cnt,zero,lst,frt,nS,x,lcnt,l;
    pw[0]=1;for (i=1;i<maxN;++i) pw[i]=pw[i-1]*3;
    scanf("%d%d",&n,&m);for (i=1;i<=m;++i) scanf("%d",&Seq[i]),--Seq[i],apr[Seq[i]]=i;
    F[0]=1;
    for (int S=0;S<pw[n];S++){
	if (!F[S]) continue;
	cnt=lcnt=0;
	for (i=0,x=S;i<n;++i){
	    vis[i]=x%3;x/=3;
	    if (vis[i]) ++cnt;
	    if (vis[i]==1) L[++lcnt]=i;
	}
	if (cnt==n){
	    Ans+=F[S];continue;
	}
	for (i=0,l=1;i<n;++i){
	    if (vis[i]) continue;
	    if (apr[i]>=2&&!vis[Seq[apr[i]-1]]) continue;
	    while (l<=lcnt&&L[l]<i) ++l;
	    if (l>m) continue;
	    nS=S+pw[i];
	    if (l<=lcnt) nS+=pw[L[l]];
	    F[nS]+=F[S];
	}
    }
    printf("%d\n",Ans);return 0;
}
