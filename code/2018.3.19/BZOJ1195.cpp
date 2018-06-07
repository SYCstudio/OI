#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<string>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=15;
const int maxM=maxN*maxN*8;
const int maxL=100;
const int maxAlpha=27;
const int inf=2147483647;

class TrieData
{
public:
	int end,fail,id,depth,input;
	int son[maxAlpha];
	int son2[maxAlpha];
};

class QueueData
{
public:
	int u,key;
};

int n,nodecnt,idcnt,Id[maxN];
bool path[maxN*maxL];
char str[maxN][maxL];
TrieData T[maxN*maxL];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Dist[maxN][1<<maxN];
string From[maxN][1<<maxN];
bool inqueue[maxN][1<<maxN];
int Map[maxN][maxN];
queue<QueueData> Q;

void Insert(char *str,int id);
void GetFail();
void dfs1(int u);
void dfs2(int u);
void Add_Edge(int u,int v,int w);
void Add(int u,int v,int w);

int main()
{
	//freopen("substr4.in","r",stdin);
	//freopen("out.out","w",stdout);
	mem(Head,-1);mem(Map,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str[i]+1);
		Insert(str[i],i);
	}
	GetFail();
	dfs1(0);
	//GetFail();
	//cout<<"idcnt:"<<idcnt<<endl;
	for (int i=1;i<=idcnt;i++)
		for (int j=1;j<=idcnt;j++)
			Map[i][j]=T[Id[j]].depth;
	//for (int i=0;i<=nodecnt;i++) if (T[i].end) cout<<i<<" "<<T[i].id<<" "<<T[i].input<<endl;
	dfs2(0);
	for (int i=1;i<=idcnt;i++)
		for (int j=1;j<=idcnt;j++)
			if (Map[i][j]!=-1) Add(i,j,Map[i][j]);
    /*
	for (int i=1;i<=idcnt;i++)
	{
		for (int j=1;j<=idcnt;j++)
			printf("%6d",Map[i][j]);
		printf("\n");
	}
	//*/
	//cout<<idcnt<<endl;
	//for (int i=1;i<=idcnt;i++) cout<<Id[i]<<" ";cout<<endl;
	mem(Dist,63);
	for (int i=1;i<=idcnt;i++)
	{
		Dist[i][1<<(i-1)]=T[Id[i]].depth;
		Q.push((QueueData){i,1<<(i-1)});
		inqueue[i][1<<(i-1)]=1;
		int l=strlen(str[T[Id[i]].input]+1);
		for (int j=1;j<=l;j++) From[i][1<<(i-1)]+=str[T[Id[i]].input][j];
	}
	do
	{
		int u=Q.front().u,key=Q.front().key;Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			if (((1<<(V[i]-1))&key)!=0) continue;
			int v=V[i],kk=key|(1<<(V[i]-1));
			int d=Dist[u][key]+W[i];
			string ss=From[u][key];
			int len=strlen(str[T[Id[V[i]]].input]+1);
			for (int j=len-W[i]+1;j<=len;j++) ss+=str[T[Id[V[i]]].input][j];
			if ((Dist[v][kk]>d)||((Dist[v][kk]==d)&&(ss<From[v][kk])))
			{
				Dist[v][kk]=d;From[v][kk]=ss;
				//cout<<Dist[v][kk]<<" "<<ss.size()<<endl;
				if (inqueue[v][kk]==0)
				{
					inqueue[v][kk]=1;
					Q.push((QueueData){v,kk});
				}
			}
		}
		inqueue[u][key]=0;
	}
	while (!Q.empty());
	int Ans=inf;
	string ansstring;
	for (int i=1;i<=idcnt;i++)
		if ((Ans>Dist[i][(1<<idcnt)-1])||((Ans==Dist[i][(1<<idcnt)-1])&&(ansstring>From[i][(1<<idcnt)-1])))
		{
			Ans=Dist[i][(1<<idcnt)-1];
			ansstring=From[i][(1<<idcnt)-1];
		}
	int sz=ansstring.size();
	for (int i=0;i<sz;i++) printf("%c",ansstring[i]);
	printf("\n");
	/*
	for (int i=1;i<=idcnt;i++)
	{
		cout<<Dist[i][(1<<idcnt)-1]<<" ";
		for (int j=0;j<idcnt;j++) cout<<T[Id[From[i][(1<<idcnt)-1][j]]].input<<" ";cout<<endl;
	}
	for (int i=0;i<idcnt;i++) cout<<T[Id[ansstring[i]]].input;cout<<endl;

	for (int i=1;i<=idcnt;i++)
	{
		cout<<Dist[i][(1<<idcnt)-1]<<" ";
		for (int j=0;j<idcnt;j++) cout<<(int)From[i][(1<<idcnt)-1][j]<<" ";cout<<endl;
	}
	printf("%d\n",Ans);
	//*/
	return 0;
}

void Insert(char *str,int id)
{
	int len=strlen(str+1);
	int now=0;
	for (int i=1;i<=len;i++)
	{
		if (T[now].son[str[i]-'A']==0) T[now].son[str[i]-'A']=T[now].son2[str[i]-'A']=++nodecnt;
		now=T[now].son[str[i]-'A'];
	}
	T[now].end=1;T[now].input=id;
	return;
}

int Queue[maxN*maxL];

void GetFail()
{
	int h=0,t=0;
	for (int i=0;i<maxAlpha;i++) if (T[0].son[i]) Queue[++h]=T[0].son[i];
	while (t!=h)
	{
		int u=Queue[++t];
		for (int i=0;i<maxAlpha;i++)
			if (T[u].son2[i])
			{
				T[T[u].son2[i]].fail=T[T[u].fail].son2[i];
				Queue[++h]=T[u].son2[i];
			}
			else T[u].son2[i]=T[T[u].fail].son2[i];
	}
	for (int i=nodecnt;i>=0;i--) T[T[i].fail].end=0;
	//for (int i=0;i<=nodecnt;i++) cout<<i<<" "<<T[i].end<<endl;
	return;
}

void dfs1(int u)
{
	if (T[u].end) T[u].id=++idcnt,Id[idcnt]=u;
	for (int i=0;i<maxAlpha;i++) if (T[u].son[i]) T[T[u].son[i]].depth=T[u].depth+1,dfs1(T[u].son[i]);
	return;
}

void dfs2(int u)
{
	path[u]=1;
	if (T[u].end)
	{
		//cout<<"u:"<<u<<endl;
		for (int i=1;i<=idcnt;i++)
		{
			//cout<<i<<":"<<endl;
			if (i==T[u].id) continue;
			int now=Id[i];
			while (now!=0)
			{
				if (path[now])
				{
					Add_Edge(i,T[u].id,T[u].depth-T[now].depth);
					//cout<<"pos:"<<u<<" "<<now<<endl;
				}
				now=T[now].fail;
			}
		}
	}
	for (int i=0;i<maxAlpha;i++) if (T[T[u].son[i]].depth==T[u].depth+1) dfs2(T[u].son[i]);
	path[u]=0;
	return;
}

void Add_Edge(int u,int v,int w)
{
	//cout<<"Add:"<<u<<" "<<v<<" "<<w<<endl;
	if ((Map[u][v]==-1)||(Map[u][v]>w)) Map[u][v]=w;
	//edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void Add(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}
