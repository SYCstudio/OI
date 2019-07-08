#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=505000;
const int maxM=2020000;
const int inf=2000000000;

int n,m,K,NW[maxN];
int ecnt=-1,Hd[maxN],Nt[maxM],V[maxM];
int dfncnt,dfn[maxN],low[maxN],St[maxN],top=0,inq[maxN],bcccnt,Bcc[maxN];
int Mnid[maxN],Mark[maxN],Dg[maxN];
int Sorter[maxN];

void tarjan(int u);
int main(){
    memset(Hd,-1,sizeof(Hd));
    scanf("%d%d%d",&n,&m,&K);NW[0]=inf;
    for (int i=1;i<=n;i++) scanf("%d",&NW[i]);
    for (int i=1;i<=m;i++){
	int u,v;scanf("%d%d",&u,&v);
	Nt[++ecnt]=Hd[u];Hd[u]=ecnt;V[ecnt]=v;
    }

    for (int i=1;i<=n;i++) if (!dfn[i]) tarjan(i);
    for (int i=1;i<=n;i++)
	for (int j=Hd[i];j!=-1;j=Nt[j])
	    if (Bcc[i]!=Bcc[V[j]]) ++Dg[Bcc[V[j]]];
    for (int i=1;i<=bcccnt;i++) if (Dg[i]==0) Mark[Mnid[i]]=1;
    //for (int i=1;i<=bcccnt;i++) cout<<Mnid[i]<<" ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<Bcc[i]<<" ";cout<<endl;

    int scnt=0;
    for (int i=1;i<=n;i++) if (!Mark[i]) Sorter[++scnt]=NW[i];
    sort(&Sorter[1],&Sorter[scnt+1]);reverse(&Sorter[1],&Sorter[scnt+1]);
    long long Ans=0;
    for (int i=1;i<=min(K,scnt);i++) Ans=Ans+Sorter[i];
    printf("%lld\n",Ans);return 0;
}
void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;St[++top]=u;inq[u]=1;
    for (int i=Hd[u];i!=-1;i=Nt[i]){
	int v=V[i];
	if (!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
	else if (inq[v]) low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u]){
	int v;++bcccnt;Mnid[bcccnt]=0;
	do{
	    v=St[top--];Bcc[v]=bcccnt;inq[v]=0;
	    if (NW[Mnid[bcccnt]]>NW[v]) Mnid[bcccnt]=v;
	}
	while (u!=v);
    }
    return;
}
