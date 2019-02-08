#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

typedef long long ll;
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))

class Point{
    public:
    ll x,y;
    ll len(){
        return sqrt(sqr(x)+sqr(x));
    }
    ll calc(ll k){
        return x*k+y;
    }
    Point operator + (Point A){
        return ((Point){x+A.x,y+A.y});
    }
    Point operator - (Point A){
        return ((Point){x-A.x,y-A.y});
    }
};
class VData{
    public:
    int v,a,b;
};

const int maxN=100100*2;
const int maxM=maxN<<1;
const int inf=1000000000;

int n,m;
vector<VData> To[maxN],Sn[maxN];
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
pair<ll,ll> W[maxM];
int vis[maxM],rte,rtsize,Sz[maxN],tot[2];
Point C[2][maxN],Bp[maxN],Out[maxN];
vector<Point> Ans;

void dfs_init(int u,int fa);
void Add_Edge(int u,int v,pair<ll,ll> w);
void dfs_root(int u,int fa,int size);
void dfs_get(int u,int fa,int opt,ll a,ll b);
void Divide(int u,int size);
ll Cross(Point A,Point B);
bool cmpx(Point A,Point B);
bool cmpy(Point A,Point B);
bool cmpc(Point A,Point B);
ostream & operator << (ostream & os,Point A);
void Convex(Point *P,int &T);
double Intersection(Point A,Point B);

