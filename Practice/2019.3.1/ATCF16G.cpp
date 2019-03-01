#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxN=202000;
const int maxM=maxN<<1;
const ll INF=1e18;

class Edge{
    public:
    int u,v;ll w;
};

int n,m,Q,ufs[maxN];
ll Val[maxN];
Edge E[maxM];

bool cmp(Edge A,Edge B);
int find(int x);
int main(){
    scanf("%d%d",&n,&Q);for (int i=1;i<=n;i++) Val[i]=INF;
    while (Q--){
        int a,b,c;scanf("%d%d%d",&a,&b,&c);++a;++b;
        E[++m]=((Edge){a,b,c});Val[a]=min(Val[a],(ll)c+1);Val[b]=min(Val[b],(ll)c+2);
    }
    Val[1]=min(Val[1],Val[n]+2);for (int i=2;i<=n;i++) Val[i]=min(Val[i-1]+2,Val[i]);
    Val[1]=min(Val[1],Val[n]+2);for (int i=2;i<=n;i++) Val[i]=min(Val[i-1]+2,Val[i]);
    E[++m]=((Edge){n,1,Val[n]});for (int i=1;i<n;i++) E[++m]=((Edge){i,i+1,Val[i]});
    sort(&E[1],&E[m+1],cmp);ll Ans=0;for (int i=1;i<=n;i++) ufs[i]=i;
    for (int i=1;i<=m;i++) if (find(E[i].u)!=find(E[i].v)) Ans+=E[i].w,ufs[find(E[i].u)]=find(E[i].v);
    printf("%lld\n",Ans);return 0;
}
bool cmp(Edge A,Edge B){
    return A.w<B.w;
}
int find(int x){
    if (ufs[x]!=x) ufs[x]=find(ufs[x]);
    return ufs[x];
}