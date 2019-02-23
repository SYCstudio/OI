#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=710;
const int maxM=maxN*maxN*2;

int n,m,E;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int match[maxN],pre[maxN],tim,Tim[maxN],ql,qr,Qu[maxN],ufs[maxN],label[maxN];

void Add_Edge(int u,int v);
int find(int x);
int bfs(int S);
int LCA(int u,int v);
void Push(int u,int v,int lca);
int main(){
    //freopen("in","r",stdin);
    int Case;scanf("%d",&Case);
    while (Case--){
        mem(Head,-1);edgecnt=-1;mem(match,0);
        scanf("%d%d%d",&n,&m,&E);
        for (int i=1;i<=E;i++){
            int u,v;scanf("%d%d",&u,&v);
            Add_Edge(u,n+v);Add_Edge(u,n+m+v);Add_Edge(u,n+m+m+v);
        }
        for (int i=1;i<=m;i++) Add_Edge(i+n,i+n+m),Add_Edge(i+n+m,i+n+m+m),Add_Edge(i+n+m+m,i+n);
        int Ans=0;
        for (int i=1;i<=n+m+m+m;i++) if (!match[i]) Ans+=bfs(i);
        printf("%d\n",Ans-n);
        //for (int i=1;i<=n;i++) cout<<match[i]<<" ";cout<<endl;
        for (int i=1;i<=n;i++) printf("%d ",(match[i]-n-1)%m+1);printf("\n");
    }
    return 0;
}
void Add_Edge(int u,int v){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
    return;
}
int find(int x){
    if (ufs[x]!=x) ufs[x]=find(ufs[x]);
    return ufs[x];
}
int bfs(int S){
    for (int i=1;i<=n+m+m+m;i++) ufs[i]=i,pre[i]=label[i]=0;
    label[Qu[ql=qr=1]=S]=1;
    while (ql<=qr)
        for (int u=Qu[ql++],i=Head[u];i!=-1;i=Next[i]){
            if (find(V[i])==find(u)||label[V[i]]==2) continue;
            int v=V[i];
            if (!label[v]){
                if (!match[v]){
                    int now=u,lst=v;
                    while (now){
                        int tmp=match[now];
                        match[now]=lst;match[lst]=now;
                        lst=tmp;now=pre[lst];
                    }
                    return 1;
                }
                label[v]=2;label[match[v]]=1;
                Qu[++qr]=match[v];pre[v]=u;
            }
            else{
                int lca=LCA(u,v);Push(u,v,lca);Push(v,u,lca);
            }
        }
    return 0;
}
int LCA(int u,int v){
    u=find(u);v=find(v);++tim;
    while (Tim[u]!=tim){
        Tim[u]=tim;u=find(pre[match[u]]);
        if (v) swap(u,v);
    }
    return u;
}
void Push(int x,int y,int lca){
    while (find(x)!=lca){
        pre[x]=y;y=match[x];
        if (label[y]==2) Qu[++qr]=y,label[y]=1;
        if (find(x)==x) ufs[x]=lca;
        if (find(y)==y) ufs[y]=lca;
        x=pre[y];
    }
    return;
}