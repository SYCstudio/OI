#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const int inf=2147483647;

class People
{
public:
	int a,b;
};

int n,H;
int F[maxN],Sum[maxN];
People P[maxN];

bool cmp(People A,People B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&P[i].a,&P[i].b);
	scanf("%d",&H);
	sort(&P[1],&P[n+1],cmp);
	for (int i=n;i>=1;i--) Sum[i]=Sum[i+1]+P[i].a;
	mem(F,-1);F[0]=0;
	for (int i=1;i<=n;i++)
		for (int j=i-1;j>=0;j--)
			if (F[j]!=-1){
				if (F[j]+Sum[i]+P[i].b>=H) F[j+1]=max(F[j+1],F[j]);
				F[j]=F[j]+P[i].a;
			}
	int Ans=0;
	for (int i=1;i<=n;i++) if (F[i]!=-1) Ans=i;
	printf("%d\n",Ans);return 0;
}

bool cmp(People A,People B){
	return A.a+A.b<B.a+B.b;
}
