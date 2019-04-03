#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=101000<<1;
const int Mod=1e9+7;

int n,m,pw[maxN];char Col[maxN];
vector<int> T[maxN],Vt[maxN];
int dfncnt,dfn[maxN],low[maxN],idcnt,top,St[maxN];
int mkcnt,Mark[maxN],Mksum[maxN],Mksz[maxN],Sz[maxN],Fob[maxN],Sn[maxN];

void tarjan(int u,int fa);
void dfs_init(int u,int fa,int mk);
void dfs_calc(int u,int fa);
void Outp(int ocnt,int mcnt,int n,int m);
int main(){
    pw[0]=1;for (int i=1;i<maxN;i++) pw[i]=2ll*pw[i-1]%Mod;
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d%d",&n,&m);
        idcnt=n;dfncnt=mkcnt=0;
        memset(dfn,0,sizeof(dfn));memset(Mark,0,sizeof(Mark));memset(Mksum,0,sizeof(Mksum));
        memset(Fob,0,sizeof(Fob));memset(Sn,0,sizeof(Sn));memset(Mksz,0,sizeof(Mksz));
        for (int i=1;i<=m;i++){
            int u,v;scanf("%d%d",&u,&v);
            T[u].push_back(v);T[v].push_back(u);
        }
        scanf("%s",Col+1);
        for (int i=1;i<=n;i++) if (!dfn[i]) tarjan(i,i);
        for (int i=1;i<=n;i++) if (!Mark[i]) dfs_init(i,i,++mkcnt);
        for (int i=1,j=0;i<=n;i++) if (Mark[i]>j) ++j,dfs_calc(i,i);

        //for (int i=1;i<=idcnt;i++) for (int j=0;j<Vt[i].size();j++) cout<<i<<"-"<<Vt[i][j]<<endl;
        //for (int i=1;i<=n;i++) cout<<Sn[i]<<" ";cout<<endl;

        int oddcnt=0;for (int i=1;i<=mkcnt;i++) oddcnt+=(Mksum[i]&1);
        Outp(oddcnt,mkcnt,n,m);

        for (int i=1;i<=n;i++)
            if (Mksz[Mark[i]]==1) Outp(oddcnt,mkcnt-1,n-1,m-T[i].size());
            else if (Sn[i]==1){
                if (Col[i]=='1'){
                    if (Mksum[Mark[i]]&1) Outp(oddcnt-1,mkcnt,n-1,m-T[i].size());
                    else Outp(oddcnt+1,mkcnt,n-1,m-T[i].size());
                }
                else Outp(oddcnt,mkcnt,n-1,m-T[i].size());
            }
            else{
                int oo=oddcnt,mm=mkcnt;
                if (Mksum[Mark[i]]&1) --oo;
                if (oo||Fob[i]) printf("0 ");else Outp(oo,mm-1+Sn[i],n-1,m-T[i].size());
            }
        printf("\n");

        for (int i=1;i<=idcnt;i++) T[i].clear(),Vt[i].clear();
    }
    return 0;
}
void tarjan(int u,int fa){
    dfn[u]=low[u]=++dfncnt;St[++top]=u;
    for (int i=0,sz=T[u].size();i<sz;i++){
        int v=T[u][i];if (v==fa) continue;
        if (!dfn[v]){
            tarjan(v,u);low[u]=min(low[u],low[v]);
            if (low[v]>=dfn[u]){
                ++idcnt;int v;
                do v=St[top--],Vt[idcnt].push_back(v),Vt[v].push_back(idcnt);while (v!=u);
                St[++top]=u;
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
    return;
}
void dfs_init(int u,int fa,int mk){
    Mark[u]=mk;Mksum[mk]+=(Col[u]=='1');++Mksz[mk];
    for (int i=0,sz=Vt[u].size();i<sz;i++) if (Vt[u][i]!=fa) dfs_init(Vt[u][i],u,mk);
    return;
}
void dfs_calc(int u,int fa){
    Sz[u]=(Col[u]=='1');
    for (int i=0,sz=Vt[u].size();i<sz;i++) if (Vt[u][i]!=fa) dfs_calc(Vt[u][i],u),Sz[u]+=Sz[Vt[u][i]],Fob[u]|=(Sz[Vt[u][i]]&1);
    Sn[u]=Vt[u].size();
    Fob[u]|=((Mksum[Mark[u]]-Sz[u])&1);
    return;
}
void Outp(int ocnt,int mcnt,int n,int m){
    if (ocnt) printf("0 ");else printf("%d ",pw[m-n+mcnt]);
    return;
}