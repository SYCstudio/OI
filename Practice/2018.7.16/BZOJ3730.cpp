#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG 
#define IL inline

const int maxN=101000;
const int maxM=maxN<<1;
const int maxBit=18;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Val[maxN];
int root,nowsum,Size[maxN],MxSon[maxN],Fa[maxN];
bool vis[maxN];
int nodecnt,rt1[maxN],rt2[maxN];
//SegmentData S[maxN*100];
int Ssum[maxN*100],Sls[maxN*100],Srs[maxN*100];

IL int Input();
IL void Add_Edge(RG int u,RG int v);
//void dfs_fa(int u,int fa);
void dfs_root(RG int u,RG int fa);
void Divide(RG int u);
void Modify_Seg(int &now,RG int l,RG int r,RG int pos,RG int key);
int Query_Seg(RG int now,RG int l,RG int r,RG int ql,RG int qr);
//IL int Dist(RG int u,RG int v);
IL void Modify(RG int u,RG int key);
IL int Query(RG int u,RG int dist);

namespace Chain
{
	int Size[maxN],Top[maxN],Hson[maxN],Fa[maxN],Depth[maxN];

	void dfs1(RG int u,RG int fa);
	void dfs2(RG int u,RG int top);
	IL int Dist(RG int u,RG int v);
}

