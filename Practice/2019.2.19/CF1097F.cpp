#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<iostream>
using namespace std;

const int maxN=101000;
const int maxB=7010;

int n,m,Mu[maxB];
bitset<maxB> B[maxN],fb[maxB],ifb[maxB];

int main(){
    Mu[1]=1;
    for (int i=1;i<=7000;i++) for (int j=i+i;j<=7000;j+=i) Mu[j]^=Mu[i];
    for (int i=1;i<=7000;i++) for (int j=i;j<=7000;j+=i) fb[j][i]=1;
    for (int i=1;i<=7000;i++) for (int j=i;j<=7000;j+=i) ifb[i][j]=Mu[j/i];
    scanf("%d%d",&n,&m);
    while (m--){
        int opt,x,y,z;scanf("%d%d%d",&opt,&x,&y);
        if (opt==2||opt==3) scanf("%d",&z);
        if (opt==1) B[x]=fb[y];
        if (opt==2) B[x]=B[y]^B[z];
        if (opt==3) B[x]=B[y]&B[z];
        if (opt==4) printf("%d",(int)(B[x]&ifb[y]).count()&1);
    }
    printf("\n");
    return 0;
}