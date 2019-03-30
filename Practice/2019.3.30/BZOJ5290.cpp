#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxN=20010;
const int maxH=40;
const ll INF=1e18;

int n;
int Rs[maxN],Rt[maxN];
ll F[maxN][maxH][maxH],A[maxN],B[maxN],C[maxN];
int Cnt[2][maxN+maxN];

void dfs_dp(int u);
ll Get(int u,int i,int j);
int main(){
    scanf("%d",&n);
    for (int i=1;i<n;i++){
        scanf("%d%d",&Rs[i],&Rt[i]);
        if (Rs[i]<0) Rs[i]=n-Rs[i];
        if (Rt[i]<0) Rt[i]=n-Rt[i];
    }
    for (int i=1;i<=n;i++) scanf("%lld%lld%lld",&A[i],&B[i],&C[i]);
    dfs_dp(1);printf("%lld\n",F[1][0][0]);return 0;
}
void dfs_dp(int u){
    if (u>n) return;
    Cnt[0][Rt[u]]=Cnt[0][Rs[u]]=Cnt[0][u];
    Cnt[1][Rt[u]]=Cnt[1][Rs[u]]=Cnt[1][u];
    ++Cnt[0][Rs[u]];++Cnt[1][Rt[u]];
    dfs_dp(Rs[u]);dfs_dp(Rt[u]);
    for (int i=0;i<=Cnt[0][u];i++) for (int j=0;j<=Cnt[1][u];j++) F[u][i][j]=min(Get(Rs[u],i+1,j)+Get(Rt[u],i,j),Get(Rs[u],i,j)+Get(Rt[u],i,j+1));
    return;
}
ll Get(int u,int i,int j){
    if (u<=n) return F[u][i][j];
    return C[u-n]*(A[u-n]+Cnt[0][u]-i)*(B[u-n]+Cnt[1][u]-j);
}