#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n,m;
int SG[2][maxN];
int St[maxN];
int tim,Tim[maxN];

void Init();
int GetSG(int key);

int main(){
	scanf("%d",&n);m=sqrt(n);
	Init();

	int Q;scanf("%d",&Q);
	while (Q--){
		int w,sum=0;scanf("%d",&w);
		while (w--){
			int key;scanf("%d",&key);
			sum^=GetSG(key);
		}

		if (sum==0) printf("No\n");
		else printf("Yes\n");
	}

	return 0;
}

void Init(){
	SG[0][1]=1;int top=0;
	for (int i=1,j;i<=n;i=j+1){
		j=n/(n/i);St[++top]=i;
	}

	for (int i=top;i>=1;i--){
		int x=St[i];
		int nowsg=0;tim++;Tim[nowsg]=tim;
		for (int l=2*x,r;l<=n;l=r+x){
			r=((n/(n/l))/x)*x;
			Tim[nowsg]=Tim[nowsg^GetSG(l)]=tim;
			if (((r-l+x)/x)&1) nowsg^=GetSG(l);
		}
		int g=0;
		while (Tim[g]==tim) g++;
		if (x<=m) SG[0][x]=g;
		else SG[1][n/x]=g;
	}
	return;
}

int GetSG(int x){
	if (x<=m) return SG[0][x];
	else return SG[1][n/x];
}
