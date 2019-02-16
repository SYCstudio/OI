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
int A[maxN],BIT[maxN];

void Plus(int pos,int key);
int Kth(int k);
void Max(int pos,int key);
int GetMax(int pos);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]),++A[i],Plus(i,1);
	for (int i=n;i>=1;i--) Plus(A[i]=Kth(A[i]),-1);
	int Ans=0;
	for (int i=1;i<=n;i++){
		int d=GetMax(A[i]-1)+1;Ans=max(Ans,d);
		Max(A[i],d);printf("%d\n",Ans);
	}
	return 0;
}

void Plus(int pos,int key){
	while (pos<=n){
		BIT[pos]+=key;pos+=(pos)&(-pos);
	}
	return;
}

int Kth(int k){
	int sum=0,pos=0;
	for (int i=20;i>=0;i--){
		pos+=(1<<i);
		if ((pos>n)||(sum+BIT[pos]>=k)) pos-=(1<<i);
		else sum+=BIT[pos];
	}
	return pos+1;
}

void Max(int pos,int key){
	while (pos<=n){
		BIT[pos]=max(BIT[pos],key);pos+=(pos)&(-pos);
	}
	return;
}

int GetMax(int pos){
	int ret=0;
	while (pos){
		ret=max(ret,BIT[pos]);pos-=(pos)&(-pos);
	}
	return ret;
}
