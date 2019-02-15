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

int a,b,c;
int SG[maxN];
bool vis[maxN];

int main(){
	scanf("%d%d%d",&a,&b,&c);
	for (int i=min(a,min(b,c));i<maxN;i++){
		mem(vis,0);
		if (i>=a) for (int j=0;j<=i-a;j++) vis[SG[j]^SG[i-a-j]]=1;
		if (i>=b) for (int j=0;j<=i-b;j++) vis[SG[j]^SG[i-b-j]]=1;
		if (i>=c) for (int j=0;j<=i-c;j++) vis[SG[j]^SG[i-c-j]]=1;
		while (vis[SG[i]]) SG[i]++;
	}

	int m;scanf("%d",&m);
	while (m--){
		int key;scanf("%d",&key);
		if (SG[key]) printf("1\n");
		else printf("2\n");
	}

	return 0;
}

/*
1 5 1
3 
1 
5 
6
//*/
