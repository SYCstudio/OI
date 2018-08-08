#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n;
int A[maxN],B[maxN];

int GetAns();

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]);
	for (int i=1;i<=n;i++) scanf("%d",&B[i]);

	sort(&A[1],&A[n+1]);sort(&B[1],&B[n+1]);

	printf("%d ",GetAns());
	swap(A,B);
	printf("%d\n",2*n-GetAns());

	return 0;
}

int GetAns(){
	int get=0;
	int p1=1,p2=n,p3=1,p4=n;
	while ((p1<=p2)&&(p3<=p4)){
		if (A[p1]>B[p3]) p1++,p3++,get+=2;
		else if (A[p2]>B[p4]) p2--,p4--,get+=2;
		else get+=A[p1]==B[p4],p1++,p4--;
	}
	return get;
}
