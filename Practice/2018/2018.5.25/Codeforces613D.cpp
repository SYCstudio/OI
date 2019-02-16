#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN*2;
const int maxBit=20;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Fa[maxBit][maxN],Depth[maxN];
int dfncnt=0,Dfn[maxN],Last[maxN];
int Node[maxN<<1],Stack[maxN<<1],Mark[maxN],Size[maxN];

void Add_Edge(int u,int v);
void dfs_init(int u,int fa);
int GetLCA(int u,int v);
bool cmp(int a,int b);
int dfs(int u,int fa);

int main()
{
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

	edgecnt=0;mem(Head,-1);
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		int K;scanf("%d",&K);
		for (int i=1;i<=K;i++) scanf("%d",&Node[i]);
		for (int i=1;i<=K;i++) Mark[Node[i]]=1;

		bool flag=1;
		for (int i=1;i<=K;i++)
			if (Mark[Fa[0][Node[i]]]){
				flag=0;break;
			}
		if (flag==0)
		{
			printf("-1\n");
			for (int i=1;i<=K;i++) Mark[Node[i]]=0;
			continue;
		}
		
		sort(&Node[1],&Node[K+1],cmp);
		for (int i=1;i<K;i++) Node[K+i]=GetLCA(Node[i],Node[i+1]);
		K=K+K;Node[K]=1;
		sort(&Node[1],&Node[K+1],cmp);K=unique(&Node[1],&Node[K+1])-Node-1;

		edgecnt=0;
		for (int i=1;i<=K;i++) Head[Node[i]]=-1;

		int top=0;
		for (int i=1;i<=K;i++)
		{
			while ((top)&&(Last[Stack[top]]<Dfn[Node[i]])) top--;
			if (top) Add_Edge(Node[i],Stack[top]);
			Stack[++top]=Node[i];
		}

		printf("%d\n",dfs(1,0));

		for (int i=1;i<=K;i++) Mark[Node[i]]=0;
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
	Depth[u]=Depth[fa]+1;
	Dfn[u]=++dfncnt;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Fa[0][V[i]]=u;
			dfs_init(V[i],u);
		}
	Last[u]=dfncnt;return;
}

int GetLCA(int u,int v)
{
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

bool cmp(int a,int b)
{
	return Dfn[a]<Dfn[b];
}

int dfs(int u,int fa)
{
	int ret=0,cnt=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			ret+=dfs(V[i],u);
			cnt+=Size[V[i]];
		}
	if (Mark[u])
	{
		Size[u]=1;
		ret+=cnt;
	}
	else
	{
		ret+=(cnt>1);
		Size[u]=(cnt==1);
	}
	return ret;
}
