#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int inf=2147483647;

class People
{
public:
	int a,b;
};

int n;
People P[maxN];
int F[maxN][maxN*maxN],Sum[maxN];

bool cmp(People A,People B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&P[i].a,&P[i].b);
	sort(&P[1],&P[n+1],cmp);
	for (int i=1;i<=n;i++) Sum[i]=Sum[i-1]+P[i].a;
	mem(F,63);
	F[0][0]=0;
	for (int i=1;i<=n;i++)
		for (int j=0;j<=Sum[i-1];j++){
			F[i][j+P[i].a]=min(F[i][j+P[i].a],max(F[i-1][j],j+P[i].a+P[i].b));
			F[i][j]=min(F[i][j],max(F[i-1][j],Sum[i-1]-j+P[i].a+P[i].b));
		}
	int Ans=inf;
	for (int i=0;i<=Sum[n];i++) Ans=min(Ans,max(i,F[n][i]));
	printf("%d\n",Ans);return 0;
}

bool cmp(People A,People B){
	if (A.b!=B.b) return A.b>B.b;
	else return A.a>B.a;
}
