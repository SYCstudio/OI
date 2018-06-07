#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=20100;
const int maxM=maxN*2;
const int inf=2147483647;

int n,root,nowsum,Ans;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Size[maxN],mxSon[maxN];
int histcnt=0,Hist[maxN],Depth[maxN],Queue[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,int w);
void GetRoot(int u,int fa);
void Solve(int u);
int Calc(int u,int dep);
int gcd(int a,int b);

int main()
{
	ios::sync_with_stdio(false);
	mem(Head,-1);
	cin>>n;
	for (int i=1;i<n;i++)
	{
		int u,v,w;cin>>u>>v>>w;w=w%3;
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	mxSon[0]=inf;root=0;nowsum=n;
	GetRoot(1,0);
	Solve(root);
	int Sum=n*n;
	int g=gcd(Ans,Sum);
	printf("%d/%d\n",Ans/g,Sum/g);
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void GetRoot(int u,int fa)
{
	Size[u]=1;mxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
		{
			GetRoot(V[i],u);Size[u]+=Size[V[i]];
			mxSon[u]=max(mxSon[u],Size[V[i]]);
		}
	mxSon[u]=max(mxSon[u],nowsum-Size[u]);
	if (mxSon[u]<mxSon[root]) root=u;
	return;
}

void Solve(int u)
{
	Ans+=Calc(u,0);
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			Ans-=Calc(V[i],W[i]);
			nowsum=Size[V[i]];root=0;
			GetRoot(V[i],0);
			Solve(root);
		}
	return;
}

int Calc(int u,int dep)
{
	Depth[u]=dep;histcnt++;Hist[u]=histcnt;
	int h=1,t=0;Queue[1]=u;
	int Cnt[4]={0,0,0,0};
	do
	{
		int u=Queue[++t];Cnt[Depth[u]%3]++;
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((vis[V[i]]==0)&&(Hist[V[i]]!=histcnt))
			{
				Hist[V[i]]=histcnt;Depth[V[i]]=(Depth[u]+W[i]);
				Queue[++h]=V[i];
			}
	}
	while (t!=h);
	return Cnt[0]+Cnt[0]*(Cnt[0]-1)+Cnt[1]*Cnt[2]*2;
}

int gcd(int a,int b)
{
	int tmp;
	while (b) tmp=a,a=b,b=tmp%b;
	return a;
}
