#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define ft first
#define sd second
const int maxN=10100;


int n,m,Dg[maxN];
vector<int> T[maxN],Del[maxN];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > H;
bool vis[maxN];

void Delete(int u);
int main(){
    //freopen("input","r",stdin);freopen("user_out","w",stdout);
    int Case;scanf("%d",&Case);
    while (Case--){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
	    int u,v;scanf("%d%d",&u,&v);
	    T[u].pb(v);T[v].pb(u);++Dg[u];++Dg[v];
	}
	for (int i=1;i<=n;i++) H.push(mp(Dg[i],i));
	int delcnt=0;
	while (!H.empty()){
	    int u=H.top().sd;H.pop();
	    if (vis[u]) continue;vis[u]=1;
	    Del[++delcnt].pb(u);
	    Delete(u);
	    for (int i=0;i<T[u].size();i++)
		if (!vis[T[u][i]]){
		    Delete(T[u][i]);Del[delcnt].pb(T[u][i]);
		}
	}//xcout<<endl;
	//cout<<"delcnt:"<<delcnt<<endl;

	/*
	for (int i=1;i<=delcnt;i++){
	    cout<<i<<":";for (int j=0;j<Del[i].size();j++) cout<<Del[i][j]<<" ";cout<<endl;
	}
	//*/
	
	int mx=0;vector<int> P,Q;
	for (int i=1;i<=delcnt;i++) mx=max(mx,(int)Del[i].size()),P.pb(Del[i][0]);
	for (int i=delcnt;i>=1;i--)
	    if (Del[i].size()==mx){
		for (int j=i;j<=delcnt;j++) for (int k=0;k<Del[j].size();k++) Q.pb(Del[j][k]);
		break;
	    }
	printf("%d ",(int)Q.size());for (int i=0;i<Q.size();i++) printf("%d ",Q[i]);puts("");
	printf("%d ",(int)P.size());for (int i=0;i<P.size();i++) printf("%d ",P[i]);puts("");

	for (int i=1;i<=n;i++) T[i].clear(),Dg[i]=0,vis[i]=0;
	for (int i=1;i<=delcnt;i++) Del[i].clear();
    }
    return 0;
}
void Delete(int u){
    vis[u]=1;
    for (int i=0;i<T[u].size();i++)
	if (!vis[T[u][i]]){
	    --Dg[T[u][i]];
	    H.push(mp(Dg[T[u][i]],T[u][i]));
	}
    return;
}
