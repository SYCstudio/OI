#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=510;
const int maxM=150000<<1;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int ufs[maxN],match[maxN],pre[maxN],label[maxN],ql,qr,Qu[maxN];
int tim,Tim[maxN];

void Add_Edge(int u,int v);
int find(int x);
int bfs(int S);
int LCA(int u,int v);
void Link(int x,int y,int lca);
int main()
{
	//freopen("in","r",stdin);
	scanf("%d%d",&n,&m);
	mem(Head,-1);
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	int Ans=0;
	for (int i=1; i<=n; i++) if (!match[i]) Ans+=bfs(i);
	printf("%d\n",Ans);
	for (int i=1; i<=n; i++) printf("%d ",match[i]);
	printf("\n");
	return 0;
}
void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
int find(int x)
{
	if (ufs[x]!=x) ufs[x]=find(ufs[x]);
	return ufs[x];
}
int bfs(int S)
{
	//cout<<"Bfs:"<<S<<endl;
	for (int i=1; i<=n; i++) ufs[i]=i,label[i]=0,pre[i]=0;
	label[Qu[ql=qr=1]=S]=1;
	while (ql<=qr)
		for (int u=Qu[ql++],i=Head[u]; i!=-1; i=Next[i]) {
			if (find(u)==find(V[i])||label[V[i]]==2) continue;
			int v=V[i];
			if (!label[v]) {
				if (!match[v]) {
					int now=u,lst=v;
					while (now) {
						int tmp=match[now];
						match[now]=lst;
						match[lst]=now;
						lst=tmp;
						now=pre[lst];
					}
					return 1;
				}
				label[v]=2;
				label[match[v]]=1;
				pre[v]=u;
				Qu[++qr]=match[v];
			} else {
				//cout<<"Getlca:"<<u<<" "<<v<<endl;
				int lca=LCA(u,v);
				Link(u,v,lca);
				Link(v,u,lca);
			}
		}
	return 0;
}
int LCA(int u,int v)
{
	++tim;
	u=find(u);
	v=find(v);
	while (Tim[u]!=tim) {
		Tim[u]=tim;
		u=find(pre[match[u]]);
		//cout<<u<<" "<<v<<endl;
		if (v) swap(u,v);
		if (!u&&!v) exit(1);
	}
	return u;
}
void Link(int x,int y,int lca)
{
	while (find(x)!=lca) {
		pre[x]=y;
		y=match[x];
		if (label[y]==2) Qu[++qr]=y,label[y]=1;
		if (find(x)==x) ufs[x]=lca;
		if (find(y)==y) ufs[y]=lca;
		x=pre[y];
	}
	return;
}