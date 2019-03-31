#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=5010;

int n,H[maxN],F[maxN][maxN];

double Slope(int a,int b);
int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&H[i]);
    int Ans=0;
    for (int r=1;r<=n;r++){
        Ans^=(F[r][r]=1);if (r==1) continue;
        Ans^=(F[r-1][r]=1);int lst=r-1,sum=1;
        for (int l=r-2;l>=1;l--){
            if (Slope(l,r)<Slope(lst,r)) sum+=min(F[l+1][lst],F[l+1][lst-1]),lst=l;
            Ans^=(F[l][r]=sum+min(F[l][lst],F[l][lst-1]));
        }
    }
    printf("%d\n",Ans);return 0;
}
double Slope(int a,int b){
    return (double)(H[a]-H[b])/(double)(a-b);
}