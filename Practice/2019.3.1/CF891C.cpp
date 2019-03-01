#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int maxN=505000;

class Edge{
    public:
    int u,v,w,id;
};

int n,m,ufs[maxN];
Edge E[maxN],Sorter[maxN];

int find(int x);
bool cmp1(Edge A,Edge B);
bool cmp2(Edge A,Edge B);

int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w),E[i].id=i;
    sort(&E[1],&E[m+1],cmp1);for (int i=1;i<=n;i++) ufs[i]=i;
    for (int l=1,r;l<=m;l=r+1){
        r=l;while (r<m&&E[r+1].w==E[l].w) ++r;
        for (int i=l;i<=r;i++) E[i].u=find(E[i].u),E[i].v=find(E[i].v);
        for (int i=l;i<=r;i++) if (find(E[i].u)!=find(E[i].v)) ufs[find(E[i].u)]=find(E[i].v);
    }
    sort(&E[1],&E[m+1],cmp2);
    int Q;scanf("%d",&Q);
    while (Q--){
        int K;scanf("%d",&K);
        for (int i=1;i<=K;i++){
            int id;scanf("%d",&id);
            Sorter[i]=E[id];
        }
        bool flag=1;sort(&Sorter[1],&Sorter[K+1],cmp1);
        for (int l=1,r;l<=K&&flag;l=r+1){
            r=l;while (r<K&&Sorter[r+1].w==Sorter[l].w) ++r;
            for (int i=l;i<=r;i++) ufs[Sorter[i].u]=Sorter[i].u,ufs[Sorter[i].v]=Sorter[i].v;
            for (int i=l;i<=r&&flag;i++) if (find(Sorter[i].u)==find(Sorter[i].v)) {flag=0;break;} else ufs[find(Sorter[i].u)]=find(Sorter[i].v);
        }
        flag?puts("YES"):puts("NO");
    }
    return 0;
}
int find(int x){
    if (ufs[x]!=x) ufs[x]=find(ufs[x]);
    return ufs[x];
}
bool cmp1(Edge A,Edge B){
    return A.w<B.w;
}
bool cmp2(Edge A,Edge B){
    return A.id<B.id;
}