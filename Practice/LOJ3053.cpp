#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=1000010;
const int Mod=998244353;

#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define Inv(x) QPow(x,Mod-2)
int n,L,K;
class Tag{
public:
    int a,b,inv,pos,num;
    void Init(){
	a=b=inv=1;pos=n;num=0;
    }
};

vector<int> T[maxN];
int Dep[maxN],Mx[maxN],Fa[maxN],pref[maxN],id[maxN],invf[maxN],invc=0,seq[maxN],invseq[maxN];
int _f[maxN*4],*F[maxN*2],*G[maxN],*POS=_f;
int Ans,Rcf[2][maxN];

int QPow(int x,int cnt);
void dfs_init(int u);
namespace CalcF{
    Tag tg[maxN*2];
    vector<pair<Tag,vector<pair<int,int> > > > Rcy[maxN];
    int GET(int u,int p);
    void PUSH(int u,int p,int key);
    void Merge(int u,int v,int len);
    void dfs1(int u);
    void Back(int u);
}
namespace CalcG{
    Tag tg[maxN*2];
    int GET(int u,int p);
    void PUSH(int u,int p,int key);
    void dfs2(int u);
}

int main(){
    scanf("%d%d%d",&n,&L,&K);
    for (int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);
	T[u].pb(v);T[v].pb(u);
    }
    dfs_init(1);
    
    invseq[0]=1;for (int i=1;i<=invc;i++) invseq[i]=1ll*invseq[i-1]*seq[i]%Mod;
    int fullinv=Inv(invseq[invc]);
    for (int i=invc;i>=1;i--) invf[i]=1ll*invseq[i-1]*fullinv%Mod,fullinv=1ll*fullinv*seq[i]%Mod;

    F[1]=POS;POS+=Dep[1];CalcF::dfs(1);
    G[1]=POS;POS+=Dep[1];CalcG::tg[1].Init();CalcG::dfs(1);

    printf("%d\n",Ans);return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%Mod;
	x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
void dfs_init(int u){
    pre_f[u]=1;
    for (int i=0,sz=T[u].size();i<sz;i++)
	if (T[u][i]!=Fa[u]){
	    Fa[T[u][i]]=u;dfs_init(T[u][i]);
	    pre_f[u]=1ll*pre_f[u]*pre_f[T[u][i]]%Mod;
	    if (Dep[T[u][i]]>Dep[Mx[u]]) Mx[u]=T[u][i];
	}
    pre_f[u]=(pre_f[u]+1)%Mod;Dep[u]=Dep[Mx[u]]+1;
    if (pre_f[u]) seq[id[u]=++invc]=pre_f[u];
    return;
}
namespace CalcF{
    int GET(int u,int p){
	int ret=p<tg[u].pos?F[u][p]:tg[u].num;
	ret=(1ll*ret*tg[u].a%Mod+tg[u].b)%Mod;
	return ret;
    }
    void PUSH(int u,int p,int key){
	F[u][p]=1ll*(key-tg[u].b+Mod)%Mod*tg[u].inv%Mod;
	return;
    }
    void Merge(int u,int v,int len){
	vector<pair<int,int> > tmp;Tag t=tg[u];
	for (int i=1;i<=len;i++){
	    tmp.pb(mp(i,F[u][i]));
	    int val=GET(v,i);
	    if (tg[u].pos==i) F[u][tg[u].pos++]=tg[u].num;
	    PUSH(u,i,1ll*GET(u,i)*val%Mod);
	}
	if (len<m){
	    int val=GET(v,len);
	    if (val==0) tg[u].pos=len+1,tg[u].num=Mod-1ll*tg[u].b*tg[u].inv%Mod;
	    else{
		int inv=invf[id[v]];tmp.pb(mp(0,F[u][0]));
		for (int i=0;i<=len;i++) PUSH(u,i,1ll*GET(u,i)*inv%Mod)%Mod;
		tg[u].a=1ll*tg[u].a*val%Mod;tg[u].b=1ll*tg[u].b*val%Mod;tg[u].inv=1ll*tg[u].inv*inv%Mod;
	    }
	}
	if (u<=n) Rcy[u].pb(mp(t,tmp));return;
    }
    void dfs1(int u){
	if (Mx[u]) F[Mx[u]]=Mx[u]+1,dfs1(Mx[u]),tg[u]=tg[Mx[u]];
	else F[u][0].Init();
	PUSH(u,0,1);
	for (int i=0,sz=T[u].size();i<sz;i++)
	    if (T[u][i]!=Fa[u]&&T[u][i]!=Mx[u]){
		int v=T[u][i];F[v]=POS;POS+=Dep[v];dfs(v);
		Merge(u,v,min(Dep[v]-1,L));
	    }
	Rcf[0][u]=GET(u,min(L-1,Dep[u]-1));Rcf[1][u]=GET(u,min(L,Dep[u]-1));
	tg[u].b=(tg[u].b+1)%Mod;return;
    }
    void Back(int u){
	tg[u]=Rcy[u].back().ft;
	vector<pair<int,int> >::iterator it;
	for (it=Rcy[u].back().sd.begin();it!=Rcy[u].back().sd.end();it++) F[u][(*it).ft]=(*it).sd;
	Rcy[u].pop_back();return;
    }
}
namespace CalcG{
    int GET(int u,int p){
	int ret=p<tg[u].pos?G[u][p]:tg[u].num;
	ret=(1ll*ret*tg[u].a%Mod+tg[u].b)%Mod;
	return ret;
    }
    void PUSH(int u,int p,int key){
	G[u][p]=1ll*(key-tg[u].b+Mod)%Mod*tg[u].inv%Mod;return;
    }
    void dfs2(int u){
	if (Dep[u]-1-L>=0) PUSH(u,Dep[u]-1-L,1);
	Ans=(Ans+QPow(1ll*Rcf[1][u]*GET(u,len[u]-1)%Mod,K))%Mod;
	if (Fa[u]) Ans=(Ans-QPow(1ll*Rcf[0][u]*GET(u,len[u]-1)%Mod,K)+Mod)%Mod;
	if (Mx[u]==0) return;int mxlen=0;
	for (int i=0,sz=T[u].size();i<sz;i++) if (T[u][i]!=Fa[u]&&T[u][i]!=Mx[u]) mxlen=max(mxlen,Dep[T[u][i]]);
	F[u+n]=POS;POS+=mxlen;CalcF::tg[u+n].Init();
	for (int sz=T[u].size();i=sz-1;i>=0;i--)
	    if (T[u][i]!=Fa[u]&&T[u][i]!=Mx[u]){
		int v=T[u][i];
		CalcF::Back(u);G[v]=POS;POS+=Dep[v];
	    }
    }
}
