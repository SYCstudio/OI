#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int inf=2147483647;

int n;
ull X,Sum[maxN];

int main(){
	cin>>n>>X;
	for (int i=1;i<=n;i++){
		cin>>Sum[i];
		Sum[i]+=Sum[i-1];
	}

	ull Ans=Sum[n]*5+n*X;

	for (int K=1;K<n;K++){
		ull nowans=K*X;
		if (K*2>=n) nowans=nowans+5*Sum[n];
		else{
			nowans=nowans+5*(Sum[n]-Sum[n-2*K]);
			int lst=n-2*K;
			ull cost=7;
			while (lst>=K){
				nowans=nowans+cost*(Sum[lst]-Sum[lst-K]);
				cost+=2;lst-=K;
			}
			nowans=nowans+cost*Sum[lst];
		}
		Ans=min(Ans,nowans);
	}

	cout<<Ans+X*n<<endl;
	return 0;
}
