#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=16;
const ld eps=1e-8;
const int inf=2147483647;

int n;
ll Tim[maxN],Good[maxN],Val[maxN];
int top=0,St[maxN],Id[maxN];

bool Check();
ll calc(ll speed,ll tim,ll limit);
bool cmp(int A,int B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld%lld%lld",&Tim[i],&Good[i],&Val[i]);
	for (int i=1;i<=n;i++) Id[i]=i;
	sort(&Id[1],&Id[n+1],cmp);

	ll Ans=0;
	for (int S=0;S<(1<<n);S++){
		ll sum=0;top=0;
		for (int i=0;i<n;i++) if (S&(1<<i)) St[++top]=Id[i+1],sum=sum+Val[Id[i+1]];
		if (Check()) Ans=max(Ans,sum);
	}

	printf("%lld\n",Ans);

	return 0;
}

bool Check(){
	//cout<<"Check ["<<top<<"] :";
	//for (int i=1;i<=top;i++) cout<<St[i]<<" ";cout<<endl;
	ll nowsum=0,speed=1;
	for (int i=1;i<=top;i++){
		//cout<<i<<" "<<nowsum<<" "<<speed<<endl;
		ll sum=0,tim=Tim[St[i]]-Tim[St[i-1]];
		for (int j=i;j<=top;j++){
			sum=sum+Good[St[j]];
			if (sum>nowsum)
				tim=min(tim,calc(speed,Tim[St[j]]-Tim[St[i-1]],sum-nowsum));
		}
		if (tim<0) return 0;
		speed=speed+tim;
		nowsum=nowsum+(Tim[St[i]]-Tim[St[i-1]]-tim)*speed-Good[St[i]];
		//cout<<Tim[St[i]]<<"-"<<Tim[St[i-1]]<<" "<<tim<<" "<<speed<<" "<<sum<<endl;
	}
	return 1;
}

ll calc(ll speed,ll tim,ll limit){
	ll a=1,b=(speed-tim),c=limit-speed*tim;
	ll delta=b*b-4ll*a*c;if (delta<0) return -1;
	//cout<<"calc:"<<a<<" "<<b<<" "<<c<<" -> "<<(ll)(floor((-(ld)b+sqrt(delta))/(ld)(2.0*a)+eps))<<endl;
	return (ll)(floor((-(ld)b+sqrt(delta)+eps)/(ld)(2.0*a)+eps));
}

bool cmp(int A,int B){
	return Tim[A]<Tim[B];
}
