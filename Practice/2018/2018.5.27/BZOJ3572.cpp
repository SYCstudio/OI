#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int maxM=maxN*2;
const int maxBit=16;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,Dfn[maxN],Last[maxN],Depth[maxN],Fa[maxBit][maxN],Size[maxN];
int Stack[maxN],Node[maxN<<1],Mark[maxN],Input[maxN],Sum[maxN],Cnt[maxN],nowFa[maxN];
int Near[maxN];//,Dist[maxN];

void Add_Edge(int u,int v);
void dfs_init(int u,int fa);
int GetLCA(int u,int v);
int GetDist(int u,int v);
bool cmp(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int fa);
void Do(int u,int fa);

int main()
{
	//freopen("10.in","r",stdin);freopen("out.out","w",stdout);
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	dfs_init(1,0);
	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=n;j++)
			if ((Fa[i-1][j])&&(Fa[i-1][Fa[i-1][j]]))
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	//cout<<"Depth:";for (int i=1;i<=n;i++) cout<<Depth[i]<<" ";cout<<endl;
	//cout<<"Size:";for (int i=1;i<=n;i++) cout<<Size[i]<<" ";cout<<endl;

	edgecnt=0;
	mem(Head,-1);
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		int K,KK;scanf("%d",&K);KK=K;
		for (int i=1;i<=K;i++) scanf("%d",&Node[i]),Input[i]=Node[i];

		for (int i=1;i<=K;i++) Mark[Node[i]]=1,Cnt[Node[i]]=0,Near[Node[i]]=Node[i];

		sort(&Node[1],&Node[K+1],cmp);
		for (int i=1;i<K;i++) Node[i+K]=GetLCA(Node[i],Node[i+1]);
		K=K+K;Node[K]=1;
		sort(&Node[1],&Node[K+1],cmp);K=unique(&Node[1],&Node[K+1])-Node-1;

		edgecnt=0;
		for (int i=1;i<=K;i++) Head[Node[i]]=-1;

		//cout<<"Node:";for (int i=1;i<=K;i++) cout<<Node[i]<<" ";cout<<endl;

		int top=0;
		for (int i=1;i<=K;i++)
		{
			while ((top)&&(Last[Stack[top]]<Dfn[Node[i]])) top--;
			if (top) Add_Edge(Stack[top],Node[i]);
			Stack[++top]=Node[i];
		}

		dfs1(1,0);
		dfs2(1,0);

		//cout<<K<<endl;
		//sort(&Node[1],&Node[K+1]);
		//for (int i=1;i<=K;i++) cout<<Node[i]<<" ";cout<<endl;
		//for (int i=1;i<=K;i++) cout<<Near[Node[i]]<<" ";cout<<endl;
		//cout<<"Dist:";for (int i=1;i<=K;i++) cout<<Dist[Node[i]]<<" ";cout<<endl;
		
		for (int i=1;i<=K;i++)
			for (int j=Head[Node[i]];j!=-1;j=Next[j])
				if (V[j]!=nowFa[Node[i]])
					Do(V[j],Node[i]);
		
		for (int i=1;i<=K;i++) Cnt[Near[Node[i]]]+=Sum[Node[i]];

		for (int i=1;i<=KK;i++) printf("%d ",Cnt[Input[i]]);
		printf("\n");

		for (int i=1;i<=K;i++) Mark[Node[i]]=Cnt[Node[i]]=Sum[Node[i]]=Near[Node[i]]=0;
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void dfs_init(int u,int fa)
{
	Depth[u]=Depth[fa]+1;Dfn[u]=++dfncnt;Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Fa[0][V[i]]=u;
			dfs_init(V[i],u);
			Size[u]+=Size[V[i]];
		}
	Last[u]=dfncnt;
	return;
}

int GetLCA(int u,int v)
{
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

int GetDist(int u,int v){
	return Depth[u]+Depth[v]-2*Depth[GetLCA(u,v)];
}

bool cmp(int u,int v){
	return Dfn[u]<Dfn[v];
}

void dfs1(int u,int fa)
{
	Sum[u]=Size[u];//Dist[u]=inf;
	//if (Mark[u]) Dist[u]=0,Near[u]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			nowFa[V[i]]=u;
			dfs1(V[i],u);
			if (Near[V[i]]==0) continue;
			int d1=GetDist(Near[V[i]],u),d2=GetDist(Near[u],u);
			if ((Near[u]==0)||(d1<d2)||((d1==d2)&&(Near[V[i]]<Near[u])))
				Near[u]=Near[V[i]];
		}
	return;
}

void dfs2(int u,int fa)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			int d1=GetDist(Near[u],V[i]),d2=GetDist(Near[V[i]],V[i]);
			if ((Near[V[i]]==0)||(d1<d2)||((d1==d2)&&(Near[u]<Near[V[i]]))) Near[V[i]]=Near[u];
			dfs2(V[i],u);
		}
	return;
}

void Do(int u,int fa)
{
	//cout<<"Do:"<<u<<" "<<fa<<endl;
	int An=u;
	for (int i=maxBit;i>=0;i--) if ((Fa[i][An])&&(Depth[Fa[i][An]]>Depth[fa])) An=Fa[i][An];
	Sum[fa]-=Size[An];
	if (Near[u]==Near[fa])
	{
		Cnt[Near[u]]+=Size[An]-Size[u];
		return;
	}
	int now=u;
	for (int i=maxBit-1;i>=0;i--)
		if ((Fa[i][now])&&(Depth[Fa[i][now]]>Depth[fa]))
		{
			int d1=GetDist(Near[u],Fa[i][now]),d2=GetDist(Near[fa],Fa[i][now]);
			if ((d1<d2)||((d1==d2)&&(Near[u]<Near[fa]))) now=Fa[i][now];
		}
	//cout<<"now:"<<now<<endl;
	Cnt[Near[u]]+=Size[now]-Size[u];
	Cnt[Near[fa]]+=Size[An]-Size[now];
	return;
}
