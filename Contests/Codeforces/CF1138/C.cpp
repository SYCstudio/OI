#include<bits/stdc++.h>
using namespace std;

const int maxN=1010;

int n,m;
int Mp[maxN][maxN],num,Num[maxN];
int X[maxN][maxN],Y[maxN][maxN],Mx[maxN];

int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&Mp[i][j]);
    for (int j=1;j<=m;j++){
        num=0;for (int i=1;i<=n;i++) Num[++num]=Mp[i][j];
        sort(&Num[1],&Num[num+1]);num=unique(&Num[1],&Num[num+1])-Num-1;
        for (int i=1;i<=n;i++) Y[i][j]=lower_bound(&Num[1],&Num[num+1],Mp[i][j])-Num;
        Mx[j]=num;
    }
    for (int i=1;i<=n;i++){
        num=0;for (int j=1;j<=m;j++) Num[++num]=Mp[i][j];
        sort(&Num[1],&Num[num+1]);num=unique(&Num[1],&Num[num+1])-Num-1;
        for (int j=1;j<=m;j++){
            int x=lower_bound(&Num[1],&Num[num+1],Mp[i][j])-Num;
            int k1=Mx[j],k2=num;
            if (x>Y[i][j]) k1+=x-Y[i][j];
            else k2+=Y[i][j]-x;
            printf("%d ",max(k1,k2));
        }
        printf("\n");
    }
    return 0;
}