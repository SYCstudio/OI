#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=10100000;
const int Mod=1e9+7;

int L,R;
bool use[maxN];

int Fc(int n);
int main(){
    scanf("%d%d",&L,&R);int cnt=0;
    for (int i=L;i<=R;i++)
        if (!use[i]){
            ++cnt;
            for (int j=i+i;j<=R;j+=i) use[j]=1;
        }
}
int Fc(int n){
    int mul=1;for (int i=1;i<=n;i++) mul=1ll*mul*i%Mod;return mul;
}