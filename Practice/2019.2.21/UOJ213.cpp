#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

#define pw(x) (1<<(x))
typedef long long ll;
const int maxN=1010000;
const int maxB=20;
const int Mod=998244353;

int n,Seq[maxN],Lg[maxN];
int ST[maxB][maxN];
ll Sk[maxN],Sb[maxN];

bool cmp(int a,int b);
int GetMx(int l,int r);
void Divide(int l,int r);
int main(){
    for (int i=2;i<maxN;i++) Lg[i]=Lg[i>>1]+1;
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
    for (int i=1;i<=n;i++) ST[0][i]=i;
    for (int i=1;i<maxB;i++) for (int j=1;j+pw(i)-1<=n;j++) ST[i][j]=max(ST[i-1][j],ST[i-1][j+pw(i-1)],cmp);
    Divide(1,n);
    for (int i=1;i<=n;i++) Sk[i]=(Sk[i]+Sk[i-1])%Mod,Sb[i]=(Sb[i]+Sb[i-1])%Mod;
    int Ans=0;
    for (int i=1;i<=n;i++) Ans=Ans^((1ll*i*Sk[i]%Mod+Sb[i])%Mod);
    printf("%d\n",Ans);return 0;
}
bool cmp(int a,int b){
    return Seq[a]<Seq[b];
}
int GetMx(int l,int r){
    int lg=Lg[r-l+1];return max(ST[lg][l],ST[lg][r-pw(lg)+1],cmp);
}
void Divide(int l,int r){
    //cout<<"Divide:"<<l<<" "<<r<<endl;
    if (l==r){
        Sb[1]=(Sb[1]+Seq[l]%Mod)%Mod;Sb[2]=(Sb[2]-Seq[l]%Mod+Mod)%Mod;
        //for (int i=1,s1=0,s2=0;i<=n;i++) s1=(s1+Sk[i])%Mod,s2=(s2+Sb[i]%Mod),cout<<(1ll*i*s1%Mod+s2)%Mod<<" ";cout<<endl;
        return;
    }
    ll p=GetMx(l,r),mx=max(p-l+1,r-p+1),mn=min(p-l+1,r-p+1),sz=r-l+1;
    //cout<<"p:"<<p<<" "<<mx<<" "<<sz<<endl;
    ll k=Mod-Seq[p]%Mod,b=(Seq[p]%Mod-1ll*sz*k%Mod+Mod)%Mod;
    Sk[mx]=(Sk[mx]+k)%Mod;Sk[sz+1]=(Sk[sz+1]-k+Mod)%Mod;
    Sb[mx]=(Sb[mx]+b)%Mod;Sb[sz+1]=(Sb[sz+1]-b+Mod)%Mod;
    b=1ll*Seq[p]%Mod*mn%Mod;
    Sb[mn]=(Sb[mn]+b)%Mod;Sb[mx]=(Sb[mx]-b+Mod)%Mod;
    k=Seq[p]%Mod;
    Sk[1]=(Sk[1]+k)%Mod;Sk[mn]=(Sk[mn]-k+Mod)%Mod;
    //for (int i=1,s1=0,s2=0;i<=n;i++) s1=(s1+Sk[i])%Mod,s2=(s2+Sb[i]%Mod),cout<<(1ll*i*s1%Mod+s2)%Mod<<" ";cout<<endl;
    if (l<p) Divide(l,p-1);if (p<r) Divide(p+1,r);
    return;
}