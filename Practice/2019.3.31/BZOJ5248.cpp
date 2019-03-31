#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<map>
using namespace std;

typedef unsigned long long ull;
const int maxN=11;
const int inf=2000000000;

map<ull,int> DP;
int n,m;
int A[maxN][maxN],B[maxN][maxN];
int Seq[maxN];

int dfs_dp(int cnt);

int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&A[i][j]);
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&B[i][j]);
    Seq[0]=n;printf("%d\n",dfs_dp(1));return 0;
}
int dfs_dp(int cnt){
    if (cnt==n*m+1) return 0;
    ull hash=0;for (int i=1;i<=m;i++) hash=hash*10+Seq[i];
    if (DP.count(hash)) return DP[hash];
    int ret;if (cnt&1) ret=-inf;else ret=inf;
    for (int i=1;i<=m;i++)
        if (Seq[i]!=n&&Seq[i]<Seq[i-1]){
            ++Seq[i];
            if (cnt&1) ret=max(ret,dfs_dp(cnt+1)+A[Seq[i]][i]);else ret=min(ret,dfs_dp(cnt+1)-B[Seq[i]][i]);
            --Seq[i];
        }
    return DP[hash]=ret;
}