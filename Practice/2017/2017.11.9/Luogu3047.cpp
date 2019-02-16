#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=100010;
const int maxK=22;
const int inf=2147483647;

int n,K;
int C[maxN];
int cnt=0,Head[maxN],Next[maxN*2],V[maxN*2];
int F[maxN][maxK];

void Add_Edge(int u,int v);
void dfs1(int u,int father);
void dfs2(int u,int father,int S[maxK]);

int main()
{
    mem(Head,-1);
    scanf("%d%d",&n,&K);
    for (int i=1;i<n;i++)
    {
	int u,v;
	scanf("%d%d",&u,&v);
	Add_Edge(u,v);Add_Edge(v,u);
    }
    for (int i=1;i<=n;i++) scanf("%d",&C[i]);
    dfs1(1,1);
    /*
    cout<<endl;
    for (int i=1;i<=n;i++)
    {
	for (int j=0;j<=K;j++)
	    cout<<F[i][j]<<" ";
	cout<<endl;
    }
    cout<<endl;
    //*/
    int S[maxK];mem(S,0);
    dfs2(1,1,S);
    /*
    cout<<endl;
    for (int i=1;i<=n;i++)
    {
	for (int j=0;j<=K;j++)
	    cout<<F[i][j]<<" ";
	cout<<endl;
    }
    cout<<endl;
    //*/
    for (int i=1;i<=n;i++)
    {
	int sum=0;
	for (int j=0;j<=K;j++) sum+=F[i][j];
	printf("%d\n",sum);
    }
    return 0;
}

void Add_Edge(int u,int v)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;V[cnt]=v;
    return;
}

void dfs1(int u,int father)
{
    F[u][0]=C[u];
    for (int i=Head[u];i!=-1;i=Next[i])
    {
	int v=V[i];if (v==father) continue;
	dfs1(v,u);
	for (int i=0;i<K;i++)
	    F[u][i+1]+=F[v][i];
    }
    return;
}

void dfs2(int u,int father,int S[maxK])
{
    //cout<<u<<":";
    //for (int i=0;i<=K;i++) cout<<S[i]<<" ";
    //cout<<endl;
    for (RG int i=0;i<=K;i++) S[i]+=F[u][i];
    int SS[maxK];
    for (RG int i=Head[u];i!=-1;i=Next[i])
    {
	RG int v=V[i];if (v==father) continue;
	//mem(SS,0);
	for (int i=0;i<=K;i++) SS[i]=S[i];
	for (int i=1;i<=K;i++) SS[i]=SS[i]-F[v][i-1];
	for (int i=K;i>=1;i--) SS[i]=SS[i-1];
	SS[0]=0;
	dfs2(v,u,SS);
    }
    for (int i=0;i<=K;i++) F[u][i]=S[i];
    return;
}
