#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;

#define Lint long long

const int Mod=1000000007;
const int maxsize=1000005;

Lint n,m;
Lint F[maxsize];//递推错排
Lint Fac[maxsize];//阶乘
Lint Inv[maxsize];//逆元

inline Lint Pow(Lint a,Lint b);
inline Lint C(Lint a,Lint b);

int main()
{
    int T;
    //预处理
    //递推错排
    F[0]=1;
    F[1]=0;
    F[2]=1;
    for (int i=3;i<=maxsize;i++)
        F[i]=(F[i-1]+F[i-2])*(i-1)%Mod;

    //计算阶乘
    Fac[0]=1;
    for (int i=1;i<=maxsize;i++)
        Fac[i]=Fac[i-1]*i%Mod;

    //计算逆元
    Inv[maxsize]=Pow(Fac[maxsize],Mod-2);
    Inv[0]=1;
    for (int i=maxsize-1;i;i--)
        Inv[i]=Inv[i+1]*(i+1)%Mod;

    //main
    //for (int i=1;i<=10000;i++)
    //    cout<<Inv[i]<<" ";
    cout<<endl;
    cin>>T;
    while (T--)
    {
        cin>>n>>m;
        //cout<<"------"<<Fac[n-m]<<" "<<C((Lint)n,(Lint)m)<<endl;
        cout<<F[n-m]*C((Lint)n,(Lint)m)%Mod<<endl;
    }
}

inline Lint Pow(Lint a,Lint b)
{
    Lint base=a;
    Lint res=1;
    while (b)
    {
        if (b&1)
            res=res*base%Mod;
        base=base*base%Mod;
        b=b>>1;
    }
    return res;
}

inline Lint C(Lint a,Lint b)
{
    return Fac[a]*Inv[b]%Mod*Inv[a-b]%Mod;
}
