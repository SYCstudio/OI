#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50000;
const int Pri[4]={2,3,4679,35617};
const int Mod=999911659;
const int Phi=Mod-1;
const int inf=2147483647;

ll Fac[4][maxN],FInv[4][maxN];

ll QPow(ll x,ll cnt,ll P);
ll Lucas(ll n,ll m);
void Exgcd(ll a,ll b,ll &x,ll &y);
ll Inv(ll a,ll P);
ll GetC(ll n,ll m,ll id);

int main(){
	for (int i=0;i<4;i++){
		Fac[i][0]=FInv[i][0]=1;
		for (int j=1;j<Pri[i];j++) Fac[i][j]=Fac[i][j-1]*j%Pri[i];
		FInv[i][Pri[i]-1]=Inv(Fac[i][Pri[i]-1],Pri[i]);
		//cout<<Pri[i]<<" "<<Fac[i][Pri[i]-1]<<" "<<FInv[i][Pri[i]-1]<<endl;
		for (int j=Pri[i]-2;j>=1;j--) FInv[i][j]=FInv[i][j+1]*(j+1)%Pri[i];
		//cout<<FInv[i][1]<<" "<<FInv[i][2]<<endl;
	}
	
    ll n,G;
    scanf("%lld%lld",&n,&G);
	if (G%Mod==0){
		printf("0\n");return 0;
	}
	
    ll Ans=0;
    for (ll i=1;i*i<=n;i++)
        if (n%i==0){
            Ans=(Ans+Lucas(n,n/i))%Phi;
            if (i*i!=n) Ans=(Ans+Lucas(n,i))%Phi;
        }
    printf("%lld\n",QPow(G,Ans,Mod));

    return 0;
}

ll QPow(ll x,ll cnt,ll P){
    ll ret=1;
    while (cnt){
        if (cnt&1) ret=ret*x%P;
        x=x*x%P;cnt>>=1;
    }
    return ret;
}

ll Lucas(ll n,ll m){
    ll Ret=0;
    if (n<m) return 0;
	for (int i=0;i<4;i++){
		//cout<<"C:"<<n<<" "<<m<<" "<<GetC(n,m,i)<<endl;
		ll rt=GetC(n,m,i);
		Ret=(Ret+rt*(Phi/Pri[i])%Phi*Inv(Phi/Pri[i],Pri[i])%Phi)%Phi;
	}
    return Ret;
}

void Exgcd(ll a,ll b,ll &x,ll &y){
    if (b==0){
        x=1;y=0;return;
    }
    Exgcd(b,a%b,x,y);
    ll t=x;x=y;y=t-a/b*y;return;
}

ll Inv(ll a,ll P){
    ll x,y;
    Exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}

ll GetC(ll n,ll m,ll id){
    if (n<m) return 0;
	if (n<Pri[id]) return Fac[id][n]*FInv[id][m]%Pri[id]*FInv[id][n-m]%Pri[id];
	return GetC(n%Pri[id],m%Pri[id],id)*GetC(n/Pri[id],m/Pri[id],id)%Pri[id];
}
