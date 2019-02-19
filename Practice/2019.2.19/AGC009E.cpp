#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=4010;
const int Mod=1e9+7;

int n,m,K,L;
int F[maxN][maxN];

void Plus(int &x,int y);
int main(){
    scanf("%d%d%d",&n,&m,&K);--m;L=(n+m)/(K-1);
    F[0][0]=1;int Ans=0;
    for (int i=1;i<=L;i++)
        for (int j=0;j<=min(i*(K-1),n);j++){
            for (int k=0;k<=K-1&&k<=j;k++)
                Plus(F[i][j],F[i-1][j-k]);
            if (j%(K-1)==n%(K-1)&&(K-1)*i-j<=m&&((K-1)*i-j)%(K-1)==m%(K-1)) Plus(Ans,F[i][j]-F[i-1][j]);//,cout<<i<<" "<<j<<endl;
        }
    printf("%d\n",Ans);return 0;
}
void Plus(int &x,int y){
    x+=y;
    if (x>=Mod) x-=Mod;
    if (x<0) x+=Mod;
    return;
}