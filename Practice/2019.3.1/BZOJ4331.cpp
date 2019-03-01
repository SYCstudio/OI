#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=505000;
const int maxM=1010000;
const int inf=1000000000;

int n,m,dfncnt,dfn[maxN],low[maxN],top,St[maxN],idcnt,Id[maxN];
int edgecnt=-1,Hd[maxN],Nt[maxM],V[maxM],W[maxM];
vector<pair<int,int> > T[maxN];
int Val[maxN];

void Add_Edge(int u,int v,int w);
void tarjan(int u,int faw);
bool check(int u,int fa,int w,int f);
int main(){
    scanf("%d%d",&n,&m);memset(Hd,-1,sizeof(Hd));int mxw=0;
    for (int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);mxw=max(mxw,w);
        Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    for (int i=1;i<=n;i++) if (dfn[i]==0) tarjan(i,edgecnt+10),T[0].push_back(make_pair(Id[i],inf));
    //for (int i=1;i<=n;i++) cout<<Id[i]<<" ";cout<<endl;
    for (int i=1;i<=n;i++) for (int j=Hd[i];j!=-1;j=Nt[j]) if (Id[i]!=Id[V[j]]) T[Id[i]].push_back(make_pair(Id[V[j]],W[j]));
    //cout<<idcnt<<endl;
    //for (int i=0;i<=idcnt;i++) for (int j=0,sz=T[i].size();j<sz;j++) cout<<i<<"->"<<T[i][j].first<<" "<<T[i][j].second<<endl;
    int l=0,r=mxw,Ans=-1;
    while (l<=r){
        int mid=(l+r)>>1;
        //cout<<"mid:"<<mid<<endl;
        //cout<<"mid:"<<check(0,0,mid)<<endl;
        if (check(0,0,mid,0)) Ans=mid,r=mid-1;else l=mid+1;
    }
    printf("%d\n",Ans);return 0;
}
void Add_Edge(int u,int v,int w){
     Nt[++edgecnt]=Hd[u];Hd[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
     return;
}
void tarjan(int u,int faw){
    dfn[u]=low[u]=++dfncnt;St[++top]=u;
    for (int i=Hd[u];i!=-1;i=Nt[i])
        if (i!=faw){
            int v=V[i];
            if (!dfn[v]) tarjan(v,i^1),low[u]=min(low[u],low[v]);
            else low[u]=min(low[u],dfn[v]);
        }
    if (dfn[u]==low[u]){
        ++idcnt;int v;
        do v=St[top--],Id[v]=idcnt;while (v!=u);
    }
    return;
}
bool check(int u,int fa,int w,int f){
    Val[u]=0;
    for (int i=0,sz=T[u].size();i<sz;i++) if (T[u][i].first==fa) if (T[u][i].second<=w) f=1;
    for (int i=0,sz=T[u].size();i<sz;i++)
        if (T[u][i].first!=fa){
            if (check(T[u][i].first,u,w,f)) return 1;
            Val[u]+=Val[T[u][i].first]+(T[u][i].second<=w);
        }
    return Val[u]>=3||(Val[u]>=2&&f);
}