#include<bits/stdc++.h>
using namespace std;

const int maxN=505000;
const int maxM=maxN<<1;

int n,m;
int ecnt=-1,Hd[maxN],Nt[maxM],V[maxM],Mark[maxN],ring,scnt,Seq[maxN],Dg[maxN],Qu[maxN];
pair<int,int> E[maxN];

void Add_Edge(int u,int v);
void dfs_init(int u,int fa);
int main(){
    scanf("%d%d",&n,&m);memset(Hd,-1,sizeof(Hd));
    for (int i=1;i<=m;i++){
	int u,v;scanf("%d%d",&u,&v);Add_Edge(u,v);Add_Edge(v,u);++Dg[u];++Dg[v];
    }
    int ocnt=0;
    for (int i=1;i<=n;i++)
	if (!Mark[i]){
	    ring=scnt=0;dfs_init(i,i);
	    if (!ring){
		for (int j=1;j<=scnt;j++) if (Dg[Seq[j]]==1) E[++ocnt]=make_pair(Seq[j],V[Hd[Seq[j]]]);
		continue;
	    }
	    int ql=1,qr=0;
	    for (int j=1;j<=scnt;j++) if (Dg[Seq[j]]==1) Qu[++qr]=Seq[j],Mark[Seq[j]]=2;
	    while (ql<=qr) for (int u=Qu[ql++],i=Hd[u];i!=-1;i=Nt[i]) if ((--Dg[V[i]])==1) Mark[Qu[++qr]=V[i]]=2;
	    for (int j=1;j<=scnt;j++) if (Mark[Seq[j]]==1) for (int k=Hd[Seq[j]];k!=-1;k=Nt[k]) if (Mark[V[k]]==2) E[++ocnt]=make_pair(Seq[j],V[k]);
	}
    sort(&E[1],&E[ocnt+1]);
    printf("%d\n",ocnt);
    for (int i=1;i<=ocnt;i++) printf("%d %d\n",E[i].first,E[i].second);

    return 0;
}
void Add_Edge(int u,int v){
    Nt[++ecnt]=Hd[u];Hd[u]=ecnt;V[ecnt]=v;return;
}
void dfs_init(int u,int fa){
    Mark[u]=1;Seq[++scnt]=u;
    for (int i=Hd[u];i!=-1;i=Nt[i])
	if (V[i]!=fa){
	    if (Mark[V[i]]) ring=1;
	    else dfs_init(V[i],u);
	}
    return;
}
