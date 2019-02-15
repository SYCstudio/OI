#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1101;
const int inf=2147483647;

int n;
int Sum[maxN],Id[maxN];

bool cmp(int A,int B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int k1,k2,k3,k4;scanf("%d%d%d%d",&k1,&k2,&k3,&k4);
		Sum[i]=k1+k2+k3+k4;Id[i]=i;
	}
	sort(&Id[1],&Id[n+1],cmp);

	for (int i=1;i<=n;i++)
		if (Id[i]==1){
			printf("%d\n",i);break;
		}

	return 0;
}

bool cmp(int A,int B){
	if (Sum[A]==Sum[B]) return A<B;
	return Sum[A]>Sum[B];
}
