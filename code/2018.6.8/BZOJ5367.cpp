#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxM=10100;
const int maxK=1010;
const ld eps=1e-8;
const int inf=2147483647;
const ll INF=1e18;

int n,m,K;
ll In[maxN][maxK],Out[maxN][maxK];
ll Map[maxN][maxN],Good[maxN][maxN];
bool vis[maxN];
ll Dist[maxN];
queue<int> Q;
bool inq[maxN];
int Cnt[maxN];

bool Check(ll k);
bool Spfa(int uu,ll k);

int main()
{
	//freopen("1.in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=n;i++) for (int j=1;j<=K;j++) scanf("%lld%lld",&In[i][j],&Out[i][j]);
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Map[i][j]=INF,Good[i][j]=-INF;
    for (int i=1;i<=n;i++) Map[i][i]=0;
    for (int i=1;i<=m;i++)
    {
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        if (u==v) continue;
        Map[u][v]=min(Map[u][v],(ll)w);
    }
    for (int k=1;k<=n;k++)
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                Map[i][j]=min(Map[i][j],Map[i][k]+Map[k][j]);

    /*
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
            cout<<Map[i][j]<<" ";
        cout<<endl;
    }
    //*/

    ll L=0,R=0,Ans;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (i!=j)
            {
                if (Map[i][j]==INF) continue;
                Good[i][j]=0;
                for (int k=1;k<=K;k++)
                    if ((In[i][k]>=0)&&(Out[j][k]>=0)) Good[i][j]=max(Good[i][j],(ll)Out[j][k]-In[i][k]);
                R=max(R,Good[i][j]);
            }

	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
			cout<<Good[i][j]<<" ";
		cout<<endl;
	}
	//*/

	//cout<<L<<" "<<R<<endl;
	
    do
    {
        ll mid=(L+R)>>1;
        //cout<<"("<<L<<","<<R<<")"<<endl;
        if (Check(mid)) Ans=mid,L=mid+1;
        else R=mid-1;
    }
    while (L<=R);

    printf("%lld\n",Ans);
    return 0;
}

bool Check(ll k)
{
    return Spfa(1,k);
}

bool Spfa(int uu,ll k)
{
    while (!Q.empty()) Q.pop();
    for (int i=1;i<=n;i++)
    {
        Q.push(i);
        Dist[i]=0;inq[i]=1;Cnt[i]=1;
    }
    do
    {
        int u=Q.front();Q.pop();inq[u]=0;
        for (int i=1;i<=n;i++)
            if ((i!=u)&&(Map[u][i]!=INF)&&(Dist[i]<=Dist[u]+Good[u][i]-1ll*(ll)k*Map[u][i]))
            {
                Dist[i]=Dist[u]+Good[u][i]-1ll*(ll)k*Map[u][i];
                if (inq[i]==0){
					if ((++Cnt[i])>n) return 1;
                    Q.push(i);inq[i]=1;
                }
            }
        inq[u]=0;
    }
    while (!Q.empty());
    return 0;
}

/*
bool Spfa(int u,int k)
{
    vis[u]=1;
    for (int i=1;i<=n;i++)
        if ((i!=u)&&(Dist[i]<Dist[u]+Good[u][i]-1ll*(ll)k*Map[u][i]))
        {
            if (vis[i]) return 0;
            Dist[i]=Dist[u]+Good[u][i]-1ll*(ll)k*Map[u][i];
            if (Spfa(i,k)==0) return 0;
        }
    vis[u]=0;
    return 1;
}
//*/
