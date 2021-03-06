#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=6;
const int maxNum=10100000;
const int inf=2147483647;

int Mod;
int pcnt,P[maxN],Pk[maxN];
int Seq[maxN],Rc[maxN][maxNum],FFF[maxN][maxNum];

int GetInv(int key,int P);
void Exgcd(int a,int b,int &x,int &y);
int GetC(int n,int m);
int QPow(int x,int cnt,int p);
int C(int n,int m,int id);
int GetFac(int n,int id);

int main(){
    int TTT;scanf("%d%d",&TTT,&Mod);
    for (int i=2,p=Mod;i<=p;i++)
        if (p%i==0){
            ++pcnt;P[pcnt]=i;Pk[pcnt]=1;
            while (p%i==0) Pk[pcnt]*=i,p/=i;
        }
    for (int i=1;i<=pcnt;i++){
        FFF[i][0]=1;for (int j=1;j<Pk[i];j++) FFF[i][j]=1ll*FFF[i][j-1]*((j%P[i])?(j):(1))%Pk[i];
        //cout<<P[i]<<" "<<Pk[i]<<endl;
        //for (int j=1;j<=20;j++) cout<<FFF[i][j]<<" ";cout<<endl;
    }

    while (TTT--){
        int n,n1,n2,m;scanf("%d%d%d%d",&n,&n1,&n2,&m);
        for (int i=0;i<n1;i++) scanf("%d",&Seq[i]);
        for (int i=1;i<=n2;i++){
            int key;scanf("%d",&key);
            m=m-key+1;
        }
        int Ans=0;
        for (int S=0;S<(1<<n1);S++){
            int sum=m,opt=1;
            for (int i=0;i<n1;i++) if (S&(1<<i)) sum=sum-Seq[i],opt*=-1;
            Ans=(Ans+GetC(sum-1,n-1)*opt+Mod)%Mod;
        }
        printf("%d\n",Ans);
    }
    return 0;
}

int GetInv(int key,int P){
    int x,y;
    Exgcd(key,P,x,y);
    x=(x%P+P)%P;
    return x;
}

void Exgcd(int a,int b,int &x,int &y){
    if (b==0){
        x=1;y=0;return;
    }
    Exgcd(b,a%b,x,y);
    int k=x;x=y;y=k-a/b*y;
    return;
}

int QPow(int x,int cnt,int p){
    int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%p;
        x=1ll*x*x%p;cnt>>=1;
    }
    return ret;
}

int GetC(int n,int m){
    if ((n<m)||(n<0)||(m<0)) return 0;
    int X=Mod,ret=0;
    for (int i=1;i<=pcnt;i++){
            int c=C(n,m,i);
            ret=(ret+1ll*c*GetInv(Mod/Pk[i],Pk[i])%Mod*(Mod/Pk[i])%Mod)%Mod;
        }
    return ret;
}

int C(int n,int m,int id){
    int a=GetFac(n,id),b=GetFac(m,id),c=GetFac(n-m,id);
    int pcnt=0,p=P[id],pk=Pk[id];
    for (int i=n;i;i/=p) pcnt+=i/p;
    for (int i=m;i;i/=p) pcnt-=i/p;
    for (int i=n-m;i;i/=p) pcnt-=i/p;
    return 1ll*QPow(p,pcnt,pk)*a%pk*GetInv(b,pk)%pk*GetInv(c,pk)%pk;
}

int GetFac(int n,int id){
    if (n==0) return 1;
    if ((n<maxNum)&&(Rc[id][n])) return Rc[id][n];
    int ret=1,p=P[id],pk=Pk[id];
    //for (int i=1;i<=pk;i++) if (i%p) ret=1ll*ret*i%pk;
    ret=FFF[id][pk-1];
    ret=QPow(ret,n/pk,pk);
    //for (int i=1;i<=n%pk;i++) if (i%p) ret=1ll*ret*i%pk;
    ret=1ll*ret*FFF[id][n%pk]%pk;
    int ans=1ll*ret*GetFac(n/p,id)%pk;
    if (n<maxNum) Rc[id][n]=ans;
    return ans;
}
