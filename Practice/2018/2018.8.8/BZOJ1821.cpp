#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int inf=2147483647;

class Edge
{
public:
	int u,v;
	ld d;
};

int n,K;
int X[maxN],Y[maxN],UFS[maxN];
Edge E[maxN*maxN];

bool cmp(Edge A,Edge B);
int Find(int x);

int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d%d",&X[i],&Y[i]),UFS[i]=i;

	int ecnt=0;
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			E[++ecnt]=((Edge){i,j,sqrt(1ll*(X[i]-X[j])*(X[i]-X[j])+1ll*(Y[i]-Y[j])*(Y[i]-Y[j]))});

	sort(&E[1],&E[ecnt+1],cmp);

	int cnt=n;
	for (int i=1;i<=ecnt;i++)
		if (Find(E[i].u)!=Find(E[i].v)){
			cnt--;UFS[Find(E[i].u)]=Find(E[i].v);
			if (cnt==K) break;
		}

	ld d=inf;
	for (int i=1;i<=ecnt;i++)
		if (Find(E[i].u)!=Find(E[i].v)) d=min(d,E[i].d);

	printf("%.2LF\n",d);

	return 0;
}

bool cmp(Edge A,Edge B){
	return A.d<B.d;
}

int Find(int x){
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
