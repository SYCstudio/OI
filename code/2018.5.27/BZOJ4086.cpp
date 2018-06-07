#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=5010*2;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],U[maxM],V[maxM];
bool Map[maxN][maxN],Ans[maxN][maxN];
int Cnt[maxN],Cnt1[maxN][maxN],Cnt2[maxN][maxN];
int Tim1[maxN][maxN],Tim2[maxN][maxN];
vector<int> Node[maxN][maxN];

void Add_Edge(int u,int v);
void Do2();
void Do3();
void Do4();
void Do5();
void Do6();
void Do7();

int main()
{
	//freopen("16.in","r",stdin);freopen("out.out","w",stdout);
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		//cerr<<TTT<<endl;
		edgecnt=0;mem(Head,-1);mem(Map,0);mem(Ans,0);
		int K;
		scanf("%d%d%d",&n,&m,&K);
		//cerr<<n<<" "<<m<<" "<<K<<endl;
		for (int i=1;i<=m;i++)
		{
			int u,v;scanf("%d%d",&u,&v);
			if ((Map[u][v])||(u==v)) continue;
			Add_Edge(u,v);Map[u][v]=Map[v][u]=1;
		}
		if (K==2) Do2();
		if (K==3) Do3();
		if (K==4) Do4();
		if (K==5) Do5();
		if (K==6) Do6();
		if (K==7) Do7();
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
				printf("%c",(Ans[i][j])?('Y'):('N'));
			printf("\n");
		}
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;U[edgecnt]=u;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;U[edgecnt]=v;
	return;
}

void Do2()
{
	for (int i=1;i<=edgecnt;i++) Ans[U[i]][V[i]]=1;
	return;
}

void Do3()
{
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			for (int k=Head[i];k!=-1;k=Next[k])
				if (Map[V[k]][j]) Ans[i][j]=Ans[j][i]=1;
	return;
}

void Do4()
{
	for (int x=1;x<=n;x++)
		for (int y=x+1;y<=n;y++)
			for (int i=Head[x];i!=-1;i=Next[i])
				if (V[i]!=y)
					for (int j=Head[y];j!=-1;j=Next[j])
						if ((V[i]!=V[j])&&(V[j]!=x)&&(Map[V[i]][V[j]]))
							Ans[x][y]=Ans[y][x]=1;
	return;
}

void Do5()
{
	for (int p=1;p<=n;p++)
		for (int q=p+1;q<=n;q++)
		{
			int sum=0;mem(Cnt,0);
			for (int i=Head[p];i!=-1;i=Next[i])
				if ((V[i]!=q)&&(Map[V[i]][q]))
					Cnt[V[i]]++,sum++;
			for (int i=Head[p];i!=-1;i=Next[i])
				if (V[i]!=q)
					for (int j=Head[q];j!=-1;j=Next[j])
						if ((V[j]!=p)&&(V[i]!=V[j])&&(sum-Cnt[V[i]]-Cnt[V[j]]))
							Ans[V[i]][V[j]]=Ans[V[j]][V[i]]=1;
		}
	return;
}

void Do6()
{
	for (int p=1;p<=n;p++)
		for (int q=p+1;q<=n;q++)
		{
			int sum=0;mem(Cnt,0);
			for (int i=Head[p];i!=-1;i=Next[i])
				if (V[i]!=q)
					for (int j=Head[q];j!=-1;j=Next[j])
						if ((V[j]!=p)&&(V[i]!=V[j])&&(Map[V[i]][V[j]]))
							Cnt[V[i]]++,Cnt[V[j]]++,sum++;
			for (int i=Head[p];i!=-1;i=Next[i])
				if (V[i]!=q)
					for (int j=Head[q];j!=-1;j=Next[j])
						if ((V[j]!=p)&&(V[i]!=V[j])&&(sum-Cnt[V[i]]-Cnt[V[j]]+Map[V[i]][V[j]])) Ans[V[i]][V[j]]=Ans[V[j]][V[i]]=1;
		}
	return;
}

void Do7()
{
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Node[i][j].clear(),Tim1[i][j]=Tim2[i][j]=0;
	for (int i=1;i<=n;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			for (int k=Head[V[j]];k!=-1;k=Next[k])
				if (V[k]!=i)
					Node[i][V[k]].push_back(V[j]);
	int tim=0;
	for (int p=1;p<=n;p++)
		for (int q=p+1;q<=n;q++)
		{
			int sum=0;mem(Cnt,0);tim++;
			for (int i=Head[p];i!=-1;i=Next[i])
				if (V[i]!=q)
					for (int j=Head[q];j!=-1;j=Next[j])
						if ((V[j]!=p)&&(V[i]!=V[j]))
						{
							int u=V[i],v=V[j];
							for (int k=0;k<Node[u][v].size();k++)
							{
								int z=Node[u][v][k];
								if ((z==p)||(z==q)) continue;
								Cnt[u]++;Cnt[v]++;Cnt[z]++;sum++;
								if (Tim1[u][v]!=tim) Tim1[u][v]=tim,Cnt1[u][v]=1;
								else Cnt1[u][v]++;
								if (Tim2[u][z]!=tim) Tim2[u][z]=tim,Cnt2[u][z]=1;
								else Cnt2[u][z]++;
								if (Tim2[v][z]!=tim) Tim2[v][z]=tim,Cnt2[v][z]=1;
								else Cnt2[v][z]++;
							}
						}

			for (int i=Head[p];i!=-1;i=Next[i])
				if (V[i]!=q)
					for (int j=Head[q];j!=-1;j=Next[j])
						if ((V[j]!=p)&&(V[i]!=V[j]))
						{
							int x=V[i],y=V[j];
							if (sum-Cnt[x]-Cnt[y]+((Tim2[x][y]==tim)?(Cnt2[x][y]):(0))+((Tim2[y][x]==tim)?(Cnt2[y][x]):(0))+((Tim1[x][y]==tim)?(Cnt1[x][y]):(0)))
								Ans[x][y]=Ans[y][x]=1;
						}
		}
	return;
}

