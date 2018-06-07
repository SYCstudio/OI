#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10010;
const int maxM=100010*2;
const int inf=2147483647;

class Edge
{
public:
    int u,v,w;
};

int n,m,S,T;
int cnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],cur[maxN],Gap[maxN],Q[maxN];
int PathEdge[maxN];

void Add_Edge(int u,int v,int w);
bool Bfs();
int ISAP();

int main()
{
    mem(Head,-1);
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for (int i=1;i<=m;i++)
    {
	int u,v,w;scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u,v,w);
    }
    if (Bfs()==0)
    {
	printf("0\n");
	return 0;
    }
    for (int i=1;i<=n;i++) cur[i]=Head[i];
    int u=S;
    int Ans=0;
    while (Depth[S]<n)
    {
	/*
	cout<<"now:"<<u<<endl;
	for (int i=1;i<=n;i++)
	{
	    cout<<i<<":"<<endl;
	    for (int j=Head[i];j!=-1;j=Next[j])
		cout<<E[j].u<<"->"<<E[j].v<<" "<<E[j].w<<endl;
	}
	cout<<"Depth:";
	for (int i=1;i<=n;i++) cout<<Depth[i]<<" ";
	cout<<endl;
	cout<<"Gap:";
	for (int i=1;i<=n;i++) cout<<Gap[i]<<" ";
	cout<<endl;
	//*/
	if (u==T)
	{
	    Ans+=ISAP();
	    u=S;
	}
	bool flag=0;//是否存在增广
	for (int &i=cur[u];i!=-1;i=Next[i])
	{
	    int v=E[i].v;
	    //cout<<"Augu:"<<E[i].u<<"->"<<E[i].v<<" "<<E[i].w<<endl;
	    if ((E[i].w>0)&&(Depth[u]==Depth[v]+1))
	    {
		//cout<<"ZG:"<<u<<"->"<<v<<" "<<E[i].w<<endl;
		flag=1;
		PathEdge[v]=i;
		u=v;
		break;
	    }
	}
	//cout<<"flag:"<<flag<<endl;
	if (!flag)
	{
	    int MIN=n-1;
	    for (int i=Head[u];i!=-1;i=Next[i])
	    {
		int v=E[i].v;
		if (E[i].w>0) MIN=min(MIN,Depth[v]);
	    }
	    Gap[Depth[u]]--;
	    if (Gap[Depth[u]]==0) break;
	    //cout<<"Depth Update:["<<u<<"] "<<Depth[u]<<"->"<<MIN+1<<endl;
	    Depth[u]=MIN+1;
	    Gap[Depth[u]]++;
	    cur[u]=Head[u];
	    if (u!=S) u=E[PathEdge[u]].u;
	}
	//cout<<endl;
    }
    printf("%d\n",Ans);
    return 0;
}

void Add_Edge(int u,int v,int w)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;
    E[cnt].u=u;E[cnt].v=v;E[cnt].w=w;

    cnt++;Next[cnt]=Head[v];Head[v]=cnt;
    E[cnt].u=v;E[cnt].v=u;E[cnt].w=0;
    return;
}

bool Bfs()
{
    int h=1,t=0;
    mem(Depth,-1);
    Q[1]=T;
    Depth[T]=0;
    do
    {
	t++;int u=Q[t];
	Gap[Depth[u]]++;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=E[i].v;
	    if ((E[i].w==0)&&(Depth[v]==-1))
	    {
		Depth[v]=Depth[u]+1;
		h++;Q[h]=v;
	    }
	}
    }
    while (t<h);
    /*
    for (int i=1;i<=n;i++) cout<<Depth[i]<<" ";
    cout<<endl;
    //*/
    if (Depth[S]==-1) return 0;
    return 1;
}

int ISAP()
{
    int u=T,flow=inf;
    while (u!=S)
    {
	flow=min(flow,E[PathEdge[u]].w);
	u=E[PathEdge[u]].u;
    }
    u=T;
    while (u!=S)
    {
	E[PathEdge[u]].w-=flow;
	E[PathEdge[u]^1].w+=flow;
	u=E[PathEdge[u]].u;
    }
    return flow;
}
