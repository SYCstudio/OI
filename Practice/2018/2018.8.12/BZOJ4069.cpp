#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNN=2010;
const int maxBit=60;
const int inf=2147483647;

int n,A,B;
ll Y[maxNN];

namespace cpp1
{
	const int maxN=101;

	bool F[maxN][maxN];
	
	void main();
}

namespace cpp2
{
	const int maxN=2010;

	int F[maxN];

	void main();
}

int main(){
	scanf("%d%d%d",&n,&A,&B);
	for (int i=1;i<=n;i++) scanf("%lld",&Y[i]);
	for (int i=1;i<=n;i++) Y[i]=Y[i]+Y[i-1];

	if (n<=100) cpp1::main();
	else cpp2::main();

	return 0;
}

namespace cpp1
{
	void main(){
		ll key=0;
		for (int b=maxBit;b>=0;b--){
			mem(F,0);ll bit=((1ll<<(maxBit+1))-1)-((1ll<<b)-1);
			F[0][0]=1;
			for (int i=1;i<=n;i++)
				for (int j=1;j<=min(i,B);j++)
					for (int k=0;k<i;k++){
						ll sum=Y[i]-Y[k];
						if ( ((sum&(1ll<<b))==0) && (((sum&bit)|key)==key) )
							F[i][j]|=F[k][j-1];
					}
			bool flag=0;
			for (int i=A;i<=B;i++) flag|=F[n][i];
			if (flag==0) key|=(1ll<<b);
		}
		
		printf("%lld\n",key);
		return;
	}
}

namespace cpp2
{
	void main(){
		ll key=0;
		for (int b=maxBit;b>=0;b--){
			mem(F,127);ll bit=((1ll<<(maxBit+1))-1)-((1ll<<b)-1);
			F[0]=0;
			for (int i=1;i<=n;i++)
				for (int j=0;j<i;j++){
					ll sum=Y[i]-Y[j];
					if ( ((sum&(1ll<<b))==0) && (((sum&bit)|key)==key) )
						F[i]=min(F[i],F[j]+1);
				}
			if (F[n]>B) key|=(1ll<<b);
		}
		printf("%lld\n",key);
		return;
	}
}
