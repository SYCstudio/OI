#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define ft first
#define sd second
const int maxN=505000*3;

int n,Lm[maxN];
vector<int> T[maxN],G[maxN+maxN];
priority_queue<pair<int,int> > H;
int D[maxN],Dg[maxN],Val[maxN];

void dfs(int u,int fa);
int main(){
    scanf("%d",&n);
    for (int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);
	T[u].pb(v);T[v].pb(u);
    }
    for (int i=1;i<=n;i++) scanf("%d",&Lm[i]);
    for (int i=1;i<=n;i++) Val[i]=i;
    for (int i=n+1;i+1<=n+n;i++) G[i].pb(i+1),++Dg[i+1];
    dfs(1,1);for (int i=1;i<=n+n;i++) if (Dg[i]==0) H.push(mp(-Val[i],i));
    int cnt=0;
    while (!H.empty()){
	int u=H.top().sd;H.pop();
	if (u<=n){
	    printf("%d",u);++cnt;
	    if (cnt<n) printf(" ");
	}
	for (int i=0;i<G[u].size();i++)
	    if ((--Dg[G[u][i]])==0) H.push(mp(-Val[G[u][i]],G[u][i]));
    }
    printf("\n");
    return 0;
}
void dfs(int u,int fa){
    D[u]=D[fa]+1;G[n+D[u]].pb(u);++Dg[u];
    G[u].pb(n+Lm[u]+1);++Dg[n+Lm[u]+1];
    for (int i=0;i<T[u].size();i++)
	if (T[u][i]!=fa) dfs(T[u][i],u);
    return;
}
