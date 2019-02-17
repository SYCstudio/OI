#include<bits/stdc++.h>
#define lc no<<1
#define rc no<<1|1
#define ls lc,l,mid
#define rs rc,mid+1,r
#define mid ((l+r)>>1)
using namespace std;
const int _=2e5+25;
int n,m,p[18][_],dep[_],st[20][_],sl[_],sr[_],lg[_],cnt;
vector<int>e[_];
int cmp(int x,int y){return dep[x]<dep[y];}
void dfs(int fa,int u){
    p[0][u]=fa;dep[u]=dep[fa]+1;
    st[0][++cnt]=u;sl[u]=cnt;
    for(int v:e[u]){
        if(v==fa)continue;
        dfs(u,v);st[0][++cnt]=u;
    }
    sr[u]=cnt;
}
int lca(int x,int y){
    int l=min(sl[x],sl[y]),r=max(sr[x],sr[y]),k=lg[r-l+1];
    return min(st[k][l],st[k][r-(1<<k)+1],cmp);
}
int dis(int x,int y){return dep[x]+dep[y]-2*dep[lca(x,y)];}
int Get(int x,int y){
    for(int i=0;i<=18;++i)
        if(y>>i&1)x=p[i][x];
    return x;
}
void init(){
    dfs(0,1);
    for(int i=1;i<=17;++i)
        for(int j=1;j<=n;++j)
            p[i][j]=p[i-1][p[i-1][j]];
    for(int i=1,k=1;i<=18;++i,k<<=1)
        for(int j=1;j+k<=cnt;++j)
            st[i][j]=min(st[i-1][j],st[i-1][j+k],cmp);
    for(int i=1;i<=cnt;++i)lg[i]=log2(i);
}
struct ljq {
    int s,t,g,x,y;
    ljq friend operator +(ljq a,ljq b){
        ljq c;
        if(a.s==-1||b.s==-1)return c.s=-1,c;
        if(dep[a.g]<dep[b.g])swap(a,b);
        if(lca(a.g,b.s)!=a.g&&lca(a.g,b.t)!=a.g)c.s=-1;
        else {
            c.s=max(lca(a.s,b.s),lca(a.s,b.t),cmp);
            c.t=max(lca(a.t,b.s),lca(a.t,b.t),cmp);
            c.g=lca(c.s,c.t);
            if(dis(a.x,c.s)>dis(a.x,c.t))swap(a.x,a.y);
            if(dis(b.x,c.s)>dis(b.x,c.t))swap(b.x,b.y);
            if(dis(a.x,c.s)<dis(b.x,c.s))c.x=b.x; else c.x=a.x;
            if(dis(a.y,c.t)<dis(b.y,c.t))c.y=b.y; else c.y=a.y;
        }
        return c;
    }
    int Get_Ans(){
        if(s==-1)return -1;
//      cerr<<s<<" "<<t<<" "<<g<<" "<<x<<" "<<y<<endl;
        int D=dis(x,y),d=dis(s,t),d1=dis(s,x),d2=dis(t,y);
        if(d1>d2)swap(x,y),swap(s,t),swap(d1,d2);
        if(d1+d<=d2)return t;
        int A,B;
        int a=D/2-d1,b=D/2+(D&1)-d2;
        A=Get(s,a);if(dep[A]<dep[g])A=Get(t,b);
        a=D/2+(D&1)-d1,b=D/2-d2;
        B=Get(s,a);if(dep[B]<dep[g])B=Get(t,b);
        return min(A,B);
    }
    istream friend & operator>>(istream&istr,ljq&a){
        istr>>a.s>>a.t;a.g=lca(a.s,a.t);
        a.x=a.s;a.y=a.t; return istr;
    }
}t[_<<2];
void build(int no,int l,int r){
    if(l==r)return cin>>t[no],void();
    build(ls);build(rs);
    t[no]=t[lc]+t[rc];
}
void modify(int no,int l,int r,int k){
    if(l==r)return cin>>t[no],void();
    if(k<=mid)modify(ls,k);
    else modify(rs,k);
    t[no]=t[lc]+t[rc];
}
ljq query(int no,int l,int r,int L,int R){
    if(l>=L&&r<=R)return t[no];
    if(R<=mid)return query(ls,L,R);
    if(L>mid)return query(rs,L,R);
    return query(ls,L,R)+query(rs,L,R);
}
int main(){
    freopen("in","r",stdin);freopen("dout","w",stdout);
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        e[u].push_back(v);e[v].push_back(u);
    }
    init();build(1,1,m);
    int Q;cin>>Q;
    while(Q--){
        int opt;cin>>opt;
        if(opt==1){
            int l,r;cin>>l>>r;
            cout<<query(1,1,m,l,r).Get_Ans()<<endl;
        }
        if(opt==2){
            int x;cin>>x;
            modify(1,1,m,x);
        }
    }
    return 0;
}