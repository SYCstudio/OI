#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int Mod=1000000009;

int main(){
    int n;scanf("%d",&n);
    int sum=0,mul=4,pw=2;
    while (n>2){
        n-=2;pw=2ll*pw%Mod;mul=1ll*mul*(pw-3+Mod)%Mod;
        sum=(sum+mul)%Mod;
    }
    sum=(2ll*sum*sum%Mod+8ll*sum%Mod+10)%Mod;
    printf("%d\n",sum);return 0;
}