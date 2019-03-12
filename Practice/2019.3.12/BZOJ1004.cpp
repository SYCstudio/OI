#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=62;
const int maxM=21;
int P;
int Seq[maxN],Mark[maxN];
int F[maxM][maxM][maxM],G[maxM][maxM][maxM];

int QPow(int x,int cnt);
void Plus(int &x,int y);
int main(){
    int sr,sb,sg,m,n;scanf("%d%d%d%d%d",&sr,&sb,&sg,&m,&P);n=sr+sb+sg;
    int sum=0;int Case=m+1;
    while (Case--){
        if (Case==m) for (int i=1;i<=n;i++) Seq[i]=i,Mark[i]=0;
        else for (int i=1;i<=n;i++) scanf("%d",&Seq[i]),Mark[i]=0;
        F[0][0][0]=1;
        for (int p=1;p<=n;p++)
            if (!Mark[p]){
                int cnt=0,now=p;while (!Mark[Seq[now]]) ++cnt,Mark[now=Seq[now]]=1;
                memcpy(G,F,sizeof(G));memset(F,0,sizeof(F));
                for (int i=0;i<=sr;i++) for (int j=0;j<=sb;j++) for (int k=0;k<=sg;k++){
                    if (!G[i][j][k]) continue;
                    if (i+cnt<=sr) Plus(F[i+cnt][j][k],G[i][j][k]);
                    if (j+cnt<=sb) Plus(F[i][j+cnt][k],G[i][j][k]);
                    if (k+cnt<=sg) Plus(F[i][j][k+cnt],G[i][j][k]);
                }
            }
        for (int i=0;i<=sr;i++) for (int j=0;j<=sb;j++) for (int k=0;k<=sg;k++) Plus(sum,F[i][j][k]);
    }
    sum=1ll*sum*QPow(m+1,P-2)%P;
    printf("%d\n",sum);return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%P;
        cnt>>=1;x=1ll*x*x%P;
    }
    return ret;
}
void Plus(int &x,int y){
    x+=y;if (x>=P) x-=P;return;
}