#include<iostream>
#include<cstdio>
#include<cstdilb>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=31;
const int maxK=8;
const int inf=2147483647;

int n,m,K;
int F[maxN][maxN][1<<maxK];

void Plus(int &x,int y);

int main(){
	scanf("%d%d%d",&n,&m,&K);K=min(K,n);
	F[K][0][0]=1;
	for (int i=0;i<m;i++)
		for (int j=0;j<(1<<K);j++)
}
