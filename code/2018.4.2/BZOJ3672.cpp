#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200010;
const int maxM=maxN*2;
const int inf=2147483647;

class Data
{
public:
	ll p,q,l;
};

class Edge
{
public:
	int v;ll w;
};

int n;
int edgecnt=0,Head[maxN],Next[maxM];
Edge E[maxM];
int nowsum,root,Size[maxN],mxSon[maxN],Fa[maxN];
ll F[maxN],Dist[maxN];
int qh,Queue[maxN],Stack[maxN];
Data P[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,int w);
void dfs_init(int u,int fa);
void GetRoot(int u,int fa);
void Divide(int u);
bool cmp(int u,int v);
void dfs(int u,int fa);
ld Slope(int u,int v);

int main()
{
	ios::sync_with_stdio(false);mem(Head,-1);mem(F,63);
	
	cin>>n;int opt;cin>>opt;
	for (int i=2;i<=n;i++)
	{
		ll fa,dis;cin>>fa>>dis>>P[i].p>>P[i].q>>P[i].l;
		Add_Edge(i,fa,dis);Add_Edge(fa,i,dis);
	}
	Dist[1]=0;F[1]=0;
	dfs_init(1,1);
	nowsum=n;root=0;mxSon[0]=inf;
	Divide(1);

	for (int i=2;i<=n;i++) cout<<F[i]<<endl;
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].w=w;
	return;
}

void dfs_init(int u,int fa)
{
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (E[i].v!=fa)
		{
			Fa[E[i].v]=u;Dist[E[i].v]=Dist[u]+E[i].w;
			dfs_init(E[i].v,u);
			Size[u]+=Size[E[i].v];
		}
	return;
}

void GetRoot(int u,int fa)
{
	Size[u]=1;mxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].v!=fa)&&(vis[E[i].v]==0))
		{
			GetRoot(E[i].v,u);
			Size[u]+=Size[E[i].v];
			mxSon[u]=max(mxSon[u],Size[E[i].v]);
		}
	mxSon[u]=max(mxSon[u],nowsum-Size[u]);
	if (mxSon[u]<mxSon[root]) root=u;
	return;
}

void Divide(int u)
{
	if (nowsum<=1) return;
	root=0;GetRoot(u,u);int nowroot=root;
	
	nowsum=Size[u]-Size[root];vis[root]=1;
	Divide(u);

	//cout<<u<<" "<<nowroot<<" "<<nowsum<<endl;
	for (int i=nowroot;i!=Fa[u];i=Fa[i])
		if (P[nowroot].l>=Dist[nowroot]-Dist[i])
		{
			//cout<<"Upt:"<<i<<"->"<<nowroot<<endl;
			F[nowroot]=min(F[nowroot],F[i]+(Dist[nowroot]-Dist[i])*P[nowroot].p+P[nowroot].q);
		}
	//else cout<<"Fail:"<<i<<"->"<<nowroot<<endl;

	qh=0;
	for (int i=Head[nowroot];i!=-1;i=Next[i])
		if ((vis[E[i].v]==0)&&(E[i].v!=Fa[nowroot])) dfs(E[i].v,nowroot);
	sort(&Queue[1],&Queue[qh+1],cmp);
	//cout<<"Queue:";for (int i=1;i<=qh;i++) cout<<Queue[i]<<" ";cout<<endl;

	int stacktop=0;
	for (int i=1,j=nowroot;i<=qh;i++)
	{
		while ((j!=Fa[u])&&(Dist[j]>=Dist[Queue[i]]-P[Queue[i]].l))
		{
			while ((stacktop>=2)&&(Slope(Stack[stacktop],Stack[stacktop-1])<=Slope(Stack[stacktop],j))) stacktop--;
			Stack[++stacktop]=j;
			j=Fa[j];
		}
		//cout<<i<<" node:"<<Queue[i]<<endl;
		//cout<<"Stack:";for (int k=1;k<=stacktop;k++) cout<<Stack[k]<<" ";cout<<endl;
		if (stacktop==1)
		{
			//cout<<"Case1"<<endl;
			if (Dist[Stack[stacktop]]>=Dist[Queue[i]]-P[Queue[i]].l)
				F[Queue[i]]=min(F[Queue[i]],F[Stack[stacktop]]+(Dist[Queue[i]]-Dist[Stack[stacktop]])*P[Queue[i]].p+P[Queue[i]].q);
		}
		else
		{
			int fd=1,l=1,r=stacktop;
			//cout<<"Case2"<<endl;
			do
			{
				int mid=(l+r)>>1;
				/*
				if (mid==stacktop){
					fd=mid;break;
				}
				//*/
				if (Slope(Stack[mid],Stack[mid+1])>=P[Queue[i]].p) fd=mid+1,l=mid+1;
				else r=mid-1;
			}
			while (l<=r);
			fd=min(fd,stacktop);
			//cout<<"find:"<<fd<<endl;
			if (Dist[Stack[fd]]>=Dist[Queue[i]]-P[Queue[i]].l)
				F[Queue[i]]=min(F[Queue[i]],F[Stack[fd]]+(Dist[Queue[i]]-Dist[Stack[fd]])*P[Queue[i]].p+P[Queue[i]].q);
		}
	}
	//cout<<endl;

	for (int i=Head[nowroot];i!=-1;i=Next[i])
		if (vis[E[i].v]==0){
			nowsum=Size[E[i].v];Divide(E[i].v);
		}
	return;
}

void dfs(int u,int fa)
{
	Queue[++qh]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].v!=fa)&&(vis[E[i].v]==0)) dfs(E[i].v,u);
	return;
}

bool cmp(int u,int v)
{
	return Dist[u]-P[u].l>Dist[v]-P[v].l;
}

ld Slope(int u,int v)
{
	return 1.0*(F[u]-F[v])/(1.0*(Dist[u]-Dist[v]));
}
