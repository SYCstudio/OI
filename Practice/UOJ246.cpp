#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxN=101000;
const int maxB=410;

int n,m,K,Seq[maxN];
int Mn[maxN][maxB];

int main(){
    scanf("%d%d%d",&n,&m,&K);int sqr=sqrt(m);
    for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
    for (int i=1;i<n;i++) Mn[i][2]=abs(Seq[i]-Seq[i+1]);
    for (int b=3;b<=sqr;b++)
        for (int i=1;i+b-1<=n;i++)
            Mn[i][b]=min(min(Mn[i][b-1],Mn[i+1][]
}