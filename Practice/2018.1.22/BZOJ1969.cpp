#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50010;
const int maxM=600010;
const int inf=2147483647;

class Splay_Data
{
public:
	int fa,ch[2];
	int size;
	int rev;
};

class Question
{
public:
	int c,u,v;
	int ans;
};

int n,m;
Splay_Data S[maxN];
int Id[maxN];
int Stack[maxN];
set<int> Exi[maxN];
Question Qn[maxN];

int Find(int *f,int x);
bool Isroot(int x);
void Update(int x);
void PushDown(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
int Findroot(int x);
void Link(int x,int y);
void Add_Edge(int x,int y);
void dfs(int u,int fa);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) Id[i]=i;
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		if (u>v) swap(u,v);
		Exi[u].insert(v);
	}
	int Q=0;
	{
		int c,u,v;
		while (scanf("%d",&c)!=EOF)
		{
			if (c==-1) break;
			scanf("%d%d",&u,&v);
			if (u>v) swap(u,v);
			Q++;Qn[Q]=(Question){c,u,v};
			if (c==0) Exi[u].erase(v);
		}
	}
	for (int i=1;i<=n;i++)
		for (set<int>::iterator j=Exi[i].begin();j!=Exi[i].end();j++)
			Add_Edge(i,*j);
	for (int i=Q;i>=1;i--)
	{
		if (Qn[i].c==0) Add_Edge(Qn[i].u,Qn[i].v);
		if (Qn[i].c==1)
		{
			int u=Find(Id,Qn[i].u);
			int v=Find(Id,Qn[i].v);
			Makeroot(u);Access(v);Splay(v);
			Qn[i].ans=S[v].size-1;
		}
	}
	for (int i=1;i<=Q;i++) if (Qn[i].c==1) printf("%d\n",Qn[i].ans);
}

int Find(int *f,int x)
{
	if (f[x]!=x) f[x]=Find(f,f[x]);
	return f[x];
}

bool Isroot(int x)
{
	int fa=Find(Id,S[x].fa);
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}

void Update(int x)
{
	S[x].size=S[S[x].ch[0]].size+S[S[x].ch[1]].size+1;
	return;
}

void PushDown(int x)
{
	if (S[x].rev)
	{
		S[x].rev=0;
		int lson=S[x].ch[0],rson=S[x].ch[1];
		swap(S[lson].ch[0],S[lson].ch[1]);
		swap(S[rson].ch[0],S[rson].ch[1]);
		S[lson].rev^=1;S[rson].rev^=1;
	}
	return;
}

void Rotate(int x)
{
	int y=Find(Id,S[x].fa);int z=Find(Id,S[y].fa);
	int sx=(x==S[y].ch[1]);
	int sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);
	return;
}

void Splay(int x)
{
	int now=x;
	int stacktop=1;Stack[1]=now;
	while (Isroot(now)==0)
	{
		Stack[++stacktop]=Find(Id,S[now].fa);
		now=Find(Id,S[now].fa);
	}
	for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	while (Isroot(x)==0)
	{
		int y=Find(Id,S[x].fa);int z=Find(Id,S[y].fa);
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);return;
}

void Access(int x)
{
	int lastx=0;
	while (x)
	{
		Splay(x);S[x].ch[1]=lastx;Update(x);
		lastx=x;x=Find(Id,S[x].fa);
	}
	return;
}

void Makeroot(int x)
{
	Access(x);Splay(x);
	S[x].rev^=1;swap(S[x].ch[0],S[x].ch[1]);
	return;
}

int Findroot(int x)
{
	Access(x);Splay(x);
	int now=x;
	while (S[now].ch[0]) now=S[now].ch[0];
	return now;
}

void Link(int x,int y)
{
	Makeroot(x);S[x].fa=y;
	return;
}

void Add_Edge(int u,int v)
{
	u=Find(Id,u);v=Find(Id,v);
	if (Findroot(u)!=Findroot(v)) Link(u,v);
	else
	{
		Makeroot(u);Access(v);Splay(v);
		dfs(v,v);
		S[v].size=1;S[v].ch[0]=S[v].ch[1]=0;
	}
	return;
}

void dfs(int u,int fa)
{
	if (u!=fa) Id[u]=fa;
	if (S[u].ch[0]) dfs(S[u].ch[0],fa);
	if (S[u].ch[1]) dfs(S[u].ch[1],fa);
	return;
}
