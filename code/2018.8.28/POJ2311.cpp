#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int inf=2147483647;

int SG[maxN][maxN];
bool use[maxN*maxN];

int main(){
	mem(SG,-1);
	int W,H;
	for (int i=2;i<maxN;i++)
		for (int j=2;j<maxN;j++){
			for (int k=2;k<=i-2;k++) use[SG[k][j]^SG[i-k][j]]=1;
			for (int k=2;k<=j-2;k++) use[SG[i][k]^SG[i][j-k]]=1;
			SG[i][j]=0;while (use[SG[i][j]]) SG[i][j]++;
			for (int k=2;k<=i-2;k++) use[SG[k][j]^SG[i-k][j]]=0;
			for (int k=2;k<=j-2;k++) use[SG[i][k]^SG[i][j-k]]=0;
		}
	while (scanf("%d%d",&W,&H)!=EOF){
		if (SG[W][H]==0) printf("LOSE\n");
		else printf("WIN\n");
	}
}
