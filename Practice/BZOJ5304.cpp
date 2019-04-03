#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;
const int maxN=202000;
const int Alpha=26;
const int maxB=20;
const int inf=2000000000;

class SAM{
    public:
    int son[Alpha],len,fail;
};
class SegmentData{
    public:
    int ls,rs;
};
class Question{
    public:
    int s,t,l,r;
};

int n,K;
char S[maxN],T[maxN];
SAM Sm[maxN];
int lst,smcnt=1,sgcnt,rt[maxN],Fa[maxB][maxN];
SegmentData Sg[maxN*20];
int Mch[maxN],Mlen[maxN];
ll Ans[maxN];
Question Qm[maxN];
vector<int> HQ[55],Qsam[maxN],Pt[maxN];

void Extend(int c);
void Insert(int &x,int l,int r,int p);
int Merge(int u,int v);
void dfs_calc(int u);
void dfs_seg(int x,int l,int r,int s,int t,int len,int &lst,int id);
int main(){
    scanf("%d%d",&n,&K);scanf("%s",S+1);
    for (int i=1;i<=n;i++) Extend(S[i]-'a'),Insert(rt[lst],1,n,i);
    for (int i=2;i<=smcnt;i++) Pt[Sm[i].fail].push_back(i),Fa[0][i]=Sm[i].fail;
    for (int i=1;i<maxB;i++) for (int j=1;j<=smcnt;j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];

    scanf("%s",T+1);
    for (int i=1,now=1,len=0;i<=n;i++){
        int c=T[i]-'a';
        while (now&&!Sm[i].son[c]) now=Sm[now].fail,len=Sm[now].len;
        if (!now){
            now=1;len=0;
        }
        else{
            now=Sm[now].son[c];++len;
        }
        Mch[i]=now;Mlen[i]=len;
    }

    int Q;scanf("%d",&Q);
    for (int i=1;i<=Q;i++){
        scanf("%d%d%d%d",&Qm[i].s,&Qm[i].t,&Qm[i].l,&Qm[i].r);int len=Qm[i].r-Qm[i].l+1;
        if (len<=50) HQ[len].push_back(i);
        else{
            if (Mlen[Qm[i].r]<len) continue;
            int now=Mch[Qm[i].r];
            for (int i=maxB-1;i>=0;i--) if (Fa[i][now]&&Sm[Fa[i][now]].len>=len) now=Fa[i][now];
            Qsam[now].push_back(i);
        }
    }

    dfs_calc(1);
}
void Extend(int c){
    int np=++smcnt,p=lst;lst=np;Sm[np].len=Sm[p].len+1;
    while (p&&Sm[p].son[c]==0) Sm[p].son[c]=np,p=Sm[p].fail;
    if (p==0) Sm[np].fail=1;
    else{
        int q=Sm[p].son[c];
        if (Sm[q].len==Sm[p].len+1) Sm[np].fail=q;
        else{
            int nq=++smcnt;Sm[nq]=Sm[q];Sm[nq].len=Sm[p].len+1;Sm[np].fail=Sm[q].fail=nq;
            while (p&&Sm[p].son[c]==q) Sm[p].son[c]=nq,p=Sm[p].fail;
        }
    }
    return;
}
void Insert(int &x,int l,int r,int p){
    if (x==0) x=++sgcnt;
    if (l==r) return;
    int mid=(l+r)>>1;if (p<=mid) Insert(Sg[x].ls,l,mid,p);else Insert(Sg[x].rs,mid+1,r,p);
    return;
}
int Merge(int u,int v){
    if (!u||!v) return u+v;
    Sg[u].ls=Merge(Sg[u].ls,Sg[v].ls);Sg[u].rs=Merge(Sg[u].rs,Sg[v].rs);
    return u;
}
void dfs_calc(int u){
    for (int i=0,sz=Pt[u].size();i<sz;i++) dfs_calc(Pt[u][i]),rt[u]=Merge(rt[u],rt[Pt[u][i]]);
    for (int i=0,sz=Qsam[u].size();i<sz;i++){
        int id=Qsam[u][i],lst=-inf;
        dfs_seg(rt[u],1,n,Qm[id].s,Qm[id].t,Qm[id].r-Qm[id].l,lst,id);
    }
}
void dfs_seg(int x,int l,int r,int s,int t,int len,int &lst,int id){
    if (l==r){
        if (l>=s&&l<=t&&l>=lst+len){
        }
    }
}