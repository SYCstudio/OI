#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxN=50500;

int n;
ll Seq[maxN];

int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%lld",&Seq[i]);
        sort(&Seq[1],&Seq[n+1]);
        bool flag=1;
        for (ll i=1;i<=n;i++){
            Seq[i]+=Seq[i-1];
            if (Seq[i]<i*(i-1)/2){
                flag=0;break;
            }
        }
        if (Seq[n]!=1ll*n*(n-1)/2) flag=0;
        flag?puts("It seems to have no problem."):puts("The data have been tampered with!");
    }
    return 0;
}