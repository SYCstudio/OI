#include<bits/stdc++.h>
using namespace std;

#define ll __int128
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) (1ll*(x)*(x))

const int maxN=201000;
const int inf=2147483647;
const ll INF=1e18;

int n,X;
ll F[maxN],D[maxN];

void Print(ll x,int opt);

int main(){
	cin>>n>>X;
	for (int i=1;i<=n;i++) cin>>D[i];
	F[0]=0;
	for (int i=1;i<=n;i++){
		ll key=X+X+D[i];F[i]=F[i-1]+key+D[i]*sqr(2);
		for (int j=i-1;j>=1;j--){
			key=key+X+(D[j+1]-D[j])*sqr(1+(i-j));
			F[i]=min(F[i],F[j-1]+key+D[j]*sqr(2+(i-j)));
		}
	}

	//for (int i=1;i<=n;i++) cout<<F[i]<<endl;

	Print(F[n],0);
	return 0;
}

