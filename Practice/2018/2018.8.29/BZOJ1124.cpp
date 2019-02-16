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
int mxd,cnt,Ans1,Ans2;

void dfs(int u);

int main(){
	scanf("%d",&n);
	Ans1=0;Ans2=n;
	for (int i=1;i<=n;i++){
		scanf("%d",&Fa[i]);Dg[Fa[i]]++;
	}
	for (int i=1;i<=n;i++) Dgg[i]=Dg[i],alive[i]=1;

	for (int i=1;i<=n;i++) if (Dg[i]==0) Q.push(i),Ans2--;
	while (!Q.empty()){
		int u=Q.front();Q.pop();
		int v=Fa[u];
		if (alive[u]){
			if (alive[v]) Ans1++,alive[v]=0;
			if (Dg[v]) Dg[v]=0,Q.push(v);
		}
		else{
			if (Dg[v]){
				Dg[v]--;
				if (Dg[v]==0) Q.push(v);
			}
		}
	}
	for (int i=1;i<=n;i++)
		if ((Dg[i]!=0)&&(vis[i]==0)){
			mxd=0;cnt=0;
			dfs(i);
			if ((mxd==1)&&(cnt>1)) Ans2--;
		}
	printf("%d %d\n",Ans1,Ans2);
	return 0;
}

void dfs(int u){
	if (vis[u]) return;
	vis[u]=1;cnt++;
	mxd=max(mxd,Dgg[u]);
	if (alive[u]) alive[Fa[u]]=0,Ans1++;
	dfs(Fa[u]);
	return;
}
/*
https://blog.csdn.net/l_0_forever_lf/article/details/78748262
//*/
