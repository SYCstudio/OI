#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
const int maxN=110;
const int maxM=10100;

class Edge{
public:
    int u,v,w;
};

int n,m;
int D1[maxN][maxM],D2[maxN][maxM];
ll Sml[maxM],Smr[maxM];
vector<Edge> Pe[maxM],Se[maxM];
vector<pair<int,int> > Vt[maxM];
int ufs[maxM],Imp[maxM],use[maxM],mark[maxM];

int ufs_find(int x);
bool ecmp(Edge A,Edge B);
void dfs1(int u,int fa);
void dfs2(int u,int fa,int anc,int mx,vector<Edge> &E);
namespace GEN{
    unsigned SA,SB,SC;int lim;
    int getweight();
}
using GEN::getweight;

int main(){
    scanf("%d%d",&n,&m);
    scanf("%u%u%u%d",&GEN::SA,&GEN::SB,&GEN::SC,&GEN::lim);

    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) D1[i][j]=getweight();
    for (int i=1;i<n;i++) for (int j=1;j<=m;j++) D2[i][j]=getweight();

    for (int i=1;i<n;i++) Pe[1].pb((Edge){i,i+1,D2[i][1]}),Sml[1]+=D2[i][1];
    for (int i=2;i<=m;i++){
	int mxsz=n+n;Pe[i]=Pe[i-1];Sml[i]=Sml[i-1];
	for (int j=0;j<Pe[i].size();j++){
	    if (Pe[i][j].u>n) Pe[i][j].u+=n;
	    if (Pe[i][j].v>n) Pe[i][j].v+=n;
	    mxsz=max(mxsz,Pe[i][j].u);
	    mxsz=max(mxsz,Pe[i][j].v);
	}
	for (int j=1;j<n;j++) Pe[i].pb((Edge){n+j,n+j+1,D2[j][i]}),Sml[i]+=D2[j][i];
	for (int j=1;j<=n;j++){
	    Sml[i]+=D1[j][i-1];
	    if (i==2) Pe[i].pb((Edge){j,j+n,D1[j][i-1]});
	    else Pe[i].pb((Edge){n+j,n+n+j,D1[j][i-1]});
	}
	
	sort(Pe[i].begin(),Pe[i].end(),ecmp);
	for (int j=1;j<=mxsz;j++) ufs[j]=j,Vt[j].clear(),Imp[j]=use[j]=mark[j]=0;
	for (int j=0;j<Pe[i].size();j++){
	    int u=Pe[i][j].u,v=Pe[i][j].v;
	    if (ufs_find(u)!=ufs_find(v)){
		ufs[ufs_find(u)]=ufs_find(v);
		Vt[u].pb(mp(v,Pe[i][j].w));
		Vt[v].pb(mp(u,Pe[i][j].w));
	    }
	    else Sml[i]-=Pe[i][j].w;
	}
	Pe[i].clear();
	for (int j=1;j<=n;j++) Imp[j]=Imp[j+n]=mark[j]=mark[j+n]=1;
	
	dfs1(1,0);
	dfs2(1,0,1,0,Pe[i]);

	int idcnt=n+n;
	for (int j=0;j<Pe[i].size();j++){
	    if (Pe[i][j].u>n+n){
		if (!use[Pe[i][j].u]) use[Pe[i][j].u]=++idcnt;
		Pe[i][j].u=use[Pe[i][j].u];
	    }
	    if (Pe[i][j].v>n+n){
		if (!use[Pe[i][j].v]) use[Pe[i][j].v]=++idcnt;
		Pe[i][j].v=use[Pe[i][j].v];
	    }
	}
    }

    for (int i=1;i<n;i++) Se[m].pb((Edge){i,i+1,D2[i][m]}),Smr[m]+=D2[i][m];
    for (int i=m-1;i>=1;i--){
	Se[i]=Se[i+1];Smr[i]=Smr[i+1];int mxsz=n+n;
	for (int j=0;j<Se[i].size();j++){
	    if (Se[i][j].u>n) Se[i][j].u+=n;
	    if (Se[i][j].v>n) Se[i][j].v+=n;
	    mxsz=max(mxsz,Se[i][j].u);
	    mxsz=max(mxsz,Se[i][j].v);
	}
	for (int j=1;j<n;j++) Se[i].pb((Edge){j+n,j+1+n,D2[j][i]}),Smr[i]+=D2[j][i];
	for (int j=1;j<=n;j++){
	    Smr[i]+=D1[j][i];
	    if (i==m-1) Se[i].pb((Edge){j,j+n,D1[j][i]});
	    else Se[i].pb((Edge){j+n,j+n+n,D1[j][i]});
	}

	sort(Se[i].begin(),Se[i].end(),ecmp);
	for (int j=1;j<=mxsz;j++) ufs[j]=j,Vt[j].clear(),Imp[j]=use[j]=mark[j]=0;
	for (int j=0;j<Se[i].size();j++){
	    int u=Se[i][j].u,v=Se[i][j].v;
	    if (ufs_find(u)!=ufs_find(v)){
		ufs[ufs_find(u)]=ufs_find(v);
		Vt[u].pb(mp(v,Se[i][j].w));
		Vt[v].pb(mp(u,Se[i][j].w));
	    }
	    else Smr[i]-=Se[i][j].w;
	}
	Se[i].clear();
	
	
	for (int j=1;j<=n;j++) Imp[j]=Imp[j+n]=mark[j]=mark[j+n]=1;
	
	dfs1(1,0);
	dfs2(1,0,1,0,Se[i]);

	int idcnt=n+n;
	for (int j=0;j<Se[i].size();j++){
	    if (Se[i][j].u>n+n){
		if (!use[Se[i][j].u]) use[Se[i][j].u]=++idcnt;
		Se[i][j].u=use[Se[i][j].u];
	    }
	    if (Se[i][j].v>n+n){
		if (!use[Se[i][j].v]) use[Se[i][j].v]=++idcnt;
		Se[i][j].v=use[Se[i][j].v];
	    }
	}
    }

    int Q;scanf("%d",&Q);
    while (Q--){
	int L,R;scanf("%d%d",&L,&R);
	if (L==1&&R==m) puts("0");
	else if (L==1) printf("%lld\n",Smr[R+1]);
	else if (R==m) printf("%lld\n",Sml[L-1]);
	else{
	    ll Ans=Sml[L-1]+Smr[R+1];
	    vector<Edge> tmp;map<int,int> idnew;int idcnt=n+n;
	    for (int i=1;i<=n;i++) tmp.pb((Edge){i,i+n,D1[i][m]}),Ans+=D1[i][m];
	    
	    for (int i=1;i<=n;i++) idnew[i]=i;
	    for (int i=0;i<Pe[L-1].size();i++){
		int u=Pe[L-1][i].u,v=Pe[L-1][i].v;
		if (idnew.count(u)==0) idnew[u]=++idcnt;
		if (idnew.count(v)==0) idnew[v]=++idcnt;
		u=idnew[u];v=idnew[v];
		tmp.pb((Edge){u,v,Pe[L-1][i].w});
	    }
	    idnew.clear();
	    for (int i=1;i<=n;i++) idnew[i]=n+i;
	    for (int i=0;i<Se[R+1].size();i++){
		int u=Se[R+1][i].u,v=Se[R+1][i].v;
		if (idnew.count(u)==0) idnew[u]=++idcnt;
		if (idnew.count(v)==0) idnew[v]=++idcnt;
		u=idnew[u];v=idnew[v];
		tmp.pb((Edge){u,v,Se[R+1][i].w});
	    }

	    sort(tmp.begin(),tmp.end(),ecmp);
	    for (int i=1;i<=idcnt;i++) ufs[i]=i;
	    for (int i=0;i<tmp.size();i++){
		int u=tmp[i].u,v=tmp[i].v;
		if (ufs_find(u)!=ufs_find(v)) ufs[ufs_find(u)]=ufs_find(v);
		else Ans-=tmp[i].w;
	    }

	    printf("%lld\n",Ans);
	}
    }
    return 0;
}
int ufs_find(int x){
    return x==ufs[x]?ufs[x]:ufs[x]=ufs_find(ufs[x]);
}
bool ecmp(Edge A,Edge B){
    if (A.w!=B.w) return A.w<B.w;
    if (A.u!=B.u) return A.u<B.u;
    return A.v<B.v;
}
void dfs1(int u,int fa){
    for (int i=0;i<Vt[u].size();i++) if (Vt[u][i].ft!=fa) dfs1(Vt[u][i].ft,u),Imp[u]+=Imp[Vt[u][i].ft];
    return;
}
void dfs2(int u,int fa,int anc,int mx,vector<Edge> &E){
    if (!Imp[u]) return;
    if (u!=1&&(Vt[u].size()>=3||mark[u])) E.pb((Edge){anc,u,mx}),mx=0,anc=u;
    for (int i=0;i<Vt[u].size();i++)
	if (Vt[u][i].ft!=fa) dfs2(Vt[u][i].ft,u,anc,max(mx,Vt[u][i].sd),E);
    return;
}
namespace GEN{
    int getweight(){
	SA^=SA<<16;
	SA^=SA>>5;
	SA^=SA<<1;
	unsigned int t=SA;
	SA=SB;
	SB=SC;
	SC^=t^SA;
	return SC%lim+1;
    }
}
