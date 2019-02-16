#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=92;
const int inf=2147483647;

ll n;
ll Fab[maxN];
int icnt=0,Id[maxN];
ll F[2][maxN];

int main(){
	Fab[1]=1;Fab[2]=2;
	for (int i=3;i<maxN;i++) Fab[i]=Fab[i-1]+Fab[i-2];
	scanf("%lld",&n);
	for (int i=maxN-1;i>=1;i--) if (n>=Fab[i]) n-=Fab[i],Id[++icnt]=i;
	reverse(&Id[1],&Id[icnt+1]);

	F[1][0]=1;
	for (int i=1;i<=icnt;i++){
		F[0][i]=(Id[i]-Id[i-1])/2*F[0][i-1]+(Id[i]-Id[i-1]-1)/2*F[1][i-1];
		F[1][i]=F[1][i-1]+F[0][i-1];
	}
	printf("%lld\n",F[0][icnt]+F[1][icnt]);return 0;
}
