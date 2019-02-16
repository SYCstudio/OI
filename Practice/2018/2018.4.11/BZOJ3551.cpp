#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson S[now].ls
#define rson S[now].rs
#define GetNum(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=100010*2;
const int maxM=500010*2;
const int maxBit=28;
const int inf=2147483647;

class Edge
{
public:
	int u,v,w;
};

class SegmentData
{
public:
	int cnt;
	int ls,rs;
};

int n,m,nodecnt,Q;
//Graph
Edge E[maxM];
int NodeW[maxN],UFS[maxN];
//Num
int numcnt,Num[maxN];
//Kruscal-Tree
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Fa[maxBit][maxN],FaW[maxBit][maxN];
//dfn
int dfncnt,From[maxN],To[maxN],DfnId[maxN],Depth[maxN];
//segment
int segcnt=0,root[maxN];
SegmentData S[maxN*20];

bool operator < (Edge A,Edge B);
int Find(int x);
void Add_Edge(int u,int v);
void dfs_dfn(int u);
void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos,int key);
int Query(int r1,int r2,int l,int r,int kth);

int main()
{
	mem(Head,-1);
	
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&NodeW[i]);
		UFS[i]=i;Num[++numcnt]=NodeW[i];
	}
	
	sort(&Num[1],&Num[numcnt+1]);
	numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	
	for (int i=1;i<=m;i++) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	sort(&E[1],&E[m+1]);

	nodecnt=n;
	for (int i=1;i<=m;i++)
	{
		int u=E[i].u,v=E[i].v;
		int fu=Find(u),fv=Find(v);
		if (fu!=fv)
		{
			nodecnt++;NodeW[nodecnt]=E[i].w;UFS[nodecnt]=nodecnt;
			Fa[0][fu]=Fa[0][fv]=nodecnt;
			FaW[0][fu]=FaW[0][fv]=E[i].w;
			UFS[fu]=UFS[fv]=nodecnt;
			Add_Edge(nodecnt,fu);Add_Edge(nodecnt,fv);
		}
	}

	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=nodecnt;j++)
			if (Fa[i-1][j]!=0){
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];FaW[i][j]=max(FaW[i-1][j],FaW[i-1][Fa[i-1][j]]);
			}

	Depth[nodecnt]=1;
	dfs_dfn(nodecnt);

	Build(root[0],1,numcnt);
	for (int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		Modify(root[i],1,numcnt,GetNum(NodeW[DfnId[i]]),1);
	}

	int lastans=0;
	while (Q--)
	{
		int v,x,k;scanf("%d%d%d",&v,&x,&k);
		if (lastans!=-1) v^=lastans,x^=lastans,k^=lastans;
		for (int i=maxBit-1;i>=0;i--) if ((Fa[i][v]!=0)&&(FaW[i][v]<=x)) v=Fa[i][v];
		//cout<<"To:"<<v<<endl;
		if (To[v]-From[v]+1<k)
		{
			printf("%d\n",lastans=-1);
			continue;
		}
		printf("%d\n",lastans=Num[Query(root[From[v]-1],root[To[v]],1,numcnt,k)]);
	}
	return 0;
}

bool operator < (Edge A,Edge B)
{
	return A.w<B.w;
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs_dfn(int u)
{
	if (u<=n)
	{
		From[u]=To[u]=++dfncnt;
		DfnId[dfncnt]=u;
		return;
	}
	From[u]=dfncnt+1;
	//cout<<u<<":"<<NodeW[u]<<endl;
	for (int i=Head[u];i!=-1;i=Next[i]){
		//cout<<u<<"->"<<V[i]<<endl;
		Depth[V[i]]=Depth[u]+1;dfs_dfn(V[i]);
	}
	To[u]=dfncnt;
	return;
}

void Build(int &now,int l,int r)
{
	now=++segcnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++segcnt]=S[now];now=segcnt;
	S[now].cnt+=key;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	return;
}

int Query(int r1,int r2,int l,int r,int kth)
{
	if (l==r) return l;
	int mid=(l+r)>>1;
	int rsize=S[S[r2].rs].cnt-S[S[r1].rs].cnt;
	if (rsize>=kth) return Query(S[r1].rs,S[r2].rs,mid+1,r,kth);
	else return Query(S[r1].ls,S[r2].ls,l,mid,kth-rsize);
}
