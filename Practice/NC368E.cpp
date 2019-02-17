#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define pw(x) (1<<(x))
#define ls (x<<1)
#define rs (ls|1)
const int maxN=101000<<1;
const int maxM=maxN<<1;
const int maxB=18;
class Data{
    public:
    int u,v,a,b,opt;
    Data(){u=v=a=b=opt=0;}
    Data(int x,int y){
        u=b=x;v=a=y;opt=0;return;
    }
};

int n,m,Log[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Dep[maxN],ecnt,lft[maxN],rht[maxN],ST[maxB][maxN],Fa[maxB][maxN];
Data S[maxN<<2];

void Add_Edge(int u,int v);
void dfs_init(int u,int fa);
int LCA(int u,int v);
int Dst(int u,int v);
bool In(int u,int v,int p);
int GetMax(int p,int a,int b,int c,int d);
Data operator + (Data A,Data B);
void Build(int x,int l,int r);
void Modify(int x,int l,int r,int p,int u,int v);
Data Query(int x,int l,int r,int ql,int qr);

int main(){
    freopen("in","r",stdin);freopen("out","w",stdout);
    mem(Head,-1);for (int i=2;i<maxN;i++) Log[i]=Log[i>>1]+1;
    scanf("%d%d",&n,&m);
    for (int i=1;i<n;i++){
        int u,v;scanf("%d%d",&u,&v);
        Add_Edge(u,v);Add_Edge(v,u);
    }
    dfs_init(1,0);
    //for (int i=1;i<=ecnt;i++) cout<<ST[0][i]<<" ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<"["<<lft[i]<<" "<<rht[i]<<"]"<<endl;
    for (int i=1;i<maxB;i++)
        for (int j=1;j+pw(i)-1<=ecnt;j++)
            if (Dep[ST[i-1][j]]<=Dep[ST[i-1][j+pw(i-1)]]) ST[i][j]=ST[i-1][j];
            else ST[i][j]=ST[i-1][j+pw(i-1)];
    for (int i=1;i<maxB;i++) for (int j=1;j<=n;j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];

    Build(1,1,m);
    int Q;scanf("%d",&Q);
    while (Q--){
        int opt;scanf("%d",&opt);
        if (opt==1){
            int l,r;scanf("%d%d",&l,&r);
            Data R=Query(1,1,m,l,r);
            //cout<<R.u<<" "<<R.v<<" "<<R.a<<" "<<R.b<<" "<<R.opt<<endl;
            if (R.opt==1) puts("-1");
            else{
                int now=Dep[R.a]>=Dep[R.b]?R.a:R.b,skip=Dst(R.a,R.b)/2,f=Dst(R.a,R.b)&1;
                for (int i=maxB-1;i>=0;i--) if (skip&pw(i)) now=Fa[i][now];
                //cout<<"skip now:"<<skip<<" "<<now<<" "<<Dst(R.a,R.b)<<endl;
                if (f){
                    int fa=Fa[0][now];//cout<<"fa:"<<fa<<endl;
                    if (In(R.u,R.v,now)&&In(R.u,R.v,fa)) printf("%d\n",min(now,fa));
                    else if (In(R.u,R.v,now)) printf("%d\n",now);
                    else if (In(R.u,R.v,fa)) printf("%d\n",fa);
                    else printf("%d\n",min(R.u,R.v));
                }
                else{
                    if (In(R.u,R.v,now)) printf("%d\n",now);
                    else printf("%d\n",min(R.u,R.v));
                }
            }
        }
        if (opt==2){
            int x,u,v;scanf("%d%d%d",&x,&u,&v);
            Modify(1,1,m,x,u,v);
        }
    }
    return 0;
}

void Add_Edge(int u,int v){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
    return;
}
void dfs_init(int u,int fa){
    Dep[u]=Dep[fa]+1;ST[0][++ecnt]=u;lft[u]=ecnt;Fa[0][u]=fa;
    for (int i=Head[u];i!=-1;i=Next[i])
        if (V[i]!=fa) dfs_init(V[i],u),ST[0][++ecnt]=u;
    rht[u]=ecnt;return;
}
int LCA(int u,int v){
    int l=min(lft[u],lft[v]),r=max(rht[u],rht[v]);
    int lg=Log[r-l+1];
    //cout<<"LCA:"<<u<<" "<<v<<" "<<ST[lg][l]<<" "<<ST[lg][r-pw(lg)+1]<<"|"<<l<<" "<<r<<endl;
    if (Dep[ST[lg][l]]<=Dep[ST[lg][r-pw(lg)+1]]) return ST[lg][l];
    return ST[lg][r-pw(lg)+1];
}
int Dst(int u,int v){
    return Dep[u]+Dep[v]-2*Dep[LCA(u,v)];
}
bool In(int u,int v,int p){
    return Dst(u,v)==Dst(u,p)+Dst(v,p);
}
int GetMax(int p,int a,int b,int c,int d){
    int r=a;
    if (Dst(p,b)>Dst(p,r)) r=b;
    if (Dst(p,c)>Dst(p,r)) r=c;
    if (Dst(p,d)>Dst(p,r)) r=d;
    return r;
}
Data operator + (Data A,Data B){
    if (lft[A.u]<lft[B.u]) swap(A,B);
    cout<<"Merge:"<<A.u<<" "<<A.v<<" "<<A.a<<" "<<A.b<<"|"<<B.u<<" "<<B.v<<" "<<B.a<<" "<<B.b<<endl;
    Data R;if (A.opt||B.opt){R.opt=1;return R;}
    if (In(A.u,A.v,B.u)&&In(A.u,A.v,B.v)) R.u=B.u,R.v=B.v;
    else{
        int u1=LCA(A.u,B.u),u2=LCA(A.u,B.v);
        R.u=Dep[u1]>=Dep[u2]?u1:u2;
        u1=LCA(A.v,B.u);u2=LCA(A.v,B.v);
        R.v=Dep[u1]>=Dep[u2]?u1:u2;
    }
    if (lft[R.u]>lft[R.v]) swap(R.u,R.v);
    cout<<R.u<<" "<<R.v<<endl;
    if (!In(A.u,A.v,R.u)||!In(A.u,A.v,R.v)||!In(B.u,B.v,R.u)||!In(B.u,B.v,R.v)){R.opt=1;return R;}
    R.a=GetMax(R.u,A.a,A.b,B.a,B.b);
    R.b=GetMax(R.v,A.a,A.b,B.a,B.b);
    return R;
}
void Build(int x,int l,int r){
    if (l==r){
        int u,v;scanf("%d%d",&u,&v);
        if (lft[u]>lft[v]) swap(u,v);
        S[x]=((Data){u,v});return;
    }
    int mid=(l+r)>>1;Build(ls,l,mid);Build(rs,mid+1,r);
    //cout<<x<<":"<<l<<" "<<r<<endl;
    S[x]=S[ls]+S[rs];
    return;
}
void Modify(int x,int l,int r,int p,int u,int v){
    if (l==r){
        if (lft[u]>lft[v]) swap(u,v);S[x]=((Data){u,v});return;
    }
    int mid=(l+r)>>1;if (p<=mid) Modify(ls,l,mid,p,u,v);else Modify(rs,mid+1,r,p,u,v);
    S[x]=S[ls]+S[rs];return;
}
Data Query(int x,int l,int r,int ql,int qr){
    //cout<<"Q:"<<x<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<":"<<S[x].u<<" "<<S[x].v<<" "<<S[x].a<<" "<<S[x].b<<" "<<S[x].opt<<endl;
    if (l==ql&&r==qr) return S[x];
    int mid=(l+r)>>1;
    if (qr<=mid) return Query(ls,l,mid,ql,qr);
    else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
    return Query(ls,l,mid,ql,mid)+Query(rs,mid+1,r,mid+1,qr);
}