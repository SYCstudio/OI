#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define Dct(x) (lower_bound(&Num[1],&Num[num+1],x)-Num)
const int maxN=101000*2;
const int maxM=maxN*4;

int n,m;
int num,Num[maxN],L[maxN],R[maxN],Dg[maxN];
int edgecnt=-1,Hd[maxN],Nt[maxM],V[maxM],vis[maxM];

void Add_Edge(int u,int v);
void dfs(int u);
int main(){
    memset(Hd,-1,sizeof(Hd));
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d%d",&L[i],&R[i]),++R[i],Num[++num]=L[i],Num[++num]=R[i];
    sort(&Num[1],&Num[num+1]);num=unique(&Num[1],&Num[num+1])-Num-1;
    for (int i=1;i<=n;i++) L[i]=Dct(L[i]),R[i]=Dct(R[i]),Add_Edge(L[i],R[i]);
    for (int i=1,lst=0;i<=num;i++) if (Dg[i]&1) if (lst) Add_Edge(lst,i),lst=0;else lst=i;
    for (int i=0;i<n;i++) if (!vis[i]) dfs(V[i<<1]);
    for (int i=0;i<n;i++) printf("%d ",vis[i]-1);printf("\n");
    return 0;
}
void Add_Edge(int u,int v){
    ++Dg[u];++Dg[v];
    Nt[++edgecnt]=Hd[u];Hd[u]=edgecnt;V[edgecnt]=v;
    Nt[++edgecnt]=Hd[v];Hd[v]=edgecnt;V[edgecnt]=u;
    return;
}
void dfs(int u){
    for (int &i=Hd[u];i!=-1;)
        if (!vis[i>>1]){
            int j=i;i=Nt[i];vis[j>>1]=((j&1)?1:2);dfs(V[j]);
        }
        else i=Nt[i];
    //cout<<u<<endl;
    return;
}