int main(){
    freopen("in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d",&n,&m);mem(Head,-1);
    for (int i=1;i<n;i++){
        int u,v,a,b;scanf("%d%d%d%d",&u,&v,&a,&b);
        To[u].push_back((VData){v,a,b});To[v].push_back((VData){u,a,b});
    }
    dfs_init(1,1);
    for (int i=1,sz;i<=n;i++)
        if (Sn[i].size()<=n)
            for (int j=0,sz=Sn[i].size();j<sz;j++) Add_Edge(i,Sn[i][j].v,make_pair(Sn[i][j].a,Sn[i][j].b));
        else{
            int ls=++n,rs=++n;Add_Edge(i,ls,make_pair(0,0));Add_Edge(i,rs,make_pair(0,0));
            for (int j=0,sz=Sn[i].size();j<sz;j++)
                if (j&1) Sn[rs].push_back(Sn[i][j]);
                else Sn[ls].push_back(Sn[i][j]);
        }
    Divide(1,n);
    sort(Ans.begin(),Ans.end(),cmpx);
    //for (int i=0,sz=Ans.size();i<sz;i++) cout<<Ans[i]<<" ";cout<<endl;
    int top=0;
    for (int i=0,sz=Ans.size();i<sz;i++){
        while (top>=1&&Out[top].x==Ans[i].x) --top;
        while (top>=2&&Intersection(Out[top-1],Out[top])>=Intersection(Out[top],Ans[i])) --top;
        Out[++top]=Ans[i];
    }
    for (int i=0,j=1;i<m;i++){
        while (j<top&&Out[j+1].calc(i)>=Out[j].calc(i)) ++j;
        printf("%lld ",Out[j].calc(i));
    }
    printf("\n");return 0;
}
void dfs_init(int u,int fa){
    for (int i=0,sz=To[u].size();i<sz;i++) if (To[u][i].v!=fa) Sn[u].push_back(To[u][i]),dfs_init(To[u][i].v,u);
    return;
}
void Add_Edge(int u,int v,pair<ll,ll> w){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
    return;
}
void dfs_root(int u,int fa,int size){
    Sz[u]=1;
    for (int i=Head[u];i!=-1;i=Next[i])
        if (V[i]!=fa&&vis[i>>1]==0){
            dfs_root(V[i],u,size);Sz[u]+=Sz[V[i]];
            int k=max(Sz[V[i]],size-Sz[V[i]]);
            if (k<rtsize) rtsize=k,rte=i;
        }
    return;
}
void dfs_get(int u,int fa,int opt,ll a,ll b){
    C[opt][++tot[opt]]=((Point){a,b});
    for (int i=Head[u];i!=-1;i=Next[i])
        if (V[i]!=fa&&vis[i>>1]==0) dfs_get(V[i],u,opt,a+W[i].first,b+W[i].second);
    return;
}
void Divide(int start,int size){
    rtsize=inf;dfs_root(start,start,size);
    if (rtsize==inf) return;
    int u=V[rte],v=V[rte^1];vis[rte>>1]=1;tot[0]=tot[1]=0;
    //cout<<u<<" "<<v<<endl;
    dfs_get(u,u,0,0,0);dfs_get(v,v,1,0,0);

    //for (int i=1;i<=tot[0];i++) cout<<C[0][i]<<" ";cout<<endl;
    //for (int i=1;i<=tot[1];i++) cout<<C[1][i]<<" ";cout<<endl;

    Convex(C[0],tot[0]);Convex(C[1],tot[1]);

    //for (int i=1;i<=tot[0];i++) cout<<C[0][i]<<" ";cout<<endl;
    //for (int i=1;i<=tot[1];i++) cout<<C[1][i]<<" ";cout<<endl;

    int top=1,p0=1,p1=1,up0=0,up1=0;Bp[1]=C[0][1]+C[1][1];
    C[0][tot[0]+1]=C[0][1];C[1][tot[1]+1]=C[1][1];
    for (int i=1;i<=tot[0];i++) C[0][i]=C[0][i+1]-C[0][i];
    for (int i=1;i<=tot[1];i++) C[1][i]=C[1][i+1]-C[1][i];

    while (up0<tot[0]&&(C[0][up0+1].y>0||(C[0][up0+1].y==0&&C[0][up0+1].x>=0))) ++up0;
    while (up1<tot[1]&&(C[1][up1+1].y>0||(C[1][up1+1].y==0&&C[1][up1+1].x>=0))) ++up1;
    //for (int i=1;i<=tot[0];i++) cout<<C[0][i]<<" ";cout<<endl;
    //for (int i=1;i<=tot[1];i++) cout<<C[1][i]<<" ";cout<<endl;

    while (p0<=up0||p1<=up1){
        //cout<<"Compare:"<<p0<<" "<<p1<<":"<<C[0][p0]<<" "<<C[1][p1]<<endl;
        if (p1>up1||(p0<=up0&&Cross(C[0][p0],C[1][p1])>=0)) ++top,Bp[top]=Bp[top-1]+C[0][p0++];
        else ++top,Bp[top]=Bp[top-1]+C[1][p1++];
    }
    while (p0<=tot[0]||p1<=tot[1]){
        //cout<<"Compare:"<<p0<<" "<<p1<<":"<<C[0][p0]<<" "<<C[1][p1]<<endl;
        if (p1>tot[1]||(p0<=tot[0]&&Cross(C[0][p0],C[1][p1])>=0)) ++top,Bp[top]=Bp[top-1]+C[0][p0++];
        else ++top,Bp[top]=Bp[top-1]+C[1][p1++];
    }

    //for (int i=1;i<=top;i++) cout<<Bp[i]<<" ";cout<<endl;

    Convex(Bp,top);

    //for (int i=1;i<=top;i++) cout<<Bp[i]<<" ";cout<<endl;

    for (int i=1;i<=top;i++) Ans.push_back(Bp[i]+((Point){W[rte].first,W[rte].second}));
    Divide(u,Sz[u]);Divide(v,size-Sz[u]);return;
}
ll Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
bool cmpx(Point A,Point B){
    if (A.x!=B.x) return A.x<B.x;
    return A.y<B.y;
}
bool cmpy(Point A,Point B){
    if (A.y!=B.y) return A.y<B.y;
    return A.x<B.x;
}
bool cmpc(Point A,Point B){
    return Cross(A,B)>0||(Cross(A,B)==0&&A.len()<B.len());
}
ostream & operator << (ostream &os,Point A){
    os<<"("<<A.x<<","<<A.y<<")";return os;
}
void Convex(Point *P,int &T){
    static Point St[maxN];sort(&P[1],&P[T+1],cmpy);
    Point base=P[1];for (int i=1;i<=T;i++) P[i]=P[i]-base;
    sort(&P[1],&P[T+1],cmpc);int top=0;
    for (int i=1;i<=T;i++){
        while (top>=2&&Cross(P[i]-St[top-1],St[top]-St[top-1])>=0) --top;
        St[++top]=P[i];
    }
    T=top;for (int i=1;i<=top;i++) P[i]=St[i]+base;return;
}
double Intersection(Point A,Point B){
    return (double)(B.y-A.y)/(double)(A.x-B.x);
}