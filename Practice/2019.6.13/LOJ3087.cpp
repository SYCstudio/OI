#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define mp make_pair
#define pb push_back
#define ft first
#define sd second
const int maxN=101000;
const int inf=2000000000;
const ll INF=1e18;

class HData{
public:
    ll key;int u,o;
    HData(){}
    HData(ll a,int b,int c){
	key=a;u=b;o=c;return;
    }
};

int n,m,K,Seq[maxN];
vector<pair<int,int> > T[maxN];
priority_queue<HData> H;
int vis[2][maxN],Fr[2][maxN];
ll D[2][maxN];

bool operator < (HData A,HData B);
int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=m;i++){
	    int u,v,w;scanf("%d%d%d",&u,&v,&w);
	    T[u].pb(mp(v,w));
	}
	for (int i=1;i<=n;i++) D[0][i]=D[1][i]=INF;
	for (int i=1;i<=K;i++) scanf("%d",&Seq[i]),D[0][Seq[i]]=0,Fr[0][Seq[i]]=Seq[i],H.push((HData){0,Seq[i],0});
	while (!H.empty()){
	    int u=H.top().u,o=H.top().o;H.pop();
	    if (vis[o][u]) continue;vis[o][u]=1;
	    for (int i=0,sz=T[u].size();i<sz;i++){
		int v=T[u][i].ft;
		ll d=D[o][u]+T[u][i].sd;
		if (Fr[o][u]!=Fr[0][v]){
		    if (d<=D[0][v]){
			D[1][v]=D[0][v];Fr[1][v]=Fr[0][v];
			D[0][v]=d;Fr[0][v]=Fr[o][u];
			H.push((HData){D[0][v],v,0});
		    }
		    else if (d<D[1][v]){
			D[1][v]=d;Fr[1][v]=Fr[o][u];
			H.push((HData){D[1][v],v,1});
		    }
		}
		else if (d<D[0][v]){
		    D[0][v]=d;H.push((HData){D[0][v],v,0});
		}
	    }
	}
	ll Ans=INF;
	for (int i=1;i<=K;i++) Ans=min(Ans,D[1][Seq[i]]);
	//for (int i=1;i<=K;i++) cout<<"("<<D[0][Seq[i]]<<" "<<Fr[0][Seq[i]]<<" "<<D[1][Seq[i]]<<" "<<Fr[1][Seq[i]]<<") ";cout<<endl;
	printf("%lld\n",Ans);

	for (int i=1;i<=n;i++) T[i].clear(),vis[0][i]=vis[1][i]=Fr[0][i]=Fr[1][i]=0;
    }
    return 0;
}
bool operator < (HData A,HData B){
    return A.key>B.key;
}
