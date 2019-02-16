#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstdlib>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

map<int,int> M;

int QPow(int x,int cnt,int P);

int main(){
	int g,P;scanf("%d%d",&g,&P);
	int m=ceil(sqrt(P));

	int bs=QPow(g,m,P),now=1;
	
	for (int i=1;i<=m;i++){
		now=1ll*now*bs%P;
		M[now]=i;
	}

	int T;scanf("%d",&T);
	while (T--){
		int A,B;scanf("%d%d",&A,&B);
		int a,b;
		int now=A;
		for (int i=0;i<=m;i++){
			if (M.count(now)){
				a=M[now]*m-i;break;
			}
			now=1ll*now*g%P;
		}
		now=B;
		for (int i=0;i<=m;i++){
			if (M.count(now)){
				b=M[now]*m-i;break;
			}
			now=1ll*now*g%P;
		}

		//cout<<"a b:"<<a<<" "<<b<<endl;

		printf("%d\n",QPow(g,1ll*a*b%(P-1),P));
	}

	return 0;
}

int QPow(int x,int cnt,int P){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%P;
		x=1ll*x*x%P;cnt>>=1;
	}
	return ret;
}
