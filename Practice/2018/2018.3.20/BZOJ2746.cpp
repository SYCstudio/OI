#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1000200;
const int maxAlpha=26;
const int Mod=1000000007;
const int hashbase=26;
const int inf=2147483647;

class TrieData
{
public:
	int fail;
	ll hash;
	int son[maxAlpha];
};

int n,nodecnt;
char str[maxN];
TrieData T[maxN];
vector<int> Pos[maxN];
int edgecnt=0,Head[maxN],Next[maxN],V[maxN];
int Hson[maxN],Size[maxN],Top[maxN],Fa[maxN],Depth[maxN];
queue<int> Queue;

void Insert(char *str,int id);
void GetFail();
void Add_Edge(int u,int v);
void dfs1(int u);
void dfs2(int u,int top);
int GetLCA(int u,int v);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		Insert(str,i);
	}
	GetFail();
	dfs1(0);dfs2(0,0);
	int m;
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
		int u=Pos[a][b],v=Pos[c][d];
		int lca=GetLCA(u,v);
		//cout<<u<<" "<<v<<" "<<lca<<endl;
		printf("%lld\n",(T[lca].hash+Mod)%Mod);
	}
	return 0;
}

void Insert(char *str,int id)
{
	int len=strlen(str+1);
	int now=0;
	Pos[id].push_back(0);
	for (int i=1;i<=len;i++)
	{
		if (T[now].son[str[i]-'a']==0) T[now].son[str[i]-'a']=++nodecnt,T[nodecnt].hash=((ll)T[now].hash*(ll)hashbase%Mod+str[i]-'a')%Mod;
		now=T[now].son[str[i]-'a'];
		Pos[id].push_back(now);
		//cout<<Pos[id][i]<<" ";
		//cout<<T[now].hash<<" ";
	}
	//cout<<endl;
	return;
}

void GetFail()
{
	for (int i=0;i<maxAlpha;i++) if (T[0].son[i]) Queue.push(T[0].son[i]);
	while (!Queue.empty())
	{
		int u=Queue.front();Queue.pop();
		for (int i=0;i<maxAlpha;i++)
			if (T[u].son[i])
			{
				T[T[u].son[i]].fail=T[T[u].fail].son[i];
				Queue.push(T[u].son[i]);
			}
			else T[u].son[i]=T[T[u].fail].son[i];
	}
	for (int i=1;i<=nodecnt;i++) Add_Edge(T[i].fail,i);
	return;
}

void Add_Edge(int u,int v)
{
    //cout<<"Add:"<<u<<" "<<v<<endl;
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u)
{
	Size[u]=1;Hson[u]=-1;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		Fa[V[i]]=u;Depth[V[i]]=Depth[u]+1;dfs1(V[i]);
		Size[u]+=Size[V[i]];
		if ((Hson[u]==-1)||(Size[V[i]]>Size[Hson[u]])) Hson[u]=V[i];
	}
	return;
}

void dfs2(int u,int top)
{
	Top[u]=top;
	if (Hson[u]==-1) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=Hson[u]) dfs2(V[i],V[i]);
	return;
}

int GetLCA(int u,int v)
{
	//cout<<u<<" "<<v<<endl;
	//cout<<Top[u]<<" "<<Top[v]<<endl;
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		u=Fa[Top[u]];
		//cout<<u<<" "<<v<<endl;
	}
	//cout<<u<<" "<<v<<" "<<Depth[u]<<" "<<Depth[v]<<endl;
	if (Depth[u]>Depth[v]) swap(u,v);
	return u;
}
