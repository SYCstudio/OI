#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int maxM=maxN*2;
const int inf=2147483647;

int n,K,Ans;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int root,Size[maxN],mxSon[maxN],nowsum;
bool vis[maxN];
int Depth[maxN],scnt,SortData[maxN];
int Queue[maxN],Fa[maxN];

void Add_Edge(int u,int v,int w);
void GetRoot(int u,int fa);
void Solve(int u);
int Calc(int u,int dep);

int main()
{
	ios::sync_with_stdio(false);
	while (cin>>n>>K)
	{
		if ((n==0)&&(K==0)) break;
		edgecnt=0;Ans=0;mem(Head,-1);mem(vis,0);
		for (int i=1;i<n;i++)
		{
			int u,v,w;cin>>u>>v>>w;
			Add_Edge(u,v,w);Add_Edge(v,u,w);
		}
		mxSon[0]=inf;
		root=0;nowsum=n;
		GetRoot(1,0);
		Solve(root);
		printf("%d\n",Ans);
	}
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
			Ans-=Calc(V[i],W[i]);nowsum=Size[V[i]];
			root=0;GetRoot(V[i],0);
			Solve(root);
		}
	return;
}

int Calc(int u,int dep)
{
	Depth[u]=dep;scnt=0;Fa[u]=0;
	int h=1,t=0;Queue[1]=u;
	do
	{
		int u=Queue[++t];
		SortData[++scnt]=Depth[u];
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((vis[V[i]]==0)&&(V[i]!=Fa[u]))
			{
				Fa[V[i]]=u;Depth[V[i]]=Depth[u]+W[i];
				Queue[++h]=V[i];
			}
	}
	while (t!=h);
	sort(&SortData[1],&SortData[scnt+1]);
	//cout<<"u:"<<u<<" scnt:"<<scnt<<endl;
	//for (int i=1;i<=scnt;i++) cout<<SortData[i]<<" ";cout<<endl;
	int l=1,r=scnt,ret=0;
	while (l<r)
	{
		if (SortData[l]+SortData[r]<=K) ret=ret+r-l,l++;
		else r--;
	}
	//cout<<"ret:"<<ret<<endl;
	return ret;
}
