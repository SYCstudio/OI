#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxN=3030;
const ll INF=1e18;

int n,m;
vector<int> B[maxN];

ll Calc(int limit);
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
	int x,y;scanf("%d%d",&x,&y);B[x].push_back(y);
    }
    for (int i=1;i<=m;i++) sort(B[i].begin(),B[i].end());
    ll Ans=INF;for (int i=1;i<=n;i++) Ans=min(Ans,Calc(i));
    printf("%lld\n",Ans);return 0;
}
ll Calc(int limit){
    vector<int> Rn;ll sum=0;int cnt=B[1].size();
    for (int i=2;i<=m;i++){
	int sz=B[i].size();
	for (int j=0;j<=sz-limit;j++) sum=sum+B[i][j],++cnt;
	for (int j=max(0,sz-limit+1);j<sz;j++) Rn.push_back(B[i][j]);
    }
    sort(Rn.begin(),Rn.end());
    if (cnt+Rn.size()<limit) return INF;
    int p=0;
    while (cnt<limit){
	sum=sum+Rn[p];++cnt;++p;
    }
    return sum;
}
