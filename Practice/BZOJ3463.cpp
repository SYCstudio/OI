#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<iostream>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define mp make_pair
#define ft first
#define sd second

const int maxN=101000;
const int Block=120;
const ll INF=1e18;

ld GetC(ll k1,ll b1,ll k2,ll b2);

class Convex{
public:
    int sz;
    deque<pair<ll,ll> > C;
    Convex(){
	sz=-1;return;
    }
    void clear(){
	sz=-1;C.clear();return;
    }
    void push_back(ll k,ll b){
	while (sz>=0){
	    if (C[sz].ft==k){
		if (C[sz].sd>=b) return;
		C.pop_back();--sz;continue;
	    }
	    else if (sz>=1&&GetC(C[sz-1].ft,C[sz-1].sd,k,b)<=GetC(C[sz-1].ft,C[sz-1].sd,C[sz].ft,C[sz].sd)){
		C.pop_back();--sz;continue;
	    }
	    break;
	}
	C.push_back(mp(k,b));++sz;return;
    }
    bool empty(){
	return sz==-1;
    }
    ll top(ll t){
	if (empty()) return -INF;
	while (sz>=1&&GetC(C[0].ft,C[0].sd,C[1].ft,C[1].sd)<=t) C.pop_front(),--sz;
	return t*C[0].ft+C[0].sd;
    }
};

int n,m;
int L[maxN],R[maxN],Bl[maxN];
bool vis[maxN];
ll K[maxN],B[maxN];
pair<ll,ll> Sorter[maxN];
Convex Cnx[Block*10],Bp;

int main(){
    //freopen("9.in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
	Bl[i]=i/Block+1;R[Bl[i]]=i;
	if (L[Bl[i]]==0) L[Bl[i]]=i;
    }
    while (m--){
	//if (m%10000==0) cerr<<m<<endl;
	int opt;scanf("%d",&opt);
	if (opt==1){
	    ll t,p,k,b;scanf("%lld%lld%lld%lld",&t,&p,&k,&b);
	    vis[p]=1;K[p]=k;B[p]=b-k*t;
	    
	    int scnt=0;for (int i=L[Bl[p]];i<=R[Bl[p]];i++) if (vis[i]) Sorter[++scnt]=mp(K[i],B[i]);
	    sort(&Sorter[1],&Sorter[scnt+1]);
	    Cnx[Bl[p]].clear();
	    for (int i=1;i<=scnt;i++) Cnx[Bl[p]].push_back(Sorter[i].ft,Sorter[i].sd);
	}
	if (opt==2){
	    int t,l,r;scanf("%d%d%d",&t,&l,&r);
	    ll Ans=-INF;if (l>r) swap(l,r);
	    if (Bl[l]==Bl[r]) for (int i=l;i<=r;i++) if (vis[i]) Ans=max(Ans,K[i]*t+B[i]);else;
	    else{
		for (int i=l;i<=R[Bl[l]];i++) Ans=max(Ans,K[i]*t+B[i]);
		for (int i=L[Bl[r]];i<=r;i++) Ans=max(Ans,K[i]*t+B[i]);
		for (int i=Bl[l]+1;i<Bl[r];i++) Ans=max(Ans,Cnx[i].top(t));
	    }
	    if (Ans==-INF) printf("nema\n");
	    else printf("%lld\n",Ans);
	}
    }
    return 0;
}

ld GetC(ll k1,ll b1,ll k2,ll b2){
    return (ld)(b1-b2)/(ld)(k2-k1);
}
