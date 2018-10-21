#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxDay=110;
const int maxN=21;
const int maxM=maxN*maxN*2;
const int maxQueue=maxN*1000;
const int inf=21474836;

int Day,n,m,K;
int Cant[maxDay];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Cost[maxDay][maxDay];
int Queue[maxQueue],Dist[maxN];
bool inqueue[maxN];
int F[maxDay];

void Add_Edge(int u,int v,int w);
void _Add(int u,int v,int w);
int Spfa(int l,int r);

int main()
{
	mem(Head,-1);
	scanf("%d%d%d%d",&Day,&n,&K,&m);
	for (int i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);u--;v--;
		Add_Edge(u,v,w);
	}
	int d;scanf("%d",&d);
	for (int i=1;i<=d;i++)
	{
		int P,l,r;scanf("%d%d%d",&P,&l,&r);
		P--;
		for (int j=l;j<=r;j++) Cant[j]|=(1<<P);
	}
	for (int i=1;i<=Day;i++)
		for (int j=i;j<=Day;j++)
			Cost[i][j]=Spfa(i,j);
	/*
	for (int i=1;i<=Day;i++)
	{
		for (int j=i;j<=Day;j++) cout<<Cost[i][j]<<" ";
		cout<<endl;
	}
	//*/
	mem(F,63);F[0]=0;
	for (int i=1;i<=Day;i++)
	{
		F[i]=Cost[1][i]*i;
		for (int j=0;j<i;j++)
			F[i]=min(F[i],F[j]+(i-j)*Cost[j+1][i]+K);
	}
	printf("%d\n",F[Day]);
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	_Add(u,v,w);_Add(v,u,w);
	return;
}

void _Add(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

int Spfa(int l,int r)
{
	int cant=0;
	for (int i=l;i<=r;i++) cant|=Cant[i];
	mem(Dist,-1);Dist[0]=0;
	int h=1,t=0;Queue[1]=0;
	do
	{
		t++;if (t==maxQueue) t=0;
		int u=Queue[t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if (((1<<V[i])&cant)==0)
				if ((Dist[V[i]]==-1)||(Dist[u]+W[i]<Dist[V[i]]))
				{
					Dist[V[i]]=Dist[u]+W[i];
					if (inqueue[V[i]]==0)
					{
						h++;if (h==maxQueue) h=0;
						inqueue[Queue[h]=V[i]]=1;
					}
				}
		inqueue[u]=0;
	}
	while (t!=h);
	if (Dist[n-1]==-1) return inf;
	return Dist[n-1];
}
