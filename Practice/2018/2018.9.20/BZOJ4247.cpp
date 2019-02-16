#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2020;
const int inf=2147483647;
const ll INF=1e18;

class Data{
public:
	int c,w;
};

int n;
Data D[maxN];
ll F[maxN][maxN];

bool cmp(Data A,Data B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&D[i].c,&D[i].w),D[i].c--;
	sort(&D[1],&D[n+1],cmp);
	for (int i=0;i<maxN;i++) for (int j=0;j<maxN;j++) F[i][j]=-INF;
	F[0][1]=0;
	for (int i=1;i<=n;i++)
		for (int j=0;j<=n;j++)
			F[i][j]=max(F[i-1][j],F[i-1][max(1,j-D[i].c)]+D[i].w);
	ll Ans=0;
	for (int j=0;j<=n;j++) Ans=max(Ans,F[n][j]);
	printf("%lld\n",Ans);return 0;
}


bool cmp(Data A,Data B){
	return A.c>B.c;
}
