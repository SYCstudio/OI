#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define GetNum(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=80010;
const int maxM=maxN*2;
const int maxBit=18;
const int inf=2147483647;

class SegmentData
{
public:
	int cnt;
	int ls,rs;
};

int n,m,T,nodecnt;
int Val[maxN],Root[maxN];
int numcnt,Num[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Fa[maxBit][maxN],UFS[maxN],Size[maxN],Depth[maxN];
SegmentData S[maxN*200];
bool vis[maxN];
vector<int> Vec;

void Add_Edge(int u,int v);
void Build(int u,int fa);
int GetLCA(int u,int v);
void Modify(int &now,int l,int r,int pos,int key);
int Query(int ru,int rv,int rlca,int rf,int l,int r,int kth);
int Find(int u);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	scanf("%d%d%d",&n,&m,&T);
	for (int i=1;i<=n;i++) UFS[i]=i;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&Val[i]);
		Num[++numcnt]=Val[i];
	}

	sort(&Num[1],&Num[numcnt+1]);
	numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	for (int i=1;i<=n;i++) Val[i]=GetNum(Val[i]);
	
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	for (int i=1;i<=n;i++)
		if (vis[i]==0)
		{
			Vec.clear();
			Build(i,0);
			for (int i=1;i<maxBit;i++)
				for (int j=0;j<Vec.size();j++)
				{
					int v=Vec[j];Fa[i][v]=-1;
					if (Fa[i-1][v]!=-1) Fa[i][v]=Fa[i-1][Fa[i-1][v]];
				}
		}
	int lastans=0;
	for (int i=1;i<=T;i++)
	{
		char opt;
		opt=getchar();
		while ((opt!='Q')&&(opt!='L')) opt=getchar();
		if (opt=='Q')
		{
			int u,v,k;scanf("%d%d%d",&u,&v,&k);u^=lastans;v^=lastans;k^=lastans;
			int lca=GetLCA(u,v);
			printf("%d\n",lastans=Num[Query(Root[u],Root[v],Root[lca],Root[Fa[0][lca]],1,numcnt,k)]);
		}
		if (opt=='L')
		{
			int u,v;scanf("%d%d",&u,&v);u^=lastans;v^=lastans;
			Add_Edge(u,v);Add_Edge(v,u);
			int fu=Find(u),fv=Find(v);
			if (Size[fu]>Size[fv]) swap(fu,fv),swap(u,v);
			Fa[0][u]=v;UFS[u]=v;

			Vec.clear();
			Build(u,v);
			for (int i=1;i<maxBit;i++)
				for (int j=0;j<Vec.size();j++)
				{
					int v=Vec[j];Fa[i][v]=-1;
					if (Fa[i-1][v]!=-1) Fa[i][v]=Fa[i-1][Fa[i-1][v]];
				}
			Size[fv]+=Size[u];
		}
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

int GetLCA(int u,int v)
{
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u]!=-1)&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u]!=-1)&&(Fa[i][v]!=-1)&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

void Build(int u,int fa)
{
	Vec.push_back(u);
	Root[u]=Root[fa];Depth[u]=Depth[fa]+1;
	Modify(Root[u],1,numcnt,Val[u],1);
	vis[u]=1;Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			UFS[V[i]]=u;Fa[0][V[i]]=u;
			Build(V[i],u);
			Size[u]+=Size[V[i]];
		}
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].cnt+=key;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[now].ls,l,mid,pos,key);
	else Modify(S[now].rs,mid+1,r,pos,key);
}

int Query(int ru,int rv,int rlca,int rf,int l,int r,int kth)
{
	if (l==r) return l;
	int lsize=S[S[ru].ls].cnt+S[S[rv].ls].cnt-S[S[rlca].ls].cnt-S[S[rf].ls].cnt;
	int mid=(l+r)>>1;
	if (lsize>=kth) return Query(S[ru].ls,S[rv].ls,S[rlca].ls,S[rf].ls,l,mid,kth);
	else return Query(S[ru].rs,S[rv].rs,S[rlca].rs,S[rf].rs,mid+1,r,kth-lsize);
}

int Find(int u)
{
	if (UFS[u]!=u) UFS[u]=Find(UFS[u]);
	return UFS[u];
}
