#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=32;
const int Mod=1e9+7;

int F[maxN][2][2][2];
int G[maxN][2][2][2];
int pw[maxN];
int Calc(int n,int m,int K);
void Plus(int &x,int y);
int main(){
    pw[0]=1;for (int i=1;i<maxN;i++) pw[i]=2ll*pw[i-1]%Mod;
    int Q;scanf("%d",&Q);
    while (Q--){
        int x1,y1,x2,y2,K;scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&K);
        --x1;--y1;--x2;--y2;
        int c=Calc(x2,y2,K);
        c=(c-Calc(x1-1,y2,K)+Mod)%Mod;
        c=(c-Calc(x2,y1-1,K)+Mod)%Mod;
        c=(c+Calc(x1-1,y1-1,K))%Mod;
        printf("%d\n",c);
    }
    return 0;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}
int Calc(int n,int m,int K){
    if (n<0||m<0) return 0;
    memset(F,0,sizeof(F));memset(G,0,sizeof(G));++n;++m;++K;
    Plus(F[0][(n&1)==0][(m&1)==0][(K&1)==0],1);
    Plus(F[0][1][1][1],1);Plus(G[0][1][1][1],1);
    for (int i=0;i+1<maxN;i++){
        int bn=(n>>i)&1,bm=(m>>i)&1,bk=(K>>i)&1;
        for (int a=0;a<=1;a++)
            for (int b=0;b<=1;b++)
                for (int c=0;c<=1;c++)
                    for (int fn=0;fn<=1;fn++)
                        for (int fm=0;fm<=1;fm++)
    }
}