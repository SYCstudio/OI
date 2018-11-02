#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=707000;
const int inf=2147483647;

int n;
int BIT[maxN];

void Plus(int pos,int key);
int GetK(int k);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) BIT[i]=i&(-i);
	int now=1;
	for (int i=n;i>=1;i--){
		int plus;scanf("%d",&plus);
		now=(now+plus-1)%i+1;
		int pos=GetK(now);Plus(pos,-1);
		printf("%d\n",pos);
	}
	return 0;
}

void Plus(int pos,int key){
	while (pos<=n){
		BIT[pos]+=key;pos+=pos&(-pos);
	}
	return;
}

int GetK(int k){
	int sum=0,ret=0;
	for (int i=20;i>=0;i--){
		ret=ret+(1<<i);
		if ((ret>n)||(sum+BIT[ret]>=k)) ret-=(1<<i);
		else sum+=BIT[ret];
	}
	return ret+1;
}
