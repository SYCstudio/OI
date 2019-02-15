#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=5010;
const int Num=5000;
const int Mod=998244353;

int n,now,all=1;
int Dp[2][maxN+maxN][2][2];
int F[maxN+maxN][2],G[maxN+maxN][2];
char Input[maxN];

void Get();
void Plus(int &x,int y);
int main(){
    freopen("in","r",stdin);
    Get();for (int j=-Num;j<=Num;j++) for (int b=0;b<=1;b++) F[maxN+j][b]=(Dp[now][maxN+j][b][0]+Dp[now][maxN+j][b][1])%Mod;
    Get();for (int j=-Num;j<=Num;j++) for (int b=0;b<=1;b++) G[maxN+j][b]=((Dp[now][maxN+j][b][0]+G[maxN+j-1][b])%Mod+Dp[now][maxN+j][b][1])%Mod;
    int Ans=0;
    for (int i=-Num;i<=Num;i++){
        //int lstans=Ans;
        Ans=(Ans+1ll*F[maxN+i][0]*G[maxN-i][0]%Mod)%Mod;
        Ans=(Ans+1ll*F[maxN+i][1]*G[maxN-i][0]%Mod)%Mod;
        Ans=(Ans+1ll*F[maxN+i][0]*G[maxN-i][1]%Mod)%Mod;
        Ans=(Ans+1ll*F[maxN+i][1]*G[maxN-i-1][1]%Mod)%Mod;
        //if (lstans!=Ans) cout<<i<<" "<<Ans-lstans<<endl;
    }
    Ans=(all-Ans+Mod)%Mod;
    printf("%d\n",Ans);return 0;
}
void Get(){
    mem(Dp,0);
    scanf("%s",Input+1);n=strlen(Input+1);
    for (int i=1;i<=n;i++) if (Input[i]=='?') all=2ll*all%Mod;
    now=1;Dp[now][maxN][1][1]=1;Input[n+1]='P';
    for (int i=n+1,mn;i>=1;i--){
        now^=1;mem(Dp[now],0);
        for (int j=-Num;j<=Num;j++)
            for (int b=0;b<=1;b++)
                for (int c=0;c<=1;c++)
                    if (Dp[now^1][maxN+j][b][c]){
                        int key=Dp[now^1][maxN+j][b][c];
                        if (Input[i-1]=='V'||Input[i-1]=='?'){
                            if (c) mn=min(j+1,1),Plus(Dp[now][maxN+mn][b&(mn!=1||i==n+1)][0],key);
                            else mn=j+1,Plus(Dp[now][maxN+mn][b][0],key);
                        }
                        if (Input[i-1]=='P'||Input[i-1]=='?'){
                            if (c) mn=min(j-1,-1),Plus(Dp[now][maxN+mn][b&(mn!=-1||i==n+1)][1],key);
                            else mn=j-1,Plus(Dp[now][maxN+mn][b][1],key);
                        }
                        if (i==1){
                            if (c==0) Plus(Dp[now][maxN+j][b][c],Dp[now^1][maxN+j][b][c]);
                            else{
                                mn=min(0,j);
                                Plus(Dp[now][maxN+mn][b&(mn!=0)][c],Dp[now^1][maxN+j][b][c]);
                            }
                        }
                    }
        /*
        for (int j=-Num;j<=Num;j++)
        for (int b=0;b<=1;b++)
            for (int c=0;c<=1;c++)
                if (Dp[now][maxN+j][b][c])
                    cout<<"("<<i-1<<","<<j<<","<<b<<","<<c<<")"<<Dp[now][maxN+j][b][c]<<endl;
        //*/
    }
    /*
    //cout<<endl;
    for (int j=-Num;j<=Num;j++)
        for (int b=0;b<=1;b++)
            for (int c=0;c<=1;c++)
                if (Dp[now][maxN+j][b][c])
                    cout<<"("<<1<<","<<j<<","<<b<<","<<c<<")"<<Dp[now][maxN+j][b][c]<<endl;
    cout<<endl;
    //*/
    return;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}