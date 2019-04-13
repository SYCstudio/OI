#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxN=303000;
const int maxM=maxN<<1;
const ll INF=1e18;

int n,m;
int ecnt=-1,Hd[maxN],Nt[maxM],V[maxM],W[maxM],Fa[maxN];
int Seq[maxN],Mk[maxN];
ll Mx=-INF,Pre=-INF,Sm[maxN];

void Add_Edge(int u,int v,int w);
void dfs(int u,int fa);
void dfs1(int u,int fa,ll sum,int dep);
void dfs2(int u,int fa,ll sum);
int main(){
    scanf("%d%d",&n,&m);memset(Hd,-1,sizeof(Hd));
    for (int i=1;i<n;i++){
	int u,v,w;scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    dfs(1,0);
    int now=n,scnt=0;while (now) Mk[Seq[++scnt]=now]=1,now=Fa[now];
    reverse(&Seq[1],&Seq[scnt+1]);
    for (int i=1;i<=scnt;i++){
	Mx=max(Mx,Pre-Sm[Seq[i]]);
	if (i>=2) Pre=max(Pre,Sm[Seq[i-1]]);int cnt=0;
	for (int j=Hd[Seq[i]];j!=-1;j=Nt[j]) if (!Mk[V[j]]) dfs1(V[j],Seq[i],W[j]-Sm[Seq[i]],1),++cnt;
	if (cnt>=2) Mx=max(Mx,INF);
	for (int j=Hd[Seq[i]];j!=-1;j=Nt[j]) if (!Mk[V[j]]) dfs2(V[j],Seq[i],W[j]+Sm[Seq[i]]);
    }
    //cout<<Mx<<endl;
    while (m--){
	int X;scanf("%d",&X);
	printf("%lld\n",min(Sm[Seq[scnt]],Sm[Seq[scnt]]+X+Mx));
    }
    return 0;
}
void Add_Edge(int u,int v,int w){
    Nt[++ecnt]=Hd[u];Hd[u]=ecnt;V[ecnt]=v;W[ecnt]=w;return;
}
void dfs(int u,int fa){
    for (int i=Hd[u];i!=-1;i=Nt[i]) if (V[i]!=fa) Fa[V[i]]=u,Sm[V[i]]=Sm[u]+W[i],dfs(V[i],u);return;
}
void dfs1(int u,int fa,ll sum,int dep){
    Mx=max(Mx,Pre+sum);int cnt=0;if (dep>=2) Mx=max(Mx,INF);
    for (int i=Hd[u];i!=-1;i=Nt[i]) if (V[i]!=fa) dfs1(V[i],u,sum+W[i],dep+1),++cnt;
    if (cnt>=2) Mx=max(Mx,INF);
    return;
}
void dfs2(int u,int fa,ll sum){
    Pre=max(Pre,sum);
    for (int i=Hd[u];i!=-1;i=Nt[i]) if (V[i]!=fa) dfs2(V[i],u,sum+W[i]);
    return;
}
