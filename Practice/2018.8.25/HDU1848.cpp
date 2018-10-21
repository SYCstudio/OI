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

int n;
int SG[maxN],Fab[maxN];
bool vis[maxN];

int main(){
	SG[0]=0;Fab[1]=1;Fab[2]=2;
	for (int i=3;i<=20;i++) Fab[i]=Fab[i-1]+Fab[i-2];
	for (int i=1;i<maxN;i++){
		for (int j=1;Fab[j]<=i;j++) vis[SG[i-Fab[j]]]=1;
		int p=0;
		while (vis[p]) p++;
		SG[i]=p;
		for (int j=1;Fab[j]<=i;j++) vis[SG[i-Fab[j]]]=0;
	}
	//for (int i=1;i<=20;i++) cout<<SG[i]<<" ";cout<<endl;

	int m,n,p;
	while (scanf("%d%d%d",&m,&n,&p)!=EOF){
		if ((m==0)&&(n==0)&&(p==0)) break;
		if (SG[m]^SG[n]^SG[p]) printf("Fibo\n");
		else printf("Nacci\n");
	}

	return 0;
}
