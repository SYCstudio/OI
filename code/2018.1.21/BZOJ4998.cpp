#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200110;
const int inf=2147483647;

class Splay_Data
{
public:
	int fa,ch[2];
	int rev;
};

int n,m,P;
Splay_Data S[maxN];
int Stack[maxN];
int Set1[maxN],Set2[maxN];
int Size[maxN];

bool Isroot(int x);
void PushDown(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
void Link(int x,int y);
int Add_Edge(int u,int v);
int Find(int *f,int x);
void dfs(int now,int fa);

int main()
{
	scanf("%d%d%d",&n,&m,&P);
	for (int i=1;i<=n;i++) Size[i]=1,Set1[i]=Set2[i]=i;
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		u=Find(Set2,u);v=Find(Set2,v);
		Add_Edge(u,v);
	}
	for (int i=1;i<=P;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		u=Find(Set2,u);v=Find(Set2,v);
		int ret=Add_Edge(u,v);
		if (ret==-1) printf("No\n");
		else printf("%d\n",ret);
	}
	return 0;
}

bool Isroot(int x)
{
	if ((S[Find(Set2,S[x].fa)].ch[0]==x)||(S[Find(Set2,S[x].fa)].ch[1]==x)) return 0;
	return 1;
}

void PushDown(int x)
{
	if (S[x].rev==1)
	{
		S[x].rev=0;
		if (S[x].ch[0]) S[S[x].ch[0]].rev^=1,swap(S[S[x].ch[0]].ch[0],S[S[x].ch[0]].ch[1]);
		if (S[x].ch[1]) S[S[x].ch[1]].rev^=1,swap(S[S[x].ch[1]].ch[0],S[S[x].ch[1]].ch[1]);
	}
	return;
}

void Rotate(int x)
{
	int y=Find(Set2,S[x].fa);int z=Find(Set2,S[y].fa);
	int sx=(x==S[y].ch[1]);
	int sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;S[y].ch[sx]=S[x].ch[sx^1];
	S[y].fa=x;S[x].ch[sx^1]=y;
	return;
}

void Splay(int x)
{
	int stacktop=1;Stack[1]=x;
	int now=x;
	while (Isroot(now)==0)
	{
		Stack[++stacktop]=Find(Set2,S[now].fa);
		now=Find(Set2,S[now].fa);
	}
	for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	while (Isroot(x)==0)
	{
		int y=Find(Set2,S[x].fa);int z=Find(Set2,S[y].fa);
		if (Isroot(y)==0)
			((S[y].ch[0]==x)^(S[z].ch[0]==y))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	return;
}

void Access(int x)
{
	int lastx=0;
	while (x)
	{
		Splay(x);S[x].ch[1]=lastx;S[lastx].fa=x;
		lastx=x;x=Find(Set2,S[x].fa);
	}
	return;
}

void Makeroot(int x)
{
	Access(x);Splay(x);
	S[x].rev^=1;swap(S[x].ch[0],S[x].ch[1]);
	return;
}

void Link(int x,int y)
{
	Makeroot(x);S[x].fa=y;
	return;
}

int Add_Edge(int u,int v)
{
	if (Find(Set1,u)!=Find(Set1,v))
	{
		Set1[Find(Set1,u)]=Find(Set1,v);
		Link(u,v);
		return -1;
	}
	else
	{
		//cout<<"Add:"<<u<<" "<<v<<endl;
		Makeroot(u);Access(v);Splay(v);
		dfs(v,v);
		S[v].ch[0]=S[v].ch[1]=0;
		return Size[v];
	}
}

int Find(int *f,int x)
{
	if (f[x]!=x) f[x]=Find(f,f[x]);
	return f[x];
}

void dfs(int now,int fa)
{
	//cout<<"now:"<<now<<" fa:"<<fa<<endl;
	//cout<<"ch:"<<S[now].ch[0]<<" "<<S[now].ch[1]<<endl;
	if (now!=fa) Size[fa]+=Size[now],Set2[now]=fa;
	if (S[now].ch[0]) dfs(S[now].ch[0],fa);
	if (S[now].ch[1]) dfs(S[now].ch[1],fa);
	return;
}
