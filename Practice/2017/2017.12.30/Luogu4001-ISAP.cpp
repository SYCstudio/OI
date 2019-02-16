#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Id(x,y) ((x-1)*m+y)
#define RG register
#define IL inline

const int maxN=1001;
const int maxNode=maxN*maxN;
const int maxW=maxNode*3*2;
const int queuesize=maxNode/10;
const int inf=2147483647;

class Edge
{
public:
    int u,v,w;
};

int n,m,S,T;
int cnt=-1,Head[maxNode],Next[maxW];
Edge E[maxW];
int Gap[maxNode],Depth[maxNode],cur[maxNode],Path[maxNode];
int Q[queuesize];

IL int read();
IL void Add_Edge(int u,int v,int w);
IL void Bfs();
IL int ISAP();

int main()
{
    mem(Head,-1);
    //scanf("%d%d",&n,&m);
    n=read();m=read();
    S=Id(1,1);T=Id(n,m);
    RG int i,j,x;
    for (i=1;i<=n;i++)
		for (j=1;j<m;j++)
		{
			x=read();
			Add_Edge(Id(i,j),Id(i,j+1),x);
		}
    for (i=1;i<n;i++)
		for (j=1;j<=m;j++)
		{
			x=read();
			Add_Edge(Id(i,j),Id(i+1,j),x);
		}
    for (i=1;i<n;i++)
		for (j=1;j<m;j++)
		{
			x=read();
			Add_Edge(Id(i,j),Id(i+1,j+1),x);
		}
    //ISAP
    n=n*m;
    /*
	  for (int i=1;i<=n;i++)
	  {
	  for (int j=Head[i];j!=-1;j=Next[j])
	  cout<<E[j].u<<"->"<<E[j].v<<" "<<E[j].w<<endl;
	  cout<<endl;
	  }
    //*/
    Bfs();
    /*
	  cout<<"Depth:";
	  for (int i=1;i<=n;i++) cout<<Depth[i]<<" ";
	  cout<<endl;
    //*/
    for (i=1;i<=n;i++) cur[i]=Head[i];
    RG int u=S;
    RG int Ans=0;
    while (Depth[S]<n)
    {
		if (u==T)
		{
			Ans+=ISAP();
			u=S;
		}
		RG bool flag=0;
		for (RG int now=cur[u];now!=-1;now=Next[now])
		{
			int v=E[now].v;
			if ((E[now].w>0)&&(Depth[u]==Depth[v]+1))
			{
				flag=1;
				Path[v]=now;
				cur[u]=now;
				u=v;
				break;
			}
		}
		if (!flag)
		{
			RG int MIN=n-1;
			for (i=Head[u];i!=-1;i=Next[i])
				if (E[i].w>0) MIN=min(MIN,Depth[E[i].v]);
			Gap[Depth[u]]--;
			if (Gap[Depth[u]]==0) break;
			Depth[u]=MIN+1;
			Gap[Depth[u]]++;
			cur[u]=Head[u];
			if (u!=S) u=E[Path[u]].u;
		}
    }
    printf("%d\n",Ans);
    return 0;
}

IL int read()
{
    char ch=getchar();int x=0;
    while ((ch>'9')||(ch<'0')) ch=getchar();
    while ((ch>='0')&&(ch<='9'))
    {
		x=x*10+ch-48;
		ch=getchar();
    }
    return x;
}

IL void Add_Edge(int u,int v,int w)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;E[cnt].u=u;E[cnt].v=v;E[cnt].w=w;
    cnt++;Next[cnt]=Head[v];Head[v]=cnt;E[cnt].u=v;E[cnt].v=u;E[cnt].w=w;
    return;
}

IL void Bfs()
{
    RG int h=1,t=0;
    Q[1]=T;
    mem(Depth,-1);
    Depth[T]=0;
    do
    {
		t++;if (t>=queuesize) t=0;RG int u=Q[t];
		Gap[Depth[u]]++;
		for (RG int i=Head[u];i!=-1;i=Next[i])
		{
			RG int v=E[i].v;
			if ((E[i].w==0)&&(Depth[v]==-1))
			{
				Depth[v]=Depth[u]+1;
				h++;if (h>=queuesize) h=0;
				Q[h]=v;
			}
		}
    }
    while (t!=h);
    return;
}

IL int ISAP()
{
    RG int u=T,flow=inf;
    while (u!=S)
    {
		flow=min(flow,E[Path[u]].w);
		u=E[Path[u]].u;
    }
    u=T;
    while (u!=S)
    {
		E[Path[u]].w-=flow;
		E[Path[u]^1].w+=flow;
		u=E[Path[u]].u;
    }
    return flow;
}
