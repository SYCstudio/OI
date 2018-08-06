#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define GetNum(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=201000*4;
const int inf=2147483647;

int n,m;
int numcnt,Num[maxN];
int L[maxN],R[maxN];
int F[maxN];
vector<int> To[maxN];
int Limit,top,St[maxN],Ans[maxN];

void dfs(int u);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d%d",&L[i],&R[i]),Num[++numcnt]=L[i],Num[++numcnt]=R[i];
	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	for (int i=1;i<=n;i++) L[i]=GetNum(L[i]),R[i]=GetNum(R[i]);

	for (int i=1;i<=numcnt+numcnt;i++) F[i]=i;
	for (int i=1;i<=n;i++)
		if (L[i]<=R[i]){
			F[L[i]]=max(F[L[i]],R[i]);
			F[L[i]+numcnt]=max(F[L[i]+numcnt],R[i]+numcnt);
		}
		else{
			F[1]=max(F[1],R[i]);
			F[L[i]]=max(F[L[i]],R[i]+numcnt);
			F[L[i]+numcnt]=max(F[L[i]+numcnt],numcnt+numcnt);
		}
	for (int i=1;i<=numcnt+numcnt;i++) F[i]=max(F[i],F[i-1]);

	Limit=0;
	for (int now=1;now<numcnt+1;now=F[now]) Limit++;
	Limit--;

	for (int i=1;i<numcnt+numcnt;i++) To[F[i]].push_back(i);
	dfs(numcnt+numcnt);

	for (int i=1;i<=n;i++) printf("%d ",Ans[L[i]]);
	printf("\n");
	return 0;
}

void dfs(int u){
	St[++top]=u;
	if (u<=numcnt)
		for (int i=Limit;;i++)
			if (St[top-i]>=u+numcnt){
				Ans[u]=i;break;
			}
	for (int sz=To[u].size(),i=0;i<sz;i++) dfs(To[u][i]);
	top--;return;
}
