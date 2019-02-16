#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const int maxM=801000;
const int inf=147483647;

int nb,ni,ns,m;
int Val[maxN];
vector<int> To[maxN];
int L1[maxN],L2[maxN],End[maxN];

bool Check(int val);

namespace FD
{
	int Mat[maxN][maxN];

	void Init();
	void Add_Edge(int u,int v,int w);
	void Do();
}

namespace FL
{
	class Edge
	{
	public:
		int v,flow;
	};

	int S,T,edgecnt,Head[maxN],Next[maxM];
	Edge E[maxM];
	int Q[maxN],Depth[maxN],cur[maxN];

	void Init();
	void Add_Edge(int u,int v,int flow);
	int Mxflow();
	bool Bfs();
	int dfs(int u,int flow);
}

int main()
{
	//freopen("input.in","r",stdin);//freopen("syc.out","w",stdout);
	scanf("%d%d%d%d",&nb,&ni,&ns,&m);FD::Init();
	//cout<<nb+ni+ni+ni+ns<<" "<<m<<endl;
	for (int i=1;i<=nb+ns;i++) scanf("%d",&Val[i]);
	for (int i=1;i<=ni;i++) scanf("%d",&L1[i]);
	for (int i=1;i<=ni;i++) scanf("%d",&L2[i]);
	for (int i=1;i<=ni;i++)
	{
		int k;scanf("%d",&k);
		while (k--)
		{
			int u;scanf("%d",&u);
			To[u].push_back(i);
		}
		scanf("%d",&End[i]);
	}
	for (int i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		FD::Add_Edge(u,v,w);
	}

	FD::Do();

	int L=0,R=0;
	for (int i=1;i<=ni;i++)
		for (int j=1;j<=ni;j++)
			if ((i!=j)&&(FD::Mat[i][j]<inf)) R=max(R,FD::Mat[i][j]);

	/*
	cout<<"L:"<<L<<endl;
	for (int i=1;i<=ni;i++) cout<<End[i]<<" ";cout<<endl;
	for (int i=nb+1;i<=nb+ns;i++)
	{
		for (int j=0;j<To[i].size();j++)
			cout<<"("<<i<<" "<<To[i][j]<<") "<<" "<<FD::Mat[To[i][j]][ni+1]<<endl;
		cout<<endl;
	}
	//*/

	int Ans=-1;

	do
	{
		int mid=(L+R)>>1;
		if (Check(mid)) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	while (L<=R);

	printf("%d\n",Ans);
	return 0;
}

bool Check(int val)
{
	//cout<<"Check:"<<val<<endl;
	FL::Init();
	FL::S=nb+ns+ni+ni+ni+1;FL::T=FL::S+1;
	int sum=0;
	for (int i=1;i<=nb;i++)
	{
		FL::Add_Edge(FL::S,i,Val[i]);sum+=Val[i];
		for (int j=0;j<To[i].size();j++) FL::Add_Edge(i,nb+ns+To[i][j],inf);
	}
	for (int i=nb+1;i<=ns+nb;i++)
	{
		FL::Add_Edge(FL::S,i,Val[i]);sum+=Val[i];
		for (int j=0;j<To[i].size();j++) FL::Add_Edge(i,nb+ns+ni+ni+To[i][j],inf);
	}
	for (int i=1;i<=ni;i++)
	{
		FL::Add_Edge(nb+ns+i,nb+ns+ni+i,L1[i]);
		if (End[i]) FL::Add_Edge(nb+ns+ni+i,FL::T,L2[i]),FL::Add_Edge(nb+ns+ni+ni+i,FL::T,inf);
		for (int j=1;j<=ni;j++)
			if ((i!=j)&&(FD::Mat[i][j]<=val)) FL::Add_Edge(nb+ns+ni+i,nb+ns+j,L2[i]),FL::Add_Edge(nb+ns+ni+ni+i,nb+ns+ni+ni+j,inf);
	}

	/*
	for (int i=1;i<=FL::T;i++)
		for (int j=FL::Head[i];j!=-1;j=FL::Next[j])
			if (FL::E[j].flow) cout<<i<<" -> "<<FL::E[j].v<<" "<<FL::E[j].flow<<endl;
	cout<<endl;
	//*/
	//cout<<"Build over"<<endl;
	//cout<<FL::edgecnt<<endl;

	int mxflow=FL::Mxflow();
	//cout<<"mxflow:"<<mxflow<<endl;

	return mxflow>=sum;
}

namespace FD
{
	void Init(){
		for (int i=1;i<=ni;i++) for (int j=1;j<=ni;j++) Mat[i][j]=inf;
		//for (int i=1;i<=ni;i++) Mat[i][i]=0;
		return;
	}

	void Add_Edge(int u,int v,int w){
		if (Mat[u][v]==inf) Mat[u][v]=Mat[v][u]=w;
		else Mat[u][v]=Mat[v][u]=Mat[u][v]+w;return;
	}

	void Do()
	{
		/*
		for (int i=1;i<=ni;i++)
		{
			for (int j=1;j<=ni;j++)
				if (Mat[i][j]!=inf) cout<<Mat[i][j]<<" ";
				else cout<<"-1 ";
			cout<<endl;
		}
		cout<<endl;
		//*/
		for (int k=1;k<=ni;k++)
			for (int i=1;i<=ni;i++)
				if (k!=i)
					for (int j=1;j<=ni;j++)
						if ((i!=j)&&(j!=k))
							Mat[i][j]=min(Mat[i][j],Mat[i][k]+Mat[k][j]);

		/*
		for (int i=1;i<=ni;i++)
		{
			for (int j=1;j<=ni;j++)
				if (Mat[i][j]!=inf) cout<<Mat[i][j]<<" ";
				else cout<<"-1 ";
			cout<<endl;
		}
		//*/
		//for (int i=1;i<=ni+1;i++) cout<<Mat[i][ni+1]<<" ";cout<<endl;
		return;
	}
}

namespace FL
{
	void Init(){
		edgecnt=-1;mem(Head,-1);return;
	}
	
	void Add_Edge(int u,int v,int flow){
		Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
		Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
		return;
	}
	
	int Mxflow(){
		int ret=0;
		while (Bfs())
		{
			for (int i=1;i<=T;i++) cur[i]=Head[i];
			while (int di=dfs(S,inf)) ret+=di;
		}
		return ret;
	}
	
	bool Bfs()
	{
		mem(Depth,-1);Depth[S]=1;Q[1]=S;
		int h=1,t=0;
		do
			for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
				if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
					Depth[Q[++h]=E[i].v]=Depth[u]+1;
		while (t!=h);
		return Depth[T]!=-1;
	}
	
	int dfs(int u,int flow)
	{
		if (u==T) return flow;
		for (int &i=cur[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
				if (int di=dfs(E[i].v,min(flow,E[i].flow))){
					E[i].flow-=di;E[i^1].flow+=di;return di;
				}
		return 0;
	}
}
