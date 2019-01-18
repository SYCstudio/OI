#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxM=maxN<<1;

int n;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int rcnt=0,Ring[maxN],Fa[maxN];
int vis[maxN],Qp[maxN];
ll W[maxM],Rw[maxN],F[maxN],Qk[maxN],dp[maxN];

void Add_Edge(int u,int v,ll w);
void dfs(int u,int fa);
void dfsmx(int u,int fa,ll &mx);

int main(){
    //freopen("in","r",stdin);
    scanf("%d",&n);mem(Head,-1);
    for (int i=1;i<=n;i++){
	int v,w;scanf("%d%d",&v,&w);
	Add_Edge(i,v,w);Add_Edge(v,i,w);
    }
    ll Ans=0;
    for (int i=1;i<=n;i++)
	if (vis[i]==0){
	    rcnt=0;dfs(i,edgecnt+10);ll mx=0;
	    for (int i=1;i<=rcnt;i++) vis[Ring[i]]=2,Rw[i]=0;
	    for (int i=1;i<=rcnt;i++){
		dfsmx(Ring[i],0,mx);
		F[i]=dp[Ring[i]];
	    }
	    for (int i=1;i<=rcnt;i++) Ring[i+rcnt]=Ring[i];
	    for (int i=1;i<=rcnt;i++)
		for (int j=Head[Ring[i]];j!=-1;j=Next[j])
		    if (V[j]==Ring[i+1]) Rw[i]=max(Rw[i],W[j]);
	    for (int i=1;i<=rcnt;i++) Rw[i+rcnt]=Rw[i],F[i+rcnt]=F[i],mx=max(mx,F[i]);

	    //for (int i=1;i<=rcnt;i++) cout<<Ring[i]<<" ";cout<<endl;
	    //for (int i=1;i<=rcnt;i++) cout<<Rw[i]<<" ";cout<<endl;
	    //for (int i=1;i<=rcnt;i++) cout<<F[i]<<" ";cout<<endl;
	    
	    int ql=1,qr=0;ll sum=0;
	    for (int i=1;i<rcnt+rcnt;i++){
		while (ql<=qr&&Qp[ql]<i-rcnt+1) ql++;
		if (ql<=qr) mx=max(mx,F[i]+Qk[ql]+sum);
		while (ql<=qr&&Qk[qr]+sum<=F[i]) --qr;
		++qr;Qk[qr]=F[i]-sum;Qp[qr]=i;
		sum+=Rw[i];
	    }

	    //cout<<mx<<endl;
	    Ans+=mx;
	}
    printf("%lld\n",Ans);return 0;
}
void Add_Edge(int u,int v,ll w){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
    return;
}
void dfs(int u,int faw){
    Fa[u]=V[faw^1];vis[u]=1;
    for (int i=Head[u];i!=-1;i=Next[i])
	if (i!=(faw^1)){
	    if (vis[V[i]]==0) dfs(V[i],i);
	    else if (rcnt==0){
		int now=u;Ring[rcnt=1]=now;
		while (now!=V[i]) Ring[++rcnt]=now=Fa[now];
	    }
	}
    return;
}
void dfsmx(int u,int fa,ll &mx){
    dp[u]=0;
    for (int i=Head[u];i!=-1;i=Next[i])
	if (V[i]!=fa&&vis[V[i]]!=2){
	    dfsmx(V[i],u,mx);mx=max(mx,dp[u]+dp[V[i]]+W[i]);
	    dp[u]=max(dp[u],dp[V[i]]+W[i]);
	}
    mx=max(mx,dp[u]);
    return;
}

