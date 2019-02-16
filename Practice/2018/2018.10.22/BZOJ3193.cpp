#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int Mod=2011;
const int inf=2147483647;

class Mountain
{
public:
	int h,k;
};

int n;
int C[maxN][maxN];
Mountain H[maxN];
int F[maxN],G[maxN][maxN],S[maxN][maxN];

bool cmp(Mountain A,Mountain B);
void Solve1();
void Solve2();
void Plus(int &x,int y);

int main(){
	for (int i=0;i<maxN;i++)
		for (int j=C[i][0]=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&H[i].h,&H[i].k);
	sort(&H[1],&H[n+1],cmp);
	//cout<<endl;for (int i=1;i<=n;i++) cout<<H[i].h<<" "<<H[i].k<<endl;
	for (int i=1;i<=n;i++)
		if (H[i].k>i) H[i].k=i;
	H[1].k=1;

	Solve1();Solve2();
	return 0;
}

bool cmp(Mountain A,Mountain B){
	if (A.h!=B.h) return A.h>B.h;
	return A.k<B.k;
}

void Solve1(){
	int Ans=1;
	for (int i=1,cnt=0;i<=n;i++){
		if ((i!=1)&&(H[i].h==H[i-1].h)) cnt++;
		else cnt=0;
		//cout<<i<<":"<<C[min(H[i].k+cnt,i)][1]<<" "<<cnt<<endl;
		Ans=1ll*Ans*C[min(H[i].k+cnt,i)][1]%Mod;
	}
	printf("%d ",Ans);return;
}

void Solve2(){
	G[1][1]=1;
	for (int i=1;i<=n;i++) S[1][i]=1;
	for (int i=2,cnt=0;i<=n;i++){
		if (H[i].h==H[i-1].h){
			cnt++;
			for (int j=1;j<=min(H[i].k+cnt,i);j++)
				Plus(G[i][j],S[i-1][j-1]);
		}
		else{
			cnt=0;
			for (int j=1;j<=H[i].k;j++)
				Plus(G[i][j],S[i-1][n]);
		}	
		for (int j=1;j<=n;j++) S[i][j]=(S[i][j-1]+G[i][j])%Mod;
	}
	printf("%d\n",S[n][n]);return;
}

void Plus(int &x,int y){
	x=(x+y)%Mod;return;
}
