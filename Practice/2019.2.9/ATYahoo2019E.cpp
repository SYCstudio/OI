#include<bits/stdc++.h>
using namespace std;

const int maxN=310;
const int Mod=998244353;

int n,m;
bitset<maxN> B[maxN];
int C[maxN][maxN],Sm[maxN],pw[maxN];

int main(){
    pw[0]=1;for (int i=1;i<maxN;i++) pw[i]=2ll*pw[i-1]%Mod;
    scanf("%d%d",&n,&m);
    int cnt=0,one=0;
    for (int i=1;i<=n;i++){
        bitset<maxN> I;I.reset();
        for (int j=1;j<=m;j++){
            int x;scanf("%d",&x);I[j]=x;
        }
        bool flag=0;
        for (int j=1;j<=m;j++)
            if (I[j]){
                if (B[j]==0){
                    B[j]=I;flag=1;break;
                }
                else I^=B[j];
            }
        if (flag==0) ++cnt;
    }

    printf("%lld\n",1ll*(pw[n]-pw[cnt]+Mod)%Mod*pw[m-1]%Mod);return 0;
}