#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=2100;

int n,P;
int F[maxN],G[maxN],C[maxN][maxN];

int main(){
    scanf("%d%d",&n,&P);C[0][0]=1;
    for (int i=1;i<=n;i++) for (int j=C[i][0]=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
    F[1]=1;G[1]=0;F[0]=1;
    for (int i=2;i<=n;i++){
        for (int j=0;j+1<=i;j++){
            int k=i-j-1,c=C[i-1][j];
            //cout<<j<<" "<<k<<"->"<<i<<endl;
            int mul=1ll*F[j]*F[k]%P*c%P;
            F[i]=(F[i]+mul)%P;
            G[i]=(G[i]+1ll*G[j]*F[k]%P*c%P)%P;
            G[i]=(G[i]+1ll*G[k]*F[j]%P*c%P)%P;
            G[i]=(G[i]+1ll*j*(n-j)%P*mul%P)%P;
            G[i]=(G[i]+1ll*k*(n-k)%P*mul%P)%P;
        }
    }
    //for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<G[i]<<" ";cout<<endl;
    printf("%d\n",G[n]);return 0;
}