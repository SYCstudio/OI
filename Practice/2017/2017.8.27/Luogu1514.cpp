#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=600;
const int F1[5]={0,1,-1,0,0};
const int F2[5]={0,0,0,1,-1};
const int inf=2147483647;

class Range
{
public:
	int l,r;
};

class Pos
{
public:
	int x,y;
};

bool operator <(Range A,Range B)
{
	return (A.l<B.l)||((A.l==B.l)&&(A.r>B.r));
}

int n,m;
int Rangecnt=0;
int Height[maxN][maxN];
bool vis[maxN][maxN];
bool is_cover[maxN];
Range R[maxN];
queue<Pos> Q;
int F[maxN];

void bfs(int st);

int main()
{
	freopen("flow.in","r",stdin);
	freopen("flow.out","w",stdout);
	memset(is_cover,0,sizeof(is_cover));
	Rangecnt=0;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&Height[i][j]);
	Height[1][0]=0;
	Height[1][m+1]=0;
	for (int i=1;i<=m;i++)
		if ((Height[1][i]>=Height[1][i-1])&&(Height[1][i]>=Height[1][i+1]))
			bfs(i);
	int sum=0;
	for (int i=1;i<=m;i++)
		sum+=(int)(is_cover[i]);
	if (sum<m)
	{
		printf("0\n%d\n",m-sum);
		return 0;
	}
	sort(&R[1],&R[Rangecnt+1]);
	memset(F,126,sizeof(F));
	F[0]=0;
	for (int i=1;i<=Rangecnt;i++)
		for (int j=R[i].l;j<=R[i].r;j++)
			F[j]=min(F[j],F[R[i].l-1]+1);
	printf("1\n%d\n",F[m]);
	/*
	for (int i=2;i<=Rangecnt;i++)
	{
		//cout<<cover_right<<" "<<max_right<<endl;
	    if (R[i].l>cover_right)
		{
			Ans++;
			cover_right=max_right;
		}
		else
			max_right=max(max_right,R[i].r);
	}
	//*/
	//printf("1\n%d\n",Ans);
	return 0;
}

void bfs(int st)
{
	memset(vis,0,sizeof(vis));
	Pos init;
	init.x=1;
	init.y=st;
	vis[1][st]=1;
	while (!Q.empty())
		Q.pop();
	Q.push(init);
	do
	{
		Pos u=Q.front();
		Q.pop();
		for (int i=1;i<=4;i++)
		{
			int x=u.x+F1[i];
			int y=u.y+F2[i];
			//cout<<u.x<<","<<u.y<<"->"<<x<<","<<y<<endl;
			//cout<<Height[u.x][u.y]<<" "<<Height[x][y]<<endl;
			//cout<<(y<=0)<<" "<<Height[u.x][u.y]<<" "<<Height[x][y]<<" "<<vis[x][y]<<endl;
			//cout<<(y<=0)<<(y>m)<<(Height[u.x][u.y]<=Height[x][y])<<(vis[x][y]==1)<<endl;
			//cout<<(x<=n)<<(x>=1)<<(y<=m)<<(y>=1)<<(Height[u.x][u.y]>Height[x][y])<<(vis[x][y]==0)<<endl;
			if ((x<=n)&&(x>=1)&&(y<=m)&&(y>=1)&&(Height[u.x][u.y]>Height[x][y])&&(vis[x][y]==0))
			{
				Q.push((Pos){x,y});
				vis[x][y]=1;
			}
		}
	}
	while (!Q.empty());
	int l=-1,r=-1;
	for (int i=1;i<=m;i++)
	{
		if ((vis[n][i]==1)&&(l==-1))
			l=i;
		if ((vis[n][i]==0)&&(l!=-1)&&(r==-1))
			r=i-1;
		if (vis[n][i]==1)
			is_cover[i]=1;
	}
	if (l==-1)
		return;
	if (r==-1)
		r=m;
	/*
	cout<<st<<endl;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			cout<<vis[i][j]<<" ";
		cout<<endl;
	}
	cout<<l<<" "<<r<<endl;
	//*/
	//cout<<l<<" "<<r<<endl;
	Rangecnt++;
	R[Rangecnt].l=l;
	R[Rangecnt].r=r;
	return;
}
