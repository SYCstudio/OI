#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=300000*4;
const int maxM=maxN<<1;

int n,m,S;
vector<pair<int,int> > To[maxN];
int ufs[maxN],edgecnt=-1,Head[maxN],Next[maxM],V[maxM],D[maxN],Odd[maxN],WId[maxN];
int vis[maxM],top,St[maxN],Stid[maxN];

int find(int x);
void Add_Edge(int u,int v,int id);
void dfs_init(int u,int fa,int fid);
void dfs_eul(int u,int fid);

int main(){
    //freopen("3.in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d",&n,&m);mem(Head,-1);S=n+n+1;
    for (int i=1;i<=n;i++) ufs[i]=i;
    for (int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);Odd[u]^=1;Odd[v]^=1;
        if (find(u)!=find(v)) To[u].push_back(make_pair(v,i)),To[v].push_back(make_pair(u,i)),ufs[find(u)]=find(v);
        else Add_Edge(u,v+n,i);
    }
    for (int i=1;i<=n;i++) if (Odd[i]) Add_Edge(S,i,0);
    dfs_init(1,0,0);dfs_eul(1,0);--top;
    //for (int i=1;i<=S;i++) for (int j=Head[i];j!=-1;j=Next[j]) if (i<V[j]) cout<<i<<" "<<V[j]<<endl;
    mem(vis,0);int start=1;
    //for (int i=1;i<=top;i++) cout<<St[i]<<" ";cout<<endl;
    while (St[start]!=S) ++top,St[top]=St[start],Stid[top]=Stid[start],++start;
    for (int i=start+1,j;i<=top;i=j+1){
        j=i;while (j<=top&&St[j]!=S) j++;
        printf("%d %d %d\n",St[i],St[j-1],j-i-1);
        //cout<<"[";for (int k=i;k+1<j;k++) cout<<St[k]<<" ";cout<<"]"<<endl;
        for (int k=i;k+1<j;k++) printf("%d ",Stid[k]);
        printf("\n");
    }
    return 0;
}
int find(int x){
    if (ufs[x]!=x) ufs[x]=find(ufs[x]);
    return ufs[x];
}
void Add_Edge(int u,int v,int id){
    ++D[u];++D[v];
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;WId[edgecnt]=id;
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;WId[edgecnt]=id;
    return;
}
void dfs_init(int u,int fa,int fid){
    for (int i=0,sz=To[u].size();i<sz;i++) if (To[u][i].first!=fa) dfs_init(To[u][i].first,u,To[u][i].second);
    if (fa==0) return;
    if (D[u]&1) Add_Edge(u,fa+n,fid);
    else Add_Edge(u+n,fa,fid);
    return;
}
void dfs_eul(int u,int fid){
    for (int &i=Head[u];i!=-1;)
        if (vis[i>>1]==0){
            int j=i;i=Next[i];vis[j>>1]=1;
            dfs_eul(V[j],WId[j]);
        }
        else i=Next[i];
    St[++top]=u;Stid[top]=fid;return;
}