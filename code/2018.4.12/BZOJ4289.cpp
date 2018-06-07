#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxM=maxN*2;
const int inf=2147483647;
const ll INF=1e17;

class EDGE
{
public:
	int u,v;
	int uu,vv;
	ll w;
};

class Edge
{
public:
	int v;ll w;
};

class HeapData
{
public:
	int u;ll dist;
};

int n,m,nodecnt;
vector<int> Eid[maxN];
EDGE EE[maxM];
int edgecnt=0,Head[maxN<<1],Next[maxM<<3];
Edge E[maxM<<3];
ll Dist[maxM<<1];
priority_queue<HeapData> H;
bool vis[maxM<<1];

bool cmp(int id1,int id2);
bool operator < (HeapData A,HeapData B);
void Add_Edge(int u,int v,ll w);

int main()
{
	mem(Head,-1);
	//ios::sync_with_stdio(false);
	scanf("%d%d",&n,&m);//cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		//cin>>EE[i].u>>EE[i].v>>EE[i].w;
		scanf("%d%d%lld",&EE[i].u,&EE[i].v,&EE[i].w);
		Eid[EE[i].u].push_back(i);
		Eid[EE[i].v].push_back(i);
	}
	for (int i=1;i<=n;i++)
	{
		if (Eid[i].size()==0) continue;
		sort(Eid[i].begin(),Eid[i].end(),cmp);
		if (i==1)
		{
			nodecnt++;
			Add_Edge(nodecnt,nodecnt+1,EE[Eid[i][0]].w);
			Add_Edge(nodecnt+1,nodecnt,0);
		}
		nodecnt++;
		if (EE[Eid[i][0]].u==i) EE[Eid[i][0]].uu=nodecnt;
		else EE[Eid[i][0]].vv=nodecnt;
		for (int j=1;j<Eid[i].size();j++)
		{
			nodecnt++;
			if (EE[Eid[i][j]].u==i) EE[Eid[i][j]].uu=nodecnt;
			else EE[Eid[i][j]].vv=nodecnt;
			Add_Edge(nodecnt,nodecnt-1,0);Add_Edge(nodecnt-1,nodecnt,EE[Eid[i][j]].w-EE[Eid[i][j-1]].w);
		}
	}
	for (int i=1;i<=m;i++) Add_Edge(EE[i].uu,EE[i].vv,EE[i].w),Add_Edge(EE[i].vv,EE[i].uu,EE[i].w);

    /*
	for (int i=1;i<=nodecnt;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			cout<<i<<"->"<<E[j].v<<" "<<E[j].w<<endl;
	//*/

	mem(Dist,-1);Dist[1]=0;H.push((HeapData){1,0});
	int cnt=0;
	do
	{
		int u=H.top().u;H.pop();
		if (vis[u]==1) continue;
		vis[u]=1;cnt++;if (cnt==nodecnt) break;
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((vis[E[i].v]==0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]>Dist[u]+E[i].w)))
			{
				Dist[E[i].v]=Dist[u]+E[i].w;
				H.push((HeapData){E[i].v,Dist[E[i].v]});
			}
	}
	while (!H.empty());
	ll Ans=INF;
	for (int i=1;i<=Eid[n].size();i++) Ans=min(Ans,Dist[nodecnt-i+1]);
	printf("%lld\n",Ans);//cout<<Ans<<endl;
	return 0;
}

bool cmp(int id1,int id2)
{
	return EE[id1].w<EE[id2].w;
}

bool operator < (HeapData A,HeapData B)
{
	return A.dist>B.dist;
}

void Add_Edge(int u,int v,ll w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
	E[edgecnt].v=v;E[edgecnt].w=w;
	return;
}
