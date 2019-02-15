#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int inf=2147483647;

int n,K;
char str[maxN];
int Next[maxN],Pre[maxN];
bool vis[maxN];

int main(){
	scanf("%d%d",&n,&K);
	scanf("%s",str+1);
	for (int i=0;i<=n+1;i++) Next[i]=i+1,Pre[i]=i-1;
	Next[n+1]=-1;Pre[0]=-1;
	int now=1;
	while (1){
		while ((Pre[now]!=-1)&&(str[now]==')')&&(str[Pre[now]]=='(')){
			vis[now]=vis[Pre[now]]=1;
			K-=2;if (K==0) break;
			int pre=Pre[now];
			now=Next[now];Pre[now]=Pre[pre];
			if (Pre[pre]!=-1) Next[Pre[pre]]=now;
		}
		if (K==0) break;
		now=Next[now];
	}
	for (int i=1;i<=n;i++) if (vis[i]) printf("%c",str[i]);printf("\n");
	return 0;
}
