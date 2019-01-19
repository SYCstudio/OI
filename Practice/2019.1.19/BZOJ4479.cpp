#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Min(x,y) x=min(x,y)

const int maxN=14;
const int maxS=1700000;
const int inf=2000000000;

int n,K,m;
int pw2[maxN],pw3[maxN],dis[maxN][maxN];
int cost[1<<maxN],dp[maxS];
vector<int> Me[maxN];
queue<int> Q;
bool inq[maxS];

int main(){
    pw2[0]=pw3[0]=1;for (int i=1;i<maxN;i++) pw2[i]=pw2[i-1]<<1,pw3[i]=pw3[i-1]*3;
    scanf("%d%d",&n,&K);mem(cost,63);mem(dp,63);mem(dis,63);
    int sum=0,must=0;
    for (int i=1;i<=K;i++){
	int u,v,w;scanf("%d%d%d",&u,&v,&w);sum+=w;--u;--v;
	Min(dis[u][v],w);Min(dis[v][u],w);
	Me[u].push_back(v);Me[v].push_back(u);
	must^=pw2[u]^pw2[v];
    }
    scanf("%d",&m);
    for (int i=1;i<=m;i++){
	int u,v,w;scanf("%d%d%d",&u,&v,&w);--u;--v;
	Min(dis[u][v],w);Min(dis[v][u],w);
    }
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) for (int k=0;k<n;k++) Min(dis[j][k],dis[j][i]+dis[i][k]);
    cost[0]=0;
    for (int S=0;S<pw2[n];S++)
	for (int i=0;i<n;i++)
	    if (S&pw2[i])
		for (int j=i+1;j<n;j++)
		    if (S&pw2[j])
			Min(cost[S],cost[S^pw2[i]^pw2[j]]+dis[i][j]);
    dp[2]=0;Q.push(2);inq[2]=1;
    while (!Q.empty()){
	int S=Q.front();Q.pop();
	for (int i=0;i<n;i++)
	    if (S/pw3[i]%3==0){
		for (int j=0,sz=Me[i].size();j<sz;j++)
		    if (S/pw3[Me[i][j]]%3){
			int SS=S+pw3[i]*2;
			if (dp[SS]>dp[S]){
			    dp[SS]=dp[S];
			    if (inq[SS]==0){
				Q.push(SS);inq[SS]=1;
			    }
			}
		    }
		for (int j=0;j<n;j++)
		    if (S/pw3[j]%3){
			int SS=S+pw3[i]+((S/pw3[j]%3==1)?pw3[j]:-pw3[j]);
			if (dp[SS]>dp[S]+dis[i][j]){
			    dp[SS]=dp[S]+dis[i][j];
			    if (inq[SS]==0){
				Q.push(SS);inq[SS]=1;
			    }
			}
		    }
	    }
	inq[S]=0;
    }
    int Ans=inf;
    for (int S=0;S<pw3[n];S++){
	bool flag=1;for (int i=0;i<n&&flag;i++) if (Me[i].size()&&S/pw3[i]%3==0) flag=0;
	if (flag==0) continue;
	int nS=must;for (int i=0;i<n;i++) if (S/pw3[i]%3==1) nS^=pw2[i];
	//cout<<S<<":"<<dp[S]<<" "<<cost[nS]<<endl;
	Ans=min(Ans,dp[S]+cost[nS]);
    }
    printf("%d\n",Ans+sum);return 0;
}
/*
6 3
1 2 1000
2 3 1000
4 5 500
2
1 4 300
3 5 300
//*/
