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

int F;
int SG[maxN];
int vis[maxN];

int GetSG(int n);

int main(){
	int TTT;mem(SG,-1);
	scanf("%d%d",&TTT,&F);
	while (TTT--){
		int n,sum=0;scanf("%d",&n);
		while (n--){
			int key;scanf("%d",&key);
			sum^=GetSG(key);
		}
		if (sum==0) printf("0");
		else printf("1");

		if (TTT!=0) printf(" ");
	}
}

int GetSG(int n){
	if (SG[n]!=-1) return SG[n];
	if (n<F) return SG[n]=0;
	for (int i=2,last;i<=n;i=last+1){
		last=n/(n/i);
		for (int j=i;j<=min(last,i+1);j++){
			if ((n%j)&1) GetSG(n/j+1);
			if ((j-n%j)&1) GetSG(n/j);
		}
	}
	mem(vis,0);
	for (int i=2,last;i<=n;i=last+1){
		last=n/(n/i);
		for (int j=i;j<=min(last,i+1);j++){
			int s=0;
			if ((n%j)&1) s^=GetSG(n/j+1);
			if ((j-n%j)&1) s^=GetSG(n/j);
			vis[s]=1;
		}
	}
	SG[n]=0;
	while (vis[SG[n]]) SG[n]++;
	return SG[n];
}
