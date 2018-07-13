#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-x))

const int maxMat=7;
const int maxN=5000001;
const int Mod=1e9+7;
const int inf=2147483647;

int n,K;
int Seq[maxN];
int A[maxMat][maxMat],B[maxMat][maxMat],Bp[maxMat][maxMat];
ll BIT[2][maxN];

void Upd(int &x,int y);
int QPow(int x,int cnt);
void Init();
void Mul1();
void Mul2();
void Add(int opt,int pos,ll key);
ll Sum(int opt,int pos);

int main()
{
    scanf("%d%d",&n,&K);
    for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
    
    Init();
    int invn=QPow(n-2,Mod-2),inv2=QPow(2,Mod-2);

    int Ans=0;
    ll sum1=0,sum2=0;
    for (int i=1;i<=n;i++)
    {
		ll t=Sum(1,Seq[i]);
        ll a=Sum(0,Seq[i]),pa=t-a,sa=1ll*n*a-t-a;
        ll b=i-1-a,pb=sum1-pa,sb=sum2-sa;
        Upd(Ans,1ll*b*A[0][0]%Mod);
        Upd(Ans,1ll*(sb+pa)%Mod*A[0][1]%Mod*invn%Mod);
        Upd(Ans,1ll*a*A[0][2]%Mod);
        Upd(Ans,1ll*(1ll*(n-i)*b%Mod+1ll*(i-2)*a%Mod)%Mod*A[0][3]%Mod*invn%Mod);
        Upd(Ans,1ll*(sa+pb)%Mod*A[0][4]%Mod*invn%Mod);
        Upd(Ans,1ll*(1ll*(n-i)*a%Mod+1ll*(i-2)*b%Mod)%Mod*A[0][5]%Mod*invn%Mod);
        sum1+=1ll*(i-1);sum2+=1ll*(n-i-1);
        Add(0,Seq[i],1);Add(1,Seq[i],i);
    }

    Upd(Ans,1ll*n*(n-1)%Mod*inv2%Mod*inv2%Mod*A[0][6]%Mod);

    printf("%d\n",Ans);
    return 0;
}

void Upd(int &x,int y){
    x+=y;x%=Mod;x+=Mod;x%=Mod;
    return;
}

int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%Mod;
        x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}

void Init()
{
    for (int i=0;i<maxMat;i++) A[i][i]=1;
    int inv2=QPow(2,Mod-2),C=1ll*(n-2)*(n-3)%Mod*inv2%Mod;
    int R[maxMat][maxMat]={{C,  n-2, 1,    0,    0,  n-2,  0},
                           {1,C+n-3, 0,    1,    1,    0,n-3},
                           {1,    0, C,  n-2,  n-2,    0,  0},
                           {0,    1, 1,C+n-3,    0,    1,n-3},
                           {0,    1, 1,    0,C+n-3,    1,n-3},
                           {1,    0, 0,    1,    1,C+n-3,n-3},
                           {0,    1, 0,    1,    1,    1,C+2*(n-4)+1}};
    for (int i=0;i<maxMat;i++) for (int j=0;j<maxMat;j++) Upd(B[i][j],R[i][j]);

    while (K){
        if (K&1) Mul1();
        Mul2();K>>=1;
    }
    return;
}

void Mul1()
{
    for (int i=0;i<maxMat;i++) for (int j=0;j<maxMat;j++) Bp[i][j]=A[i][j],A[i][j]=0;
    for (int k=0;k<maxMat;k++)
        for (int i=0;i<maxMat;i++)
            for (int j=0;j<maxMat;j++)
                Upd(A[i][j],1ll*Bp[i][k]*B[k][j]%Mod);
    return;
}

void Mul2()
{
    for (int i=0;i<maxMat;i++) for (int j=0;j<maxMat;j++) Bp[i][j]=B[i][j],B[i][j]=0;
    for (int k=0;k<maxMat;k++)
        for (int i=0;i<maxMat;i++)
            for (int j=0;j<maxMat;j++)
                Upd(B[i][j],1ll*Bp[i][k]*Bp[k][j]%Mod);
    return;
}

void Add(int opt,int pos,ll key){
    while (pos<=n){
        BIT[opt][pos]+=key;pos+=lowbit(pos);
    }
    return;
}

ll Sum(int opt,int pos){
    ll ret=0;
    while (pos){
        ret+=BIT[opt][pos];pos-=lowbit(pos);
    }
    return ret;
}
