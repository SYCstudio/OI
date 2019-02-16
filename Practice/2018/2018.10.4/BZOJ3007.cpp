#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=3010;
const int maxM=maxN*maxN;
const ld eps=1e-8;
const int inf=2147483647;

class Edge
{
public:
	int u,v;ld d;
};

int n,R,C,ecnt;
ll X[maxN],Y[maxN];
Edge E[maxM];
int UFS[maxN];

bool cmp(Edge A,Edge B);
int Find(int x);

int main(){
	scanf("%d%d%d",&n,&R,&C);
	for (int i=1;i<=n+2;i++) UFS[i]=i;
	for (int i=1;i<=n;i++){
		scanf("%lld%lld",&X[i],&Y[i]);
		if ((X[i]==1)||(Y[i]==C)) UFS[Find(n+1)]=Find(i);
		else E[++ecnt]=((Edge){n+1,i,min(X[i]-1,C-Y[i])});
		if ((Y[i]==1)||(X[i]==R)) UFS[Find(n+2)]=Find(i);
		else E[++ecnt]=((Edge){n+2,i,min(Y[i]-1,R-X[i])});
	}
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			E[++ecnt]=((Edge){i,j,(ld)0.5*sqrt((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j]))});
	sort(&E[1],&E[ecnt+1],cmp);
	for (int i=1;i<=ecnt;i++){
		if (Find(E[i].u)!=Find(E[i].v)){
			UFS[Find(E[i].u)]=Find(E[i].v);
			if (Find(n+1)==Find(n+2)){
				printf("%.2lf\n",E[i].d);
				return 0;
			}
		}
	}
	return 0;
}

bool cmp(Edge A,Edge B){
	return A.d<B.d;
}

int Find(int x){
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
