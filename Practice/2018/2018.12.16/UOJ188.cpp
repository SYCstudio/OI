#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=705000;
const int inf=2147483647;

ll n,srt;
bool notprime[maxN];
int pcnt,P[maxN];
ll num,Num[maxN+maxN],Id[maxN+maxN];
ll G[maxN+maxN];

void Init();
ll Calc(ll x);
int GetId(ll x);
pair<ll,ll> S(ll x,int p);

int main(){
	Init();ll L,R;scanf("%lld%lld",&L,&R);
	printf("%lld\n",Calc(R)-Calc(L-1));
	return 0;
}

void Init(){
	notprime[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) P[++pcnt]=i;
		for (int j=1;(j<=pcnt)&&(1ll*i*P[j]<maxN);j++){
			notprime[i*P[j]]=1;if (i%P[j]==0) break;
		}
	}
	return;
}

ll Calc(ll x){
	num=0;n=x;srt=sqrt(x);
	for (ll i=1,j;i<=n;i=j+1){
		j=x/i;Num[++num]=j;G[num]=j-1;
		if (j<=srt) Id[j]=num;
		else Id[i+maxN]=num;j=n/j;
	}
	for (int j=1;j<=pcnt;j++)
		for (int i=1;(i<=num)&&(1ll*P[j]*P[j]<=Num[i]);i++)
			G[i]=G[i]-G[GetId(Num[i]/P[j])]+j-1;
	//for (int i=1;i<=num;i++) cout<<Num[i]<<" ";cout<<endl;
	//for (int i=1;i<=num;i++) cout<<G[i]<<" ";cout<<endl;
	return S(x,1).second;
}

int GetId(ll x){
	if (x<=srt) return Id[x];
	return Id[n/x+maxN];
}

pair<ll,ll> S(ll x,int p){
	if ((x<=1)||(x<P[p])) return make_pair(0,0);
	ll r1=G[GetId(x)]-(p-1),r2=0;
	for (int i=p;(i<=pcnt)&&(1ll*P[i]*P[i]<=x);i++){
		ll mul=P[i];
		for (int j=1;1ll*mul*P[i]<=x;j++,mul=mul*P[i]){
			pair<ll,ll> R=S(x/mul,i+1);
			r2=r2+R.first*P[i]+R.second+P[i];
		}
	}
	return make_pair(r1,r2);
}
