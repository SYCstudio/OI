#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const int inf=2147473647;

class Range
{
public:
	int l,r,opt;
};

int n,m,K;
Range Rg[maxN];
int numcnt=0,Num[maxN];

int main(){
	scanf("%d%d%d",&n,&K,&m);
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&Rg[i].l,&Rg[i].r,&Rg[i].opt);
	}
}
