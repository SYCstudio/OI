#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2000010;
const int maxM=maxN*2;
const int maxAlpha=27;
const int inf=2147483647;

class Trie
{
public:
	int fail,cnt;
	int son[maxAlpha];
};

int n,nodecnt;
char str[maxN],input[maxN];
Trie T[maxN];
int Id[maxN];
int Queue[maxN];

namespace TC
{
	int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
	int Sum[maxN];
	int dfncnt=0,Dfn[maxN],Hson[maxN],Size[maxN],Top[maxN],Fa[maxN];
	void init()
	{
		mem(Head,-1);Fa[0]=-1;
	}
	
	void Add_Edge(int u,int v)
	{
		//cout<<"Link:"<<u<<" "<<v<<endl;
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
		//edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
		return;
	}
	void dfs(int u,int fa)
	{
		Size[u]=T[u].cnt;
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			dfs(V[i],u);
			Size[u]+=Size[V[i]];
		}
		return;
	}
/*
	void dfs1(int u,int fa)
	{
		Size[u]=1;Hson[u]=-1;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=fa)
			{
				//cout<<u<<"->"<<V[i]<<endl;
				dfs1(V[i],u);
				Fa[V[i]]=u;Size[u]+=Size[V[i]];
				if ((Hson[u]==-1)||(Size[Hson[u]]<Size[V[i]])) Hson[u]=V[i];
			}
		return;
	}

	void dfs2(int u,int top)
	{
		Top[u]=top;Dfn[u]=++dfncnt;
		if (Hson[u]==-1) return;
		dfs2(Hson[u],top);
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((V[i]!=Hson[u])&&(V[i]!=
				dfs2(V[i],V[i]);
		return;
	}

	void Cover(int l,int r,int cnt)
	{
		//cout<<"Cover:"<<l<<" "<<r<<" "<<cnt<<endl;
		Sum[l]+=cnt;Sum[r+1]-=cnt;
		return;
	}
	
	void Modify(int u,int cnt)
	{
		cout<<"Modify:"<<u<<" "<<cnt<<endl;
		while (u!=-1)
		{
			//cout<<"u:"<<u<<" Top[u]:"<<Top[u]<<endl;
			Cover(Dfn[Top[u]],Dfn[u],cnt);
			u=Fa[Top[u]];
		}
		return;
	}

	void Calc()
	{
		for (int i=1;i<=dfncnt;i++) Sum[i]+=Sum[i-1];
		return;
	}
				//*/
				
	void Outp()
	{
		/*
		cout<<"dfncnt:"<<dfncnt<<endl;
		for (int i=0;i<=nodecnt;i++) cout<<Dfn[i]<<" ";cout<<endl;
		for (int i=0;i<=nodecnt;i++) cout<<Top[i]<<" ";cout<<endl;
		for (int i=0;i<=nodecnt;i++) cout<<Hson[i]<<" ";cout<<endl;
		//*/
	}
}



void Insert(char *str,int id);
void GetFail();
//void AhoChorasick(char *str);
void dfs(int u);

int main()
{
	//freopen("str.in","r",stdin);
	ios::sync_with_stdio(false);TC::init();
	
	cin>>n;
	int len=0;
	for (int i=1;i<=n;i++)
	{
		cin>>(input+1);
		int l=strlen(input+1);
		Insert(input,i);
		str[++len]='z'+1;
		for (int j=1;j<=l;j++) str[len+j]=input[j];
		len=len+l;
		Id[len]=i;
	}
	str[++len]='\0';
	//cout<<(str+1)<<endl;
	//cout<<nodecnt<<endl;
	GetFail();
	TC::dfs(0,0);
	//TC::dfs1(0,0);TC::dfs2(0,0);
	//AhoChorasick(str);
	//TC::Outp();TC::Calc();
	//for (int i=1;i<=nodecnt;i++) cout<<TC::Size[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<TC::Size[Id[i]]<<endl;
	return 0;
}

void Insert(char *str,int id)
{
	int len=strlen(str+1);
	int now=0;
	for (int i=1;i<=len;i++)
	{
		if (T[now].son[str[i]-'a']==0) T[now].son[str[i]-'a']=++nodecnt;
		now=T[now].son[str[i]-'a'];
		T[now].cnt++;
	}
	Id[id]=now;//T[now].cnt++;
	return;
}

void GetFail()
{
	int h=0,t=0;
	for (int i=0;i<maxAlpha;i++) if (T[0].son[i]!=0) Queue[++h]=T[0].son[i];
	do
	{
		int u=Queue[++t];
		for (int i=0;i<maxAlpha;i++)
		{
			if (T[u].son[i])
			{
				T[T[u].son[i]].fail=T[T[u].fail].son[i];
				Queue[++h]=T[u].son[i];
			}
			else T[u].son[i]=T[T[u].fail].son[i];
		}
	}
	while (t!=h);
	for (int i=1;i<=nodecnt;i++) TC::Add_Edge(T[i].fail,i);
	return;
}
/*
void AhoChorasick(char *str)
{
	int len=strlen(str+1);
	int now=0;
	for (int i=1;i<=len;i++)
	{
		now=T[now].son[str[i]-'a'];
		if (T[now].cnt) cout<<"pos:"<<now<<" ",TC::Modify(now,T[now].cnt);
	}
	return;
}
//*/