int main()
{
	mem(Head,-1);
	n=Input();m=Input();//scanf("%d%d",&n,&m);
	RG int i,u,v,lastans,opt,x,y;
	for (i=1;i<=n;++i) Val[i]=Input();//scanf("%d",&Val[i]);
	for (i=1;i<n;++i)
	{
		u=Input(),v=Input();//scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}

	Chain::Depth[1]=1;
	Chain::dfs1(1,1);
	Chain::dfs2(1,1);
	
	root=0;MxSon[0]=inf;nowsum=n;
	dfs_root(1,1);
	Divide(root);

	//for (int i=1;i<=n;i++) cout<<Fa[i]<<" ";cout<<endl;

	for (i=1;i<=n;++i) Modify(i,Val[i]);

	//cout<<Query_Seg(rt1[5],0,n-1,0,0)<<" "<<Query_Seg(rt1[5],0,n-1,0,1)<<" "<<Query_Seg(rt1[5],0,n-1,0,2)<<" "<<Query_Seg(rt1[5],0,n-1,0,3)<<endl;
	while (m--)
	{
		opt=Input();x=Input()^lastans;y=Input()^lastans;//scanf("%d",&opt);
		if (opt==0) printf("%d\n",lastans=Query(x,y));
		else{
			Modify(x,y-Val[x]);Val[x]=y;
		}
	}
	return 0;
}

IL int Input()
{
	RG int x=0;RG char ch=getchar();
	while ((ch>'9')||(ch<'0')) ch=getchar();
	while ((ch>='0')&&(ch<='9')) x=x*10+ch-48,ch=getchar();
	return x;
}

IL void Add_Edge(RG int u,RG int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

/*
void dfs_fa(int u,int fa){
	Seq[0][++dfncnt]=u;fst[u]=dfncnt;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Depth[V[i]]=Depth[u]+1;
			dfs_fa(V[i],u);
			Seq[0][++dfncnt]=u;
		}
	lst[u]=dfncnt;
	return;
}
//*/

void dfs_root(RG int u,RG int fa)
{
	Size[u]=1;MxSon[u]=0;
	for (RG int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)){
			dfs_root(V[i],u);
			Size[u]+=Size[V[i]];MxSon[u]=max(MxSon[u],Size[V[i]]);
		}
	MxSon[u]=max(MxSon[u],nowsum-Size[u]);
	if (MxSon[root]>MxSon[u]) root=u;
	//cout<<"dfs_root:"<<u<<" "<<Size[u]<<" "<<MxSon[u]<<" "<<nowsum<<endl;
	return;
}

void Divide(RG int u)
{
	//cout<<"Divide:"<<u<<endl;
	vis[u]=1;
	for (RG int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			root=0;nowsum=Size[V[i]];
			dfs_root(V[i],V[i]);
			Fa[root]=u;
			Divide(root);
		}
	return;
}

void Modify_Seg(int &now,RG int l,RG int r,RG int pos,RG int key){
	if (now==0) now=++nodecnt;
	Ssum[now]+=key;
	RG int node=now,mid;
	while (l!=r)
	{
		mid=(l+r)>>1;
		if (pos<=mid){
			if (Sls[node]==0) Sls[node]=++nodecnt;
			node=Sls[node];r=mid;
		}
		else{
			if (Srs[node]==0) Srs[node]=++nodecnt;
			node=Srs[node];l=mid+1;
		}
		Ssum[node]+=key;
	}
	return;
}

int Query_Seg(RG int now,RG int l,RG int r,RG int ql,RG int qr){
	if (now==0) return 0;
	if (Ssum[now]==0) return 0;
	if ((l==ql)&&(r==qr)) return Ssum[now];
	RG int mid=(l+r)>>1;
	if (qr<=mid) return Query_Seg(Sls[now],l,mid,ql,qr);
	else if (ql>=mid+1) return Query_Seg(Srs[now],mid+1,r,ql,qr);
	else return Query_Seg(Sls[now],l,mid,ql,mid)+Query_Seg(Srs[now],mid+1,r,mid+1,qr);
}

/*
IL int Dist(RG int u,RG int v)
{
	RG int lca,l=min(fst[u],fst[v]),r=max(lst[u],lst[v]);
	RG int lg=Log[r-l+1];
	if (Depth[Seq[lg][l]]<=Depth[Seq[lg][r-(1<<lg)+1]]) lca=Seq[lg][l];
	else lca=Seq[lg][r-(1<<lg)+1];
	//cout<<"GetLca:"<<u<<" "<<v<<" "<<lca<<"["<<Seq[lg][l]<<" "<<Seq[lg][r-(1<<lg)+1]<<"]"<<endl;

	//cout<<"GetDist:"<<uu<<" "<<vv<<" "<<lca<<" "<<Depth[uu]+Depth[vv]-2*Depth[lca]<<endl;

	return Depth[u]+Depth[v]-2*Depth[lca];
}
//*/

IL void Modify(RG int u,RG int key)
{
	Modify_Seg(rt1[u],0,n-1,0,key);
	RG int now=u,d;
	while (Fa[now]!=0)
	{
		d=Chain::Dist(Fa[now],u);
		Modify_Seg(rt1[Fa[now]],0,n-1,d,key);
		Modify_Seg(rt2[now],0,n-1,d,key);
		now=Fa[now];
	}
	return;
}

IL int Query(RG int u,RG int dist)
{
	dist=min(dist,n);
	RG int ret=Query_Seg(rt1[u],0,n-1,0,dist),now=u,d;
	while (Fa[now]!=0)
	{
		d=Chain::Dist(Fa[now],u);
		if (d>dist){
			now=Fa[now];continue;
		}
		ret+=Query_Seg(rt1[Fa[now]],0,n-1,0,dist-d);
		ret-=Query_Seg(rt2[now],0,n-1,0,dist-d);
		now=Fa[now];
	}
	return ret;
}


namespace Chain
{
	void dfs1(RG int u,RG int fa)
	{
		Size[u]=1;Hson[u]=0;
		for (RG int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=fa){
				Depth[V[i]]=Depth[u]+1;Fa[V[i]]=u;
				dfs1(V[i],u);
				Size[u]+=Size[V[i]];
				if (Size[V[i]]>Size[Hson[u]]) Hson[u]=V[i];
			}
		return;	
	}

	void dfs2(RG int u,RG int top)
	{
		Top[u]=top;
		if (Hson[u]==0) return;
		dfs2(Hson[u],top);
		for (RG int i=Head[u];i!=-1;i=Next[i])
			if ((V[i]!=Fa[u])&&(V[i]!=Hson[u]))
				dfs2(V[i],V[i]);
		return;
	}

	int Dist(RG int u,RG int v)
	{
		RG int uu=u,vv=v;
		while (Top[u]!=Top[v])
		{
			if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
			u=Fa[Top[u]];
		}
		if (Depth[u]>Depth[v]) swap(u,v);
		return Depth[uu]+Depth[vv]-2*Depth[u];
	}
}

/*
8 1
1 10 100 1000 10000 100000 1000000 10000000
1 2
1 3
2 4
2 5
3 6
3 7
3 8
0 3 1

9 9
1 5 6 4 7 3 9 10 2
1 2
2 3
2 4
1 5
5 6
5 7
7 8
8 9
0 5 4
0 7 2
0 8 1
0 1 2
1 1 4
0 1 0
0 1 1
1 5 2
0 3 2
//*/


