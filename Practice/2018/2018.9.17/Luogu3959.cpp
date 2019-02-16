#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=12;
const int inf=1000000000;

int n,m;
int Map[maxN][maxN];
int F[maxN][maxN+1][1<<maxN];
int SS[1<<maxN],SC[1<<maxN];
int Two[maxN+5];

//IL int dfs(RG int u,RG int depth,RG int S);
IL void calc();
bool cmp(int a,int b);

int main(){
	Two[0]=1;for (RG int i=1;i<maxN+5;i++) Two[i]=Two[i-1]<<1;
	freopen("in.in","r",stdin);
	mem(F,-1);mem(Map,-1);
	scanf("%d%d",&n,&m);
	for (RG int i=1;i<=m;++i){
		RG int u,v,w;scanf("%d%d%d",&u,&v,&w);u--;v--;
		if (Map[u][v]==-1) Map[u][v]=Map[v][u]=w;
		else Map[u][v]=Map[v][u]=min(Map[u][v],w);
	}

	for (int i=0;i<Two[n];++i){
		SS[i]=i;
		RG int key=i;
		while (key) ++SC[i],key-=((key)&(-key));
	}

	sort(&SS[0],&SS[Two[n]],cmp);

	calc();
	RG int Ans=inf;
	for (RG int i=0;i<n;++i) Ans=min(Ans,F[i][1][Two[n]-1]);

	printf("%d\n",Ans);return 0;
}

IL void calc(){
	for (RG int s=0;s<Two[n];++s){
		RG int S=SS[s];
		for (RG int d=n-SC[S]+1;d>=1;--d)
			for (RG int u=0;u<n;++u)
				if (S&Two[u]){
					if (SC[S]==1){
						F[u][d][S]=0;continue;
					}
					F[u][d][S]=inf;
					for (RG int qS=1;qS<Two[SC[S]];++qS){
						RG int nowS=0;
						for (int i=0,j=0;i<n;++i)
							if (S&Two[i]){
								if (qS&Two[j]) nowS|=Two[i];
								++j;
							}
						if (nowS&Two[u]) continue;
						RG int mn=inf;
						for (RG int i=0;i<n;++i)
							if ((Map[u][i]!=-1)&&(nowS&Two[i])) mn=min(mn,F[i][d+1][nowS]+Map[u][i]*d);
						mn=mn+F[u][d][S^nowS];
						F[u][d][S]=min(F[u][d][S],mn);
					}
				}
	}
	return;
}

bool cmp(int a,int b){
	return SC[a]<SC[b];
}

/*
IL int dfs(RG int u,RG int depth,RG int S){
	if (F[u][depth][S]!=-1) return F[u][depth][S];
	F[u][depth][S]=inf;
	RG int nowS=S,cnt=0,ret=inf;
	while (nowS) cnt++,nowS-=((nowS)&(-nowS));
	if (cnt==1) return F[u][depth][S]=0;
	for (RG int qS=1;qS<(1<<cnt);qS++){
		RG int nowS=0;
		for (RG int i=0,j=0;i<n;i++)
			if (S&(1<<i)){
				if (qS&(1<<j)) nowS|=1<<i;
				j++;
			}
		if (nowS&(1<<u)) continue;
		RG int mn=inf;
		for (RG int i=0;i<n;i++)
			if ((Map[u][i]!=-1)&&(nowS&(1<<i)) ) mn=min(mn,dfs(i,depth+1,nowS)+Map[u][i]*depth);
		mn=mn+dfs(u,depth,S^nowS);
		ret=min(ret,mn);
	}
	return F[u][depth][S]=ret;
}
//*/
