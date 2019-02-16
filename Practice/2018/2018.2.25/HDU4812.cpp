#pragma comment(linker,"/STACK:102400000,102400000")
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int maxM=maxN*2;
const int Mod=1e6+3;
const int inf=1061109567;

int n;
ll K;
int nowsum,root,Ans1=inf,Ans2=inf;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll Node[maxN];
int Size[maxN],mxSon[maxN];
ll Inv[Mod+10],Depth[maxN];
bool vis[maxN];
int stacktop=0,Stack[maxN];
int Min[Mod+10];

void Add_Edge(int x,int y);
void GetRoot(int u,int fa);
void Solve(int u);
void GetAns(int u,int fa,ll ret);
void Modify(int u,int v);

int main()
{
	ios::sync_with_stdio(false);
	Inv[1]=1;
	for (int i=2;i<Mod;i++) Inv[i]=((ll)(Mod-Mod/i)*(ll)Inv[Mod%i]+Mod)%Mod;//预处理逆元
	while (cin>>n>>K)
	{
		edgecnt=0;Ans1=Ans2=inf;mem(vis,0);mem(Head,-1);mem(Min,63);
		for (int i=1;i<=n;i++) cin>>Node[i];
		for (int i=1;i<=n;i++) Node[i]=Node[i]%Mod;
		for (int i=1;i<n;i++)
		{
			int x,y;cin>>x>>y;
			Add_Edge(x,y);Add_Edge(y,x);
		}
		mxSon[0]=inf;root=0;nowsum=n;
		GetRoot(1,0);
		Solve(root);
		if ((Ans1==inf)||(Ans2==inf)) printf("No solution\n");
		else printf("%d %d\n",Ans1,Ans2);
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
	stacktop=0;
	Min[Node[u]]=u;
	//cout<<"root:"<<root<<endl;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			int lasttop=stacktop;
			GetAns(V[i],u,1);
			for (int j=lasttop+1;j<=stacktop;j++)
			{
				ll w=Depth[Stack[j]]*Node[u]%Mod;
				Min[w]=min(Min[w],Stack[j]);
				//cout<<Stack[j]<<":"<<w<<endl;
			}
		}
	//for (int i=1;i<=stacktop;i++) cout<<Stack[i]<<" ";cout<<endl;
	vis[u]=1;
	for (int i=1;i<=stacktop;i++)
	{
		ll w=Depth[Stack[i]]*Node[u]%Mod;
		Min[w]=inf;
	}
	Min[Node[u]]=inf;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			root=0;nowsum=Size[V[i]];
			GetRoot(V[i],0);
			Solve(root);
		}
	return;
}

void GetAns(int u,int fa,ll ret)
{
	//cout<<"bret:"<<ret<<endl;
	ret=ret*Node[u]%Mod;
	Depth[u]=ret;Stack[++stacktop]=u;
	//cout<<u<<" ret:"<<ret<<" inv:"<<K*Inv[ret]%Mod<<endl;
	Modify(u,Min[K*Inv[ret]%Mod]);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa))
			GetAns(V[i],u,ret);
	return;
}

void Modify(int u,int v)
{
	if (u>v) swap(u,v);
	if (v==inf) return;
	//cout<<"Mofy:"<<u<<" "<<v<<endl;
	if (Ans1>u) {
		Ans1=u;Ans2=v;
	}
	else if ((Ans1==u)&&(Ans2>v)) {
		Ans1=u;Ans2=v;
	}
	return;
}
