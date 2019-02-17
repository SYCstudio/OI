#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=20;
const int maxM=(1<<maxN)+10;
const int Mod=1000000007;
const int inv2=500000004;

int n;
char In[maxM];
int A[maxM],C[maxM],pw[maxN+10];

void FWT(int N,int *P,int opt);

int main(){
    scanf("%d",&n);int N=1<<n;scanf("%s",In);
    for (int i=0;i<N;i++) A[i]=In[i]-'0';
    FWT(N,A,1);
    for (int i=0;i<N;i++) A[i]=1ll*A[i]*A[i]%Mod;
    FWT(N,A,-1);
    //for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
    pw[0]=1;for (int i=1;i<maxN+10;i++) pw[i]=2ll*pw[i-1]%Mod;
    for (int i=0;i<N;i++) C[i]=C[i>>1]+(i&1);
    int Ans=0;
    for (int i=0;i<N;i++) Ans=(Ans+1ll*pw[n-C[i]]*A[i]%Mod)%Mod;
    Ans=3ll*Ans%Mod;
    printf("%d\n",Ans);return 0;
}
void FWT(int N,int *P,int opt){
    for (int i=1;i<N;i<<=1)
        for (int j=0;j<N;j+=(i<<1))
            for (int k=0;k<i;k++){
                int X=P[j+k],Y=P[j+k+i];
                P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
                if (opt==-1) P[j+k]=1ll*P[j+k]*inv2%Mod,P[j+k+i]=1ll*P[j+k+i]*inv2%Mod;
            }
    return;
}