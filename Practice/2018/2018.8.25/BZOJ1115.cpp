#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int inf=2147483647;

int Seq[maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int n;scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
		int sum=0;
		for (int i=n,opt=1;i>=1;i--,opt^=1) sum^=(opt*(Seq[i]-Seq[i-1]));
		if (sum==0) printf("NIE\n");
		else printf("TAK\n");
	}

	return 0;
}
