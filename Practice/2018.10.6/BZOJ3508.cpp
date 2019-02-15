#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "starlit"

const int maxN=40100;
const int maxM=200;
const int maxK=21;
const int inf=100000000;
const int meminf=1061109567;

int n,K,m;
int L[maxM],Dist[maxN],Cost[maxK][maxK];
bool off[maxN];
int pcnt,P[maxN];
queue<int> Q;
int F[1<<maxK];

void Bfs(int st);
int dp(int S);

int main(){
	//freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		mem(off,0);pcnt=0;mem(L,0);mem(Dist,0);mem(Cost,0);
		scanf("%d%d%d",&n,&K,&m);
		for (int i=1;i<=K;i++){
			int p;scanf("%d",&p);off[p]=1;
		}
		for (int i=1;i<=m;i++) scanf("%d",&L[i]);
		
		for (int i=0;i<=n;i++) if (off[i]^off[i+1]) P[pcnt++]=i;
		for (int i=0;i<pcnt;i++){
			Bfs(P[i]);
			for (int j=0;j<pcnt;j++) Cost[i][j]=Dist[P[j]];
		}
		/*
		  for (int i=0;i<pcnt;i++) cout<<P[i]<<" ";cout<<endl;
		  for (int i=0;i<pcnt;i++){
		  for (int j=0;j<pcnt;j++) cout<<Cost[i][j]<<" ";cout<<endl;
		  }
		//*/
		mem(F,-1);F[0]=0;
		int ret=dp((1<<pcnt)-1);
		if (ret!=meminf) printf("%d\n",ret);
		else printf("-1\n");
	}return 0;
}
	
void Bfs(int st){
	mem(Dist,63);while (!Q.empty()) Q.pop();
	Dist[st]=0;Q.push(st);
	do{
		int u=Q.front();Q.pop();
		for (int i=1;i<=m;i++){
			if ((u+L[i]<=n)&&(Dist[u+L[i]]>Dist[u]+1)){
				Dist[u+L[i]]=Dist[u]+1;Q.push(u+L[i]);
			}
			if ((u-L[i]>=0)&&(Dist[u-L[i]]>Dist[u]+1)){
				Dist[u-L[i]]=Dist[u]+1;Q.push(u-L[i]);
			}
		}
	}
	while (!Q.empty());
	return;
}

int dp(int S){
	if (F[S]!=-1) return F[S];
	if (S==0) return 0;
	F[S]=meminf;
	int l,r;l=0;while ((S&(1<<l))==0) ++l;
	for (r=l+1;r<pcnt;r++)
		if ((S&(1<<r))&&(Cost[l][r]!=meminf)) F[S]=min(F[S],dp(S^(1<<l)^(1<<r))+Cost[l][r]);
	return F[S];
}
