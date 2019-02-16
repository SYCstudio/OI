#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=401000;
const int maxM=maxN*2;
const ld eps=1e-4;
const int inf=2147483647;
const ll INF=1e17;

int n,m,D,U;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int root,nowsize,Size[maxN],mxSon[maxN],Depth[maxN];
int rtcnt,Rt[maxN],Q[maxN];
ld F[maxN],G[maxN],Val[maxN],W[maxM];
vector<int> Son[maxN];
bool vis[maxN],inq[maxN];

void Add_Edge(int u,int v,int w);
void GetRoot(int u,int fa);
void RootInit(int u);
bool Check(ld k);
bool Calc(int u);
int dfs(int u,int fa);
void Bfs(int S);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	scanf("%d%d",&D,&U);
	ld L=inf,R=0,Ans;
	for (int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);
		L=min(L,(ld)w);R=max(R,(ld)w);
	}

	root=0;mxSon[0]=inf;nowsize=n;
	GetRoot(1,0);
	RootInit(root);

	//for (int i=1;i<=n;i++) cout<<Rt[i]<<" ";cout<<endl;
	
	do
	{
		ld mid=(L+R)/2.0;
		//cout<<"("<<L<<","<<R<<")"<<endl;
		if (Check(mid)) Ans=mid,L=mid+eps;
		else R=mid-eps;
	}
	while (L+eps<=R);

	printf("%.3LF\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
	return;
}

void GetRoot(int u,int fa)
{
	Size[u]=1;mxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
		{
			GetRoot(V[i],u);
			Size[u]+=Size[V[i]];mxSon[u]=max(mxSon[u],Size[V[i]]);
		}
	mxSon[u]=max(mxSon[u],nowsize-Size[u]);
	if (mxSon[u]<mxSon[root]) root=u;
	return;
}

void RootInit(int u)
{
	vis[u]=1;Rt[++rtcnt]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			nowsize=Size[V[i]];root=0;
			GetRoot(V[i],0);
			RootInit(root);
		}
	return;
}

bool Check(ld k)
{
	//cout<<"Check:"<<k<<endl;
	mem(vis,0);
	for (int i=1;i<=edgecnt;i++) W[i]-=k;

	bool flag=0;
	for (int i=1;i<=n;i++)
		if (Calc(Rt[i])){
			flag=1;break;
		}
	
	for (int i=1;i<=edgecnt;i++) W[i]+=k;
	//cout<<endl;
	return flag;
}

bool Calc(int u)
{
	vis[u]=1;
	//cout<<"Calc:"<<u<<endl;
	int mxdep=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			Depth[V[i]]=1;
			int dep=dfs(V[i],V[i]);
			mxdep=max(mxdep,dep);
			Son[dep].push_back(V[i]);
		}
	/*
	cout<<"mxdep:"<<mxdep<<endl;
	for (int i=1;i<=mxdep;i++)
	{
		for (int j=0;j<Son[i].size();j++)
			cout<<Son[i][j]<<" ";
		cout<<endl;
	}
	//*/
	bool flag=0;
	mxdep=min(mxdep,U);
	for (int i=1;i<=mxdep;i++) F[i]=-INF;
	for (int d=1;d<=mxdep;d++)
	{
		if (flag==0)
		{
			for (int p=0;p<Son[d].size();p++)
			{
				int v=Son[d][p];
				//cout<<"v:"<<v<<endl;
				for (int j=1;j<=d;j++) G[j]=-INF;
				for (int j=Head[v];j!=-1;j=Next[j]) if (V[j]==u) Val[v]=W[j]/*,cout<<"v w:"<<W[j]<<endl*/;
				Bfs(v);
				//cout<<"F:";for (int j=1;j<=d;j++) cout<<F[j]<<" ";cout<<endl;
				//cout<<"G:";for (int j=1;j<=d;j++) cout<<G[j]<<" ";cout<<endl;
				int pos=d,l=1,r=0;
				for (int i=1;i<=d;i++)
				{
					while ((pos>=0)&&(pos+i>=D))
					{
						while ((l<=r)&&(F[Q[r]]<=F[pos])) r--;
						Q[++r]=pos--;
					}
					while ((l<=r)&&(i+Q[l]>U)) l++;
					//cout<<"Cmp? "<<" "<<Q[l]<<" "<<i<<endl;
					//cout<<"["<<l<<","<<r<<"]"<<endl;
					//for (int k=l;k<=r;k++) cout<<Q[k]<<" ";cout<<endl;
					if ((l<=r)&&(F[Q[l]]+G[i]>=0)) flag=1;
				}
				for (int i=1;i<=d;i++) F[i]=max(F[i],G[i]);
				if (flag) break;
				//for (int i=1;i<=d;i++) cout<<F[i]<<" ";cout<<endl;
			}
		}
		Son[d].clear();
	}
	return flag;
}

int dfs(int u,int fa)
{
	int Ret=Depth[u];
	if (Depth[u]>=U) return Ret;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
		{
			Depth[V[i]]=Depth[u]+1;
			Ret=max(Ret,dfs(V[i],u));
		}
	return Ret;
}

void Bfs(int S)
{
	int h=1,t=0;Q[1]=S;
	inq[S]=1;Depth[S]=1;
	do
	{
		int u=Q[++t];G[Depth[u]]=max(G[Depth[u]],Val[u]);
		if (Depth[u]>=U) continue;
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((vis[V[i]]==0)&&(inq[V[i]]==0))
			{
				inq[V[i]]=1;Depth[V[i]]=Depth[u]+1;Val[V[i]]=Val[u]+W[i];
				Q[++h]=V[i];
			}
	}
	while (t!=h);
	for (int i=1;i<=t;i++) inq[Q[i]]=0;
	return;
}

