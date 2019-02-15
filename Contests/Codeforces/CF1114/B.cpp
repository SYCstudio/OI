#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxN=202000;

int n,m,K;
pair<ll,int> Seq[maxN];
bool vis[maxN];

int main(){
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=n;i++) scanf("%lld",&Seq[i].first),Seq[i].second=i;
    sort(&Seq[1],&Seq[n+1]);reverse(&Seq[1],&Seq[n+1]);
    ll Ans=0;
    for (int i=1;i<=m*K;i++) Ans+=Seq[i].first,vis[Seq[i].second]=1;
    printf("%lld\n",Ans);
    int tot=0;
    for (int i=1,cnt=0;i<=n;i++){
        cnt+=vis[i];
        if (cnt==m){
            ++tot;if (tot==K) break;
            printf("%d ",i);cnt=0;
        }
    }
    printf("\n");return 0;
}