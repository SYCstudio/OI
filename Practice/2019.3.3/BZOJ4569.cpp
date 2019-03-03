#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000;
const int maxB=17;

int n,m,Lg[maxN];
int ufs[maxB][maxN];

int find(int b,int u);
void Merge(int b,int l1,int l2);
int main(){
    for (int i=2;i<maxN;i++) Lg[i]=Lg[i>>1]+1;
    scanf("%d%d",&n,&m);
    for (int i=0,idcnt=0;i<maxB;i++) for (int j=1;j+(1<<i)-1<=n;j++) ufs[i][j]=j;
    while (m--){
        int l1,r1,l2,r2;scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        int lg=Lg[r1-l1+1];Merge(lg,l1,l2);Merge(lg,r1-(1<<lg)+1,r2-(1<<lg)+1);
    }
    int num=-1;
    for (int i=1;i<=n;i++) if (find(0,i)==i) ++num;
    int Ans=9;while (num--) Ans=10ll*Ans%1000000007;
    printf("%d\n",Ans);return 0;
}
int find(int b,int u){
    if (ufs[b][u]!=u) ufs[b][u]=find(b,ufs[b][u]);
    return ufs[b][u];
}
void Merge(int b,int l1,int l2){
    int f1=find(b,l1),f2=find(b,l2);
    if (f1!=f2){
        if (b) Merge(b-1,l1,l2),Merge(b-1,l1+(1<<(b-1)),l2+(1<<(b-1)));
        ufs[b][f1]=f2;
    }
    return;
}