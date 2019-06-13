#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=50500;
const int maxM=maxN<<1;
const int Mod=998244353;

int n,Q,K;
vector<int> T[maxN],Qk[maxN];
int Sz[maxN],Mx[maxN],Dep[maxN],Top[maxN],Fa[maxN],dfncnt,dfn[maxN],lst[maxN],idfn[maxN];
int Key[maxN<<2],Lz[maxN<<2],Sm[maxN<<2];
int Ans[maxN],Qy[maxN];

int QPow(int x,int cnt);
void dfs1(int u);
void dfs2(int u,int top);
void Build(int x,int l,int r);
void Push(int x,int l,int r,int ql,int qr);
int Query(int x,int l,int r,int ql,int qr,int o);

int main(){
    scanf("%d%d%d",&n,&Q,&K);
    for (int i=2;i<=n;i++){
	scanf("%d",&Fa[i]);T[Fa[i]].pb(i);
    }
    for (int i=1;i<=Q;i++){
	int x;scanf("%d%d",&x,&Qy[i]);Qk[x].pb(i);
    }
    Dep[1]=1;dfs1(1);dfs2(1,1);
    Build(1,1,n);
    for (int i=1;i<=n;i++){
	int u=i;
	while (Top[u]!=1){
	    Push(1,1,n,dfn[Top[u]],dfn[u]);
	    u=Fa[Top[u]];
	}
	Push(1,1,n,dfn[1],dfn[u]);

	for (int j=0,sz=Qk[i].size();j<sz;j++){
	    int id=Qk[i][j],u=Qy[id],sum=0;
	    while (Top[u]!=1){
		sum=(sum+Query(1,1,n,dfn[Top[u]],dfn[u],0))%Mod;
		u=Fa[Top[u]];
	    }
	    sum=(sum+Query(1,1,n,dfn[1],dfn[u],0))%Mod;
	    Ans[id]=sum;
	}
    }
    for (int i=1;i<=Q;i++) printf("%d\n",Ans[i]);
    return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%Mod;x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
void dfs1(int u){
    Sz[u]=1;
    for (int i=0,sz=T[u].size();i<sz;i++){
	int v=T[u][i];Dep[v]=Dep[u]+1;
	dfs1(v);Sz[u]+=Sz[v];
	if (Sz[v]>Sz[Mx[u]]) Mx[u]=v;
    }
    return;
}
void dfs2(int u,int top){
    Top[u]=top;idfn[dfn[u]=++dfncnt]=u;
    if (Mx[u]) dfs2(Mx[u],top);
    for (int i=0,sz=T[u].size();i<sz;i++) if (T[u][i]!=Mx[u]) dfs2(T[u][i],T[u][i]);
    lst[u]=dfncnt;return;
}
#define ls (x<<1)
#define rs (ls|1)
void Build(int x,int l,int r){
    if (l==r){
	int u=idfn[l];
	Key[x]=(QPow(Dep[u],K)-QPow(Dep[u]-1,K)+Mod)%Mod;
	//cout<<Dep[u]<<" "<<Key[x]<<endl;
	return;
    }
    int mid=(l+r)>>1;Build(ls,l,mid);Build(rs,mid+1,r);
    Key[x]=(Key[ls]+Key[rs])%Mod;return;
}
void Push(int x,int l,int r,int ql,int qr){
    if (l==ql&&r==qr){
	++Lz[x];Sm[x]=(Sm[x]+Key[x])%Mod;
	return;
    }
    int mid=(l+r)>>1;
    if (qr<=mid) Push(ls,l,mid,ql,qr);
    else if (ql>=mid+1) Push(rs,mid+1,r,ql,qr);
    else Push(ls,l,mid,ql,mid),Push(rs,mid+1,r,mid+1,qr);
    Sm[x]=(Sm[ls]+Sm[rs])%Mod;
    Sm[x]=(Sm[x]+1ll*Lz[x]*Key[x]%Mod)%Mod;return;
}
int Query(int x,int l,int r,int ql,int qr,int o){
    if (l==ql&&r==qr){
	int ret=Sm[x];
	ret=(ret+1ll*Key[x]*o%Mod)%Mod;
	return ret;
    }
    int mid=(l+r)>>1;o+=Lz[x];
    if (qr<=mid) return Query(ls,l,mid,ql,qr,o);
    else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr,o);
    else return (Query(ls,l,mid,ql,mid,o)+Query(rs,mid+1,r,mid+1,qr,o))%Mod;
}
