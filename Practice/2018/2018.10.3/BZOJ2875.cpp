#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

ll P;
ll M1[2][2],M2[2][2],Bp[2][2];

void Mul1();
void Mul2();
ll Mul(ll x,ll y);

int main(){
	ll a,c,x,n,g;
	scanf("%lld%lld%lld%lld%lld%lld",&P,&a,&c,&x,&n,&g);
	M1[0][0]=x;M1[0][1]=c;M1[1][0]=M1[1][1]=0;
	M2[0][0]=a;M2[0][1]=0;M2[1][0]=1;M2[1][1]=1;
	while (n){
		if (n&1) Mul1();
		Mul2();n>>=1;
	}
	//*/
	printf("%lld\n",M1[0][0]%g);return 0;
}

void Mul1(){
	for (int i=0;i<2;i++) for (int j=0;j<2;j++) Bp[i][j]=M1[i][j],M1[i][j]=0;
	for (int k=0;k<2;k++)
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				M1[i][j]=(M1[i][j]+Mul(Bp[i][k],M2[k][j])%P)%P;
	return;
}

void Mul2(){
	for (int i=0;i<2;i++) for (int j=0;j<2;j++) Bp[i][j]=M2[i][j],M2[i][j]=0;
	for (int k=0;k<2;k++)
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				M2[i][j]=(M2[i][j]+Mul(Bp[i][k],Bp[k][j])%P)%P;
	return;
}

ll Mul(ll x,ll y){
	x=(x%P+P)%P;y=(y%P+P)%P;
	return (x*y-(ll)((ld)x/P*y+0.5)*P+P)%P;
}
