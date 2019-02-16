#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=55;
const int maxM=5010;
const int inf=2147483647;

int n,m;
int L[maxM],R[maxM],C[maxM],nC[maxM];
int numcnt=0,Num[maxM];
int F[maxN][maxN][maxM],G[maxN][maxN][maxM],Val[maxN][maxM];
int PathF[maxN][maxN][maxM],PathG[maxN][maxN][maxM];
int W[maxN];

void dfs(int l,int r,int w);

int main()
{
	//ios::sync_with_stdio(false);
	
	scanf("%d%d",&n,&m);//cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&L[i],&R[i],&C[i]);//cin>>L[i]>>R[i]>>C[i];
		Num[++numcnt]=C[i];
	}
	sort(&Num[1],&Num[numcnt+1]);
	numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	//for (int i=1;i<=numcnt;i++) cout<<Num[i]<<" ";cout<<endl;
	for (int i=1;i<=m;i++) nC[i]=find(C[i]);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) for (int k=1;k<=numcnt;k++) F[i][j][k]=G[i][j][k]=-inf;
	for (int i=1;i<=n;i++) for (int k=1;k<=numcnt;k++) F[i][i-1][k]=G[i][i-1][k]=0;
	
	for (int len=0;len<=n;len++)
		for (int l=1;l+len<=n;l++)
		{
			int r=l+len;
			for (int i=l;i<=r;i++)
				for (int j=1;j<=numcnt;j++) Val[i][j]=0;
			for (int i=1;i<=m;i++)
				if ((L[i]>=l)&&(R[i]<=r))
					for (int j=L[i];j<=R[i];j++)
						Val[j][nC[i]]++;
			for (int i=l;i<=r;i++)
				for (int j=numcnt;j>=1;j--)
					Val[i][j]+=Val[i][j+1];
			for (int k=1;k<=numcnt;k++)
				for (int x=l;x<=r;x++)
					if (F[l][r][k]<G[l][x-1][k]+G[x+1][r][k]+Val[x][k]*Num[k])
					{
						PathF[l][r][k]=x;
						F[l][r][k]=G[l][x-1][k]+G[x+1][r][k]+Val[x][k]*Num[k];
					}
			for (int k=numcnt;k>=1;k--)
			{
				if (G[l][r][k+1]<F[l][r][k])
					PathG[l][r][k]=k;
				else PathG[l][r][k]=PathG[l][r][k+1];
				G[l][r][k]=max(G[l][r][k+1],F[l][r][k]);
			}
			//cout<<"["<<l<<","<<r<<"]"<<endl;
			//for (int k=1;k<=numcnt;k++) cout<<F[l][r][k]<<" ("<<"["<<l<<","<<PathF[l][r][k]<<","<<r<<"]) ";cout<<endl;
			//for (int k=1;k<=numcnt;k++) cout<<G[l][r][k]<<" ["<<PathG[l][r][k]<<"] ";cout<<endl;
		}
	int mxid=0;
	for (int i=1;i<=numcnt;i++) if (F[1][n][i]>F[1][n][mxid]) mxid=i;
	printf("%d\n",F[1][n][mxid]);
	dfs(1,n,mxid);
	for (int i=1;i<=n;i++) printf("%d ",Num[W[i]]);
	return 0;
}


void dfs(int l,int r,int w)
{
	if (l>r) return;
	//cout<<l<<" "<<r<<" "<<w<<endl;
	for (int i=l;i<=r;i++) W[i]=max(W[i],w);
	int p=PathF[l][r][w];
	if (p==0) return;
	//cout<<"p:"<<p<<endl;
	W[p]=w;
	dfs(l,p-1,PathG[l][p-1][w]);
	dfs(p+1,r,PathG[p+1][r][w]);
	return;
}
