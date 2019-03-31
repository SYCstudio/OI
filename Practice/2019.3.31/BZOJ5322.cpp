#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=202000;
const int maxM=10500000;
const int Mod=998244353;

int Fc[maxM],Ifc[maxM];
int n,m,l,r;
int Sorter[maxN],Seq[maxN],num,Num[maxN],Cnt[maxN];

int Input();
int QPow(int x,int cnt);
int main(){
    Fc[0]=Ifc[0]=1;for (int i=1;i<maxM;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;

    int Case=Input();
    while (Case--){
        n=Input();m=Input();l=Input();r=Input();int rm=m;
        for (int i=1;i<=n;i++) Seq[i]=Input(),Num[i]=Seq[i];
        sort(&Num[1],&Num[n+1]);num=unique(&Num[1],&Num[n+1])-Num-1;
        for (int i=1;i<=n;i++) ++Cnt[lower_bound(&Num[1],&Num[num+1],Seq[i])-Num];
        int Ans=1,scnt=0,sz=r-l+1;
        for (int i=1;i<=num;i++)
            if (Num[i]>=l&&Num[i]<=r&&m) Sorter[++scnt]=Cnt[i],--sz;
            else Ans=1ll*Ans*Fc[Cnt[i]]%Mod;
        sort(&Sorter[1],&Sorter[scnt+1]);
        if (m){
            if (scnt==0||1ll*sz*Sorter[1]>=m){
                int v=m/sz,res=m%sz;Ans=1ll*Ans*QPow(Fc[v+1],res)%Mod*QPow(Fc[v],sz-res)%Mod;
                for (int i=1;i<=scnt;i++) Ans=1ll*Ans*Fc[Sorter[i]]%Mod;
            }
            else{
                m-=1ll*sz*Sorter[1];int lst=1;++sz;while (lst+1<=scnt&&Sorter[lst+1]==Sorter[lst]) ++lst,++sz;
                while (1){
                    if (lst==scnt){
                        int v=m/sz,res=m%sz;Ans=1ll*Ans*QPow(Fc[Sorter[scnt]+v+1],res)%Mod*QPow(Fc[Sorter[scnt]+v],sz-res)%Mod;
                        break;
                    }
                    int dw=Sorter[lst+1]-Sorter[lst];
                    if (1ll*sz*dw>=m){
                        int v=m/sz,res=m%sz;Ans=1ll*Ans*QPow(Fc[Sorter[lst]+v+1],res)%Mod*QPow(Fc[Sorter[lst]+v],sz-res)%Mod;
                        for (int i=lst+1;i<=scnt;i++) Ans=1ll*Ans*Fc[Sorter[i]]%Mod;
                        break;
                    }
                    m-=1ll*sz*dw;++lst;++sz;
                    while (lst+1<=scnt&&Sorter[lst+1]==Sorter[lst]) ++lst,++sz;
                }
            }
        }
        Ans=1ll*Ans*QPow(Fc[n+rm],Mod-2)%Mod;
        printf("%d\n",QPow(Ans,Mod-2));

        for (int i=1;i<=scnt;i++) Sorter[i]=0;
        for (int i=1;i<=num;i++) Cnt[i]=0,Num[i]=0;
    }
    return 0;
}
int Input(){
    char ch=getchar();int x=0;
    while (!isdigit(ch)) ch=getchar();
    while (isdigit(ch)) x=x*10+ch-48,ch=getchar();
    return x;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%Mod;
        cnt>>=1;x=1ll*x*x%Mod;
    }
    return ret;
}