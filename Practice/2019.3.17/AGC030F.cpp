#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=310;
const int Mod=1e9+7;

int n,Seq[maxN+maxN];
int use[maxN+maxN],one[maxN+maxN];
int F[2][maxN][maxN];

void Plus(int &x,int y);
int main(){
    int ecnt=0,ocnt=0;
    scanf("%d",&n);for (int i=1;i<=n+n;i++) scanf("%d",&Seq[i]);
    for (int i=1;i<=n+n;i+=2)
        if (Seq[i]==-1&&Seq[i+1]==-1) ++ecnt;
        else if (Seq[i]==-1||Seq[i+1]==-1) one[Seq[i]+Seq[i+1]+1]=1,++ocnt;
        else use[Seq[i]]=use[Seq[i+1]]=1;
    int now=1;F[now][0][0]=1;
    for (int i=n+n;i>=1;i--)
        if (!use[i]){
            now^=1;memset(F[now],0,sizeof(F[now]));
            for (int j=0;j<=ecnt+ocnt;j++)
                for (int k=0;k<=ocnt;k++)
                    if (F[now^1][j][k]){
                        int key=F[now^1][j][k];
                        if (one[i]){
                            if (j) Plus(F[now][j-1][k],key);
                            Plus(F[now][j][k+1],key);
                        }
                        else{
                            Plus(F[now][j+1][k],key);
                            if (j) Plus(F[now][j-1][k],key);
                            if (k) Plus(F[now][j][k-1],1ll*k*key%Mod);
                        }
                    }
        }
    int Ans=F[now][0][0];for (int i=1;i<=ecnt;i++) Ans=1ll*Ans*i%Mod;
    printf("%d\n",Ans);return 0;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}