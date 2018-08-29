#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int inf=2147483647;

int n,Fa[maxN],Dg[maxN],Dgg[maxN];
bool vis[maxN],alive[maxN];
queue<int> Q;

int main(){
	int Ans1=0,Ans2=n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d",&Fa[i]);Dg[Fa[i]]++;
	}
	for (int i=1;i<=n;i++) Dgg[i]=Dg[i],alive[i]=1;

	for (int i=1;i<=n;i++) if (Dg[i]==0) Q.push(i),Ans2--;
	while (!Q.empty()){
		int u=Q.front();Q.pop();
		int v=Fa[u];
		if (alive[v]){
			
		}
	}
}
/*
https://blog.csdn.net/l_0_forever_lf/article/details/78748262
//*/
