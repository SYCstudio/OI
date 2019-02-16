#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100001*3;
const int maxMap=1000001;
const int maxM=maxN*8;
const int F1[9]={0,-1,-1,-1,0,1,1,1,0};
const int F2[9]={0,-1,0,1,1,1,0,-1,-1};
const int inf=2147483647;

int n,R,C;
int Ans=0;
int nodecnt=0,nnodecnt;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
map<int,int> Map[maxMap],Opt[maxMap];
int dfncnt=0,dfn[maxN],low[maxN],Id[maxN];

int idcnt=0,Size[maxN];
int stacktop=0,Stack[maxN];
bool instack[maxN];
int edgecnt2=0,Head2[maxN],Next2[maxN*2],V2[maxN*2],Indegree[maxN*2];
int Queue[maxN],F[maxN];
int Hang[maxMap],Lie[maxMap];
set<int> Set[maxN];

void Add_Edge(int u,int v);
void Add_Edge2(int u,int v);
void dfs(int u,int fa);
int GetHang(int h);
int GetLie(int l);

int main()
{
	ios::sync_with_stdio(false);
	mem(Head,-1);mem(Head2,-1);
	cin>>n>>R>>C;
	for (int i=1;i<=n;i++)
	{
		int x,y,opt;cin>>x>>y>>opt;
		Map[x][y]=++nodecnt;Opt[x][y]=opt;
	}
	nnodecnt=nodecnt;
	for (int i=1;i<=R;i++)
		for (map<int,int>::iterator j=Map[i].begin();j!=Map[i].end();j++)
		{
			//cout<<"("<<i<<","<<j->first<<")"<<endl;
			Add_Edge(GetHang(i),j->second);Add_Edge(GetLie(j->first),j->second);
			if (Opt[i][j->first]==1) Add_Edge(j->second,GetHang(i));
			else if (Opt[i][j->first]==2) Add_Edge(j->second,GetLie(j->first));
			else for (int f=1;f<=8;f++) if (Map[i+F1[f]].count(j->first+F2[f])!=0) Add_Edge(j->second,Map[i+F1[f]][j->first+F2[f]]);
		}
	for (int i=1;i<=nodecnt;i++)
		if (dfn[i]==0) dfs(i,i);
	/*
	for (int i=1;i<=nodecnt+R+C;i++) printf("%3d",i);printf("\n");
	for (int i=1;i<=nodecnt+R+C;i++) printf("%3d",dfn[i]);printf("\n");
	for (int i=1;i<=nodecnt+R+C;i++) printf("%3d",low[i]);printf("\n");
	for (int i=1;i<=nodecnt+R+C;i++) printf("%3d",Id[i]);printf("\n");
	for (int i=1;i<=idcnt;i++) cout<<Size[i]<<" ";cout<<endl;
	//*/
	for (int i=1;i<=nodecnt;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			if ((Id[i]!=Id[V[j]])&&(Set[i].count(V[j])==0))
				Add_Edge2(Id[i],Id[V[j]]),Set[i].insert(V[j]);
	int h=0,t=0;
	for (int i=1;i<=idcnt;i++) if (Indegree[i]==0) Queue[++h]=i;
	do
	{
		int u=Queue[++t];
		for (int i=Head2[u];i!=-1;i=Next2[i])
		{
			F[V2[i]]=max(F[V2[i]],F[u]+Size[u]);
			Indegree[V2[i]]--;if (Indegree[V2[i]]==0) Queue[++h]=V2[i];
		}
	}
	while (t!=h);
	for (int i=1;i<=idcnt;i++) Ans=max(Ans,F[i]+Size[i]);
	printf("%d\n",Ans);
	return 0;
}

void Add_Edge(int u,int v)
{
	//cout<<"Add:"<<u<<" "<<v<<endl;
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	//edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void Add_Edge2(int u,int v)
{
	//cout<<"Add2:"<<u<<" "<<v<<endl;
	edgecnt2++;Next2[edgecnt2]=Head2[u];Head2[u]=edgecnt2;V2[edgecnt2]=v;
	Indegree[v]++;
	return;
}

void dfs(int u,int fa)
{
	dfn[u]=low[u]=++dfncnt;
	Stack[++stacktop]=u;instack[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		//if (V[i]==fa) continue;
		if (dfn[V[i]]==0){
			dfs(V[i],u);low[u]=min(low[u],low[V[i]]);
		}
		else if (instack[V[i]]) low[u]=min(low[u],dfn[V[i]]);
	}
	if (dfn[u]==low[u]){
		int size=0,v;idcnt++;
		do{
			v=Stack[stacktop--];Id[v]=idcnt;instack[v]=0;if (v<=nnodecnt) size++;//cout<<v<<" ";
		}
		while (u!=v);
		//cout<<endl;
		Size[idcnt]=size;
	}
	return;
}

int GetHang(int h)
{
	if (Hang[h]==0) Hang[h]=++nodecnt;
	return Hang[h];
}

int GetLie(int l)
{
	if (Lie[l]==0) Lie[l]=++nodecnt;
	return Lie[l];
}
