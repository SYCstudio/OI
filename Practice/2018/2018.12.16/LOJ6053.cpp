#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=505000;
const int Mod=1e9+7;
const int inv2=500000004;
const int inf=2147483647;

ll n,srt;
bool notprime[maxN];
int pcnt,P[maxN],SumP[maxN];
ll G[maxN],H[maxN],num,Num[maxN],Id[maxN+maxN];

void Init();
int GetId(ll x);
ll S(ll n,int p);

int main(){
	Init();scanf("%lld",&n);srt=sqrt(n);
	for (ll i=1,j;i<=n;i=j+1){
		j=n/i;Num[++num]=j;H[num]=(j-1)%Mod;G[num]=(1ll*j%Mod*((j+1)%Mod)%Mod*inv2%Mod-1+Mod)%Mod;
		if (j<=srt) Id[j]=num;
		else Id[i+maxN]=num;
		j=n/j;
	}
	for (int j=1;j<=pcnt;j++)
		for (int i=1;(i<=num)&&(1ll*P[j]*P[j]<=Num[i]);i++){
			G[i]=(G[i]-1ll*(G[GetId(Num[i]/P[j])]-SumP[j-1]+Mod)%Mod*P[j]%Mod+Mod)%Mod;
			H[i]=((H[i]-H[GetId(Num[i]/P[j])]+j-1)%Mod+Mod)%Mod;
		}
	//for (int i=1;i<=100;i++) cout<<P[i]<<" ";cout<<endl;
	//for (int i=1;i<=num;i++) cout<<Num[i]<<" ";cout<<endl;
	//for (int i=1;i<=num;i++) cout<<G[i]<<" ";cout<<endl;
	//for (int i=1;i<=num;i++) cout<<H[i]<<" ";cout<<endl;
	printf("%lld\n",(S(n,1)+1)%Mod);return 0;
}

void Init(){
	notprime[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) P[++pcnt]=i,SumP[pcnt]=(SumP[pcnt-1]+i)%Mod;
		for (int j=1;(j<=pcnt)&&(1ll*i*P[j]<maxN);j++){
			notprime[i*P[j]]=1;if (i%P[j]==0) break;
		}
	}
	return;
}

int GetId(ll x){
	if (x<=srt) return Id[x];
	return Id[n/x+maxN];
}

ll S(ll m,int p){
	if ((m<=1)||(P[p]>m)) return 0;
	int id=GetId(m);ll ret=(((G[id]-SumP[p-1])-(H[id]-(p-1)))%Mod+Mod)%Mod;
	if (p==1) ret=ret+2;
	//cout<<"Calc:"<<m<<" "<<p<<" "<<ret<<endl;
	for (int i=p;(i<=pcnt)&&(1ll*P[i]*P[i]<=m);i++){
		ll x=P[i];
		for (int e=1;x*P[i]<=m;e++,x*=P[i])
			ret=((ret+1ll*S(m/x,i+1)*(P[i]^e)%Mod)%Mod+((P[i])^(e+1))%Mod)%Mod;
	}
	return ret;
}
