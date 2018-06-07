#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1100100*4;
const int maxM=maxN*8;
const int inf=2147483647;

int n,m,K;
int Queue[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt=0,dfn[maxN],low[maxN];
int stacktop,Stack[maxN];
bool instack[maxN];
int idcnt=0,Id[maxN];
int Ans[maxN],Col[maxN];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);
int read();

int main()
{
	mem(Head,-1);
	n=read();m=read();K=read();//scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++)
	{
		Add_Edge(i,n*2+i);
		Add_Edge(n*3+i,i+n);
	}
	for (int i=1;i<=m;i++)
	{
		int u=read(),v=read();//scanf("%d%d",&u,&v);
		Add_Edge(u+n,v);Add_Edge(v+n,u);
	}
	for (int i=1;i<=K;i++)
	{
		int W=read();//scanf("%d",&W);
		for (int j=1;j<=W;j++) Queue[j]=read();//scanf("%d",&Queue[j]);
		for (int j=1;j<W;j++)
		{
			Add_Edge(Queue[j+1],n*3+Queue[j]);
			Add_Edge(n*2+Queue[j],n+Queue[j+1]);
			Add_Edge(n*2+Queue[j],n*2+Queue[j+1]);
			Add_Edge(n*3+Queue[j+1],n*3+Queue[j]);
		}
	}
	for (int i=1;i<=n*4;i++)
		if (dfn[i]==0) tarjan(i,i);

	bool flag=1;
	for (int i=1;i<=n;i++) if (Id[i]==Id[i+n]) {flag=0;break;}
	if (flag==0) printf("NIE\n");//io::putc('N'),io::putc('I'),io::putc('E'),io::putc('\n');
	else printf("TAK\n");//io::putc('T'),io::putc('A'),io::putc('K'),io::putc('\n');
	//io :: flush ();
	return 0;
}

int read()
{
	char ch=getchar();
	while ((ch>'9')||(ch<'0'))
	{
		if (ch==EOF) return EOF;
		ch=getchar();
	}
	int x=0;
	while ((ch>='0')&&(ch<='9')) x=x*10+ch-48,ch=getchar();
	return x;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++dfncnt;
	Stack[++stacktop]=u;instack[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			if (dfn[V[i]]==0)
			{
				tarjan(V[i],u);
				low[u]=min(low[u],low[V[i]]);
			}
			else if (instack[V[i]]) low[u]=min(low[u],dfn[V[i]]);
		}
	if (dfn[u]==low[u])
	{
		idcnt++;
		int v=0;
		while (v!=u){
			v=Stack[stacktop--];Id[v]=idcnt;instack[v]=0;
		}
	}
	return;
}
