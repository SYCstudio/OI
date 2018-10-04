#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50500<<1;
const int inf=2147483647;

int n;
int Seq[maxN];
bool Exi[maxN];
int F[maxN],G[maxN];
set<int> S;

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]),Exi[Seq[i]]=1;
	for (int i=1;i<=n+n;i++) if (Exi[i]==0) S.insert(i);
	for (int i=1;i<=n;i++)
		if (S.upper_bound(Seq[i])!=S.end()){
			S.erase(S.upper_bound(Seq[i]));F[i]=F[i-1]+1;
		}
		else F[i]=F[i-1];
	S.clear();
	for (int i=1;i<=n+n;i++) if (Exi[i]==0) S.insert(-i);
	for (int i=n;i>=1;i--)
		if (S.lower_bound(-Seq[i])!=S.end()){
			S.erase(S.lower_bound(-Seq[i]));G[i]=G[i+1]+1;
		}
		else G[i]=G[i+1];
	int Ans=0;
	for (int i=0;i<=n;i++) Ans=max(Ans,F[i]+G[i+1]);
	printf("%d\n",Ans);return 0;
}
/*
4
1
8
4
3
//*/
