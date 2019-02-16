#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN*2;
const int maxBit=18;
const int inf=2147483647;

class SetData
{
public:
	int pos;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll W[maxM];
int dfncnt,Dfn[maxN];
int Depth[maxN],Fa[maxBit][maxN];
ll Dist[maxN];
set<SetData> Set;
int Mark[maxN];

bool operator < (SetData A,SetData B);
void Add_Edge(int u,int v,int w);
void dfs_init(int u,int fa);
int GetLCA(int u,int v);
ll GetDist(int u,int v);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);
	}
	dfs_init(1,0);
	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=n;j++)
			if ((Fa[i-1][j])&&(Fa[i-1][Fa[i-1][j]]))
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	ll Ans=0;
	for (int i=1;i<=m;i++)
	{
		int u;scanf("%d",&u);
		SetData uu=((SetData){u});
		if (Mark[u])
		{
			Mark[u]=0;
			if (Set.size()==1){
				Set.erase(uu);Ans=0;
			}
			else if (Set.size()==2){
				Set.erase(uu);Ans=0;
			}
			else
			{
				set<SetData>::iterator p1=Set.find(uu),p2,p3;
				if ((*p1).pos==(*Set.begin()).pos)
				{
					p2=p1;p2++;
					Ans-=GetDist((*p1).pos,(*p2).pos);
					Ans-=GetDist((*p1).pos,(*Set.rbegin()).pos);
					Set.erase(p1);
					Ans+=GetDist((*Set.begin()).pos,(*Set.rbegin()).pos);
				}
				else if ((*p1).pos==(*Set.rbegin()).pos)
				{
					p2=p1;p2--;
					Ans-=GetDist((*p1).pos,(*p2).pos);
					Ans-=GetDist((*p1).pos,(*Set.begin()).pos);
					Set.erase(p1);
					Ans+=GetDist((*Set.begin()).pos,(*Set.rbegin()).pos);
				}
				else
				{
					p2=p1;p2--;p3=p1;p3++;
					Ans-=GetDist((*p1).pos,(*p2).pos);
					Ans-=GetDist((*p1).pos,(*p3).pos);
					Ans+=GetDist((*p2).pos,(*p3).pos);
					Set.erase(p1);
				}
			}
		}
		else
		{
			Mark[u]=1;
			Set.insert(uu);
			set<SetData>::iterator p1=Set.find(uu),p2,p3;
			if (Set.size()==1) Ans=0;
			else if (Set.size()==2)	Ans=GetDist((*Set.begin()).pos,(*Set.rbegin()).pos)*2ll;
			else
			{
				if ((*p1).pos==(*Set.begin()).pos)
				{
					p2=p1;p2++;
					Ans-=GetDist((*p2).pos,(*Set.rbegin()).pos);
					Ans+=GetDist((*p1).pos,(*p2).pos);
					Ans+=GetDist((*p1).pos,(*Set.rbegin()).pos);
				}
				else if ((*p1).pos==(*Set.rbegin()).pos)
				{
					p2=p1;p2--;
					Ans-=GetDist((*p2).pos,(*Set.begin()).pos);
					Ans+=GetDist((*p1).pos,(*p2).pos);
					Ans+=GetDist((*p1).pos,(*Set.begin()).pos);
				}
				else
				{
					p2=p1;p2--;p3=p1;p3++;
					Ans-=GetDist((*p2).pos,(*p3).pos);
					Ans+=GetDist((*p1).pos,(*p2).pos);
					Ans+=GetDist((*p1).pos,(*p3).pos);
				}
			}
		}
		printf("%lld\n",Ans);
	}
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
	return;
}

void dfs_init(int u,int fa)
{
	Depth[u]=Depth[fa]+1;Dfn[u]=++dfncnt;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Dist[V[i]]=Dist[u]+W[i];
			Fa[0][V[i]]=u;
			dfs_init(V[i],u);
		}
	return;
}

bool operator < (SetData A,SetData B){
	return Dfn[A.pos]<Dfn[B.pos];
}

int GetLCA(int u,int v)
{
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

ll GetDist(int u,int v)
{
	//cout<<"GetDist:"<<u<<" "<<v<<endl;
	int lca=GetLCA(u,v);
	//cout<<"lca:"<<lca<<" "<<Dist[u]<<" "<<Dist[v]<<" "<<Dist[lca]<<endl;
	return Dist[u]-Dist[lca]+Dist[v]-Dist[lca];
}
