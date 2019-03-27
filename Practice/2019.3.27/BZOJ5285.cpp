#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=1010;
const int maxM=5010;
const int Mod=1000000007;

int n,m,Q;
char In[maxM];
bool Mp[maxM][maxN];
int Sorter[maxM],Key[maxM];

bool icmp(int a,int b);
int main(){
    scanf("%d%d%d",&n,&m,&Q);
    for (int i=1;i<=n;i++){
        scanf("%s",In+1);
        for (int j=1;j<=m;j++) Mp[j][n-i+1]=In[j]-'0';
    }
    for (int i=1;i<=m;i++) for (int j=1;j<=n;j++) Key[i]=(2ll*Key[i]%Mod+Mp[i][j])%Mod;
    int FULL=1;for (int i=1;i<=n;i++) FULL=2ll*FULL%Mod;Key[m+1]=FULL;Sorter[m+1]=m+1;
    for (int i=1;i<=m;i++) Sorter[i]=i;
    sort(&Sorter[1],&Sorter[m+1],icmp);
    while (Q--){
        scanf("%s",In+1);int p1,p2;
        for (p1=1;p1<=m;p1++) if (In[Sorter[p1]]=='1') break;
        for (p2=m;p2>=1;p2--) if (In[Sorter[p2]]=='0') break;
        if (p2>=p1) puts("0");
        else printf("%d\n",(Key[Sorter[p1]]-Key[Sorter[p2]]+Mod)%Mod);
    }
    return 0;
}
bool icmp(int a,int b){
    for (int i=1;i<=n;i++){
        if (Mp[a][i]==Mp[b][i]) continue;
        return Mp[a][i]<Mp[b][i];
    }
    return 0;
}