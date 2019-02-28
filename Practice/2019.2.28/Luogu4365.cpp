#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=1700;
const int maxM=maxN<<1;
const int Mod=64123;

class Data{
    public:
    int a,b,c,d;
    Data(int _a=1,int _b=0,int _c=0,int _d=0){
        a=_a;b=_b;c=_c;d=_d;return;
    }
};
class SegmentData{
    public:
    int ls,rs;
    Data lazy;
};

int n,Val[maxN],K,W;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int nodecnt=0,rt[maxN],Y[maxN],Poly[maxN],Final[maxN];
SegmentData S[maxN*100];

int QPow(int x,int cnt);
void Add_Edge(int u,int v);
void dfs_calc(int u,int fa,int x);
int Newnode();
Data operator + (Data A,Data B);
void PushDown(int x);
void Modify(int &x,int l,int r,int ql,int qr,Data d);
int Merge(int x,int y);
int Query(int x,int l,int r);
int main(){
    //freopen("in","r",stdin);//freopen("out","w",stdout);
    scanf("%d%d%d",&n,&K,&W);memset(Head,-1,sizeof(Head));
    for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
    for (int i=1;i<n;i++){
        int u,v;scanf("%d%d",&u,&v);Add_Edge(u,v);Add_Edge(v,u);
    }
    for (int i=1;i<=n+1;i++){
        nodecnt=0;memset(rt,0,sizeof(rt));
        dfs_calc(1,0,i);
        Y[i]=Query(rt[1],1,W);
    }
    //for (int i=1;i<=n+1;i++) cout<<Y[i]<<" ";cout<<endl;
    Poly[0]=1;
    for (int i=1;i<=n+1;i++){
        for (int j=n+1;j>=1;j--) Poly[j]=(1ll*Poly[j]*(Mod-i)%Mod+Poly[j-1])%Mod;
        Poly[0]=1ll*Poly[0]*(Mod-i)%Mod;
    }
    for (int i=1;i<=n+1;i++){
        int mul=1,invi=QPow(Mod-i,Mod-2);for (int j=1;j<=n+1;j++) if (i!=j) mul=1ll*mul*(i-j+Mod)%Mod;mul=QPow(mul,Mod-2);
        Poly[0]=1ll*Poly[0]*invi%Mod;
        for (int j=1;j<=n+1;j++) Poly[j]=1ll*(Poly[j]-Poly[j-1]+Mod)%Mod*invi%Mod;
        for (int j=0;j<=n+1;j++) Final[j]=(Final[j]+1ll*Poly[j]*Y[i]%Mod*mul%Mod)%Mod;
        for (int j=n+1;j>=1;j--) Poly[j]=(1ll*Poly[j]*(Mod-i)%Mod+Poly[j-1])%Mod;
        Poly[0]=1ll*Poly[0]*(Mod-i)%Mod;
    }
    int Ans=0;
    for (int i=K;i<=n;i++) Ans=(Ans+Final[i])%Mod;
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
void Add_Edge(int u,int v){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
    return;
}
void dfs_calc(int u,int fa,int x){
    Modify(rt[u],1,W,1,W,((Data){0,1,0,0}));
    for (int i=Head[u];i!=-1;i=Next[i]) if (V[i]!=fa) dfs_calc(V[i],u,x),rt[u]=Merge(rt[u],rt[V[i]]);
    Modify(rt[u],1,W,1,Val[u],((Data){x,0,0,0}));
    Modify(rt[u],1,W,1,W,((Data){1,0,1,0}));
    Modify(rt[u],1,W,1,W,((Data){1,1,0,0}));
    return;
}
int Newnode(){
    int id=++nodecnt;
    S[id].ls=S[id].rs=0;S[id].lazy=Data();
    return id;
}
Data operator + (Data A,Data B){
    return ((Data){1ll*A.a*B.a%Mod,(1ll*A.b*B.a%Mod+B.b)%Mod,(1ll*A.a*B.c%Mod+A.c)%Mod,(1ll*A.b*B.c%Mod+A.d+B.d)%Mod});
}
void PushDown(int x){
    if (!S[x].ls) S[x].ls=Newnode();
    if (!S[x].rs) S[x].rs=Newnode();
    S[S[x].ls].lazy=S[S[x].ls].lazy+S[x].lazy;
    S[S[x].rs].lazy=S[S[x].rs].lazy+S[x].lazy;
    S[x].lazy=Data();
    return;
}
void Modify(int &x,int l,int r,int ql,int qr,Data d){
    if (x==0) x=Newnode();
    if (l==ql&&r==qr){
        S[x].lazy=S[x].lazy+d;
        return;
    }
    PushDown(x);int mid=(l+r)>>1;
    if (qr<=mid) Modify(S[x].ls,l,mid,ql,qr,d);
    else if (ql>=mid+1) Modify(S[x].rs,mid+1,r,ql,qr,d);
    else Modify(S[x].ls,l,mid,ql,mid,d),Modify(S[x].rs,mid+1,r,mid+1,qr,d);
    return;
}
int Merge(int x,int y){
    if (!x||!y) return x+y;
    if (!S[x].ls&&!S[x].rs) swap(x,y);
    if (!S[y].ls&&!S[y].rs){
        S[x].lazy=S[x].lazy+((Data){S[y].lazy.b,0,0,S[y].lazy.d});return x;
    }
    PushDown(x);PushDown(y);
    S[x].ls=Merge(S[x].ls,S[y].ls);S[x].rs=Merge(S[x].rs,S[y].rs);return x;
}
int Query(int x,int l,int r){
    if (l==r) return S[x].lazy.d;
    int mid=(l+r)>>1;PushDown(x);
    return (Query(S[x].ls,l,mid)+Query(S[x].rs,mid+1,r))%Mod;
}