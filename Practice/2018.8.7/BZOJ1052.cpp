#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=20010;
const int inf=2100000000;

int n;
int X[maxN],Y[maxN];
int Mark[maxN];

bool dfs(int depth,int Limit);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&X[i],&Y[i]);

	int L=0,R=2000000000,Ans=-1;
	do{
		int mid=(L+R)>>1;mem(Mark,0);
		if (dfs(1,mid)) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	while (L<=R);

	printf("%d\n",Ans);

	return 0;
}

bool dfs(int depth,int Limit){
	if (depth==4){
		for (int i=1;i<=n;i++) if (Mark[i]==0) return 0;
		return 1;
	}

	for (int opt=1;opt<=4;opt++){
		int x,y;
		if (opt==1) x=inf,y=inf;
		if (opt==2) x=-inf,y=inf;
		if (opt==3) x=-inf,y=-inf;
		if (opt==4) x=inf,y=-inf;

		for (int i=1;i<=n;i++)
			if (Mark[i]==0){
				if (opt==1) x=min(x,X[i]),y=min(y,Y[i]);
				if (opt==2) x=max(x,X[i]),y=min(y,Y[i]);
				if (opt==3) x=max(x,X[i]),y=max(y,Y[i]);
				if (opt==4) x=min(x,X[i]),y=max(y,Y[i]);
			}

		for (int i=1;i<=n;i++)
			if (Mark[i]==0){
				bool flag=0;
				if (opt==1) flag=(X[i]<=x+Limit)*(Y[i]<=y+Limit);
				if (opt==2) flag=(X[i]>=x-Limit)*(Y[i]<=y+Limit);
				if (opt==3) flag=(X[i]>=x-Limit)*(Y[i]>=y-Limit);
				if (opt==4) flag=(X[i]<=x+Limit)*(Y[i]>=y-Limit);
				if (flag) Mark[i]=depth;
			}

		if (dfs(depth+1,Limit)) return 1;

		for (int i=1;i<=n;i++) if (Mark[i]==depth) Mark[i]=0;
	}
	return 0;
}
