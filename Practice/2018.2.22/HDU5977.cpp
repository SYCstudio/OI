#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50010;
const int maxM=maxN*2;
const int maxBit=10;
const int inf=2147483647;

int n,K;
ll Ans;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],NodeW[maxN];
int root,nowsum,Size[maxN],mxSon[maxN];
int histcnt,Hist[maxN];
int Queue[maxN],Path[maxN];
ll Cnt[1<<(maxBit+1)];
int Stack[maxN];
bool vis[maxN];

void Add_Edge(int u,int v);
void GetRoot(int u,int fa);
void Solve(int u);
ll Calc(int u,int init);

int main()
{
	ios::sync_with_stdio(false);
	while (cin>>n>>K)
	{
		edgecnt=0;mem(Head,-1);mem(vis,0);Ans=0;
		for (int i=1;i<=n;i++){
			cin>>NodeW[i];NodeW[i]=1<<(NodeW[i]-1);
		}
		for (int i=1;i<n;i++)
		{
			int u,v;cin>>u>>v;
			Add_Edge(u,v);Add_Edge(v,u);
		}
		root=0;mxSon[0]=inf;nowsum=n;
		GetRoot(1,0);//cout<<"root:"<<root<<endl;
		Solve(root);
		printf("%lld\n",Ans);
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void GetRoot(int u,int fa)
{
	Size[u]=1;mxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)){
			GetRoot(V[i],u);Size[u]+=Size[V[i]];mxSon[u]=max(mxSon[u],Size[V[i]]);
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
			Ans-=Calc(V[i],NodeW[u]);
			nowsum=Size[V[i]];root=0;
			GetRoot(V[i],0);
			Solve(root);
		}
	return;
}

ll Calc(int u,int init)
{
	mem(Cnt,0);
	histcnt++;Hist[u]=histcnt;
	Path[u]=init|NodeW[u];
	int h=1,t=0;Queue[1]=u;
	int stacktop=0;
	do
	{
		int u=Queue[++t];Cnt[Path[u]]++;Stack[++stacktop]=Path[u];
		//cout<<u<<" "<<Path[u]<<endl;
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((vis[V[i]]==0)&&(Hist[V[i]]!=histcnt))
			{
				Hist[V[i]]=histcnt;Path[V[i]]=Path[u]|NodeW[V[i]];
				Queue[++h]=V[i];
			}
	}
	while (t!=h);
	//for (int i=0;i<(1<<K);i++) cout<<i<<":"<<Cnt[i]<<endl;cout<<endl;
	for (int i=0;i<K;i++)
		for (int j=0;j<(1<<K);j++)
			if ((j&(1<<i))==0) Cnt[j]+=Cnt[j|(1<<i)];
	//for (int i=0;i<(1<<K);i++) cout<<i<<":"<<Cnt[i]<<endl;cout<<endl;
	ll ret=0;
	for (int i=1;i<=stacktop;i++) ret=ret+Cnt[Stack[i]^((1<<K)-1)];
	return ret;
}
