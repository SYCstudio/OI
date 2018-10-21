#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int maxN=110;

int main(){
	ll n,m,K,Ans=0;
	cin>>n>>m>>K;
	ll x=n,y=m;
	for (int i=1;i<=K;i++){
		Ans=Ans+2*(n+m)-4;
		n-=4;m-=4;
		if ((n<0)||(m<0)) break;
	}
	cout<<Ans<<endl;
	return 0;
}
