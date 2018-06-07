#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))
#define GetDist(i,j) (sqrt(sqr(X[i]-X[j])+sqr(Y[i]-Y[j])))

const int maxN=1010;
const ld eps=1e-8;
const int inf=2147483647;

class HData
{
public:
	int u;
	ld dist;
};

int n;
int X[maxN],Y[maxN],Z[maxN];
ld Dist[maxN],S1[maxN],S2[maxN];
bool vis[maxN];
priority_queue<HData> H;

bool operator < (HData A,HData B);
ld Calc(ld K);

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		if (n==0) break;
		for (int i=1;i<=n;i++) scanf("%d%d%d",&X[i],&Y[i],&Z[i]);
		ld L=0,Ans;
		do
		{
			Ans=Calc(L);
			//cout<<L<<" "<<Ans<<endl;
			if (fabs(Ans-L)>eps) L=Ans;
			else break;
		}
		while (1);
		printf("%.3LF\n",Ans);
	}
	return 0;
}

bool operator < (HData A,HData B){
	return A.dist>B.dist;
}

ld Calc(ld K)
{
	for (int i=1;i<=n;i++) Dist[i]=inf;
	mem(vis,0);while (!H.empty()) H.pop();
	Dist[1]=0;H.push((HData){1,Dist[1]});
	ld sum1=0,sum2=0;
	do
	{
		int u=H.top().u;H.pop();
		if (vis[u]) continue;
		vis[u]=1;sum1+=S1[u];sum2+=S2[u];
		for (int i=1;i<=n;i++)
			if ((vis[i]==0)&&(Dist[i]>abs(Z[u]-Z[i])-K*1.0*GetDist(u,i)))
			{
				Dist[i]=abs(Z[u]-Z[i])-K*1.0*GetDist(u,i);
				//cout<<u<<"->"<<i<<" "<<Dist[i]<<" "<<endl;
				H.push((HData){i,Dist[i]});
				S1[i]=abs(Z[u]-Z[i]);S2[i]=GetDist(u,i);
			}
	}
	while (!H.empty());
	return sum1/sum2;
}
