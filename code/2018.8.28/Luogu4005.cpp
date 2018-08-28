#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50;
const int maxCnt=4194304+10;
const int inf=2147483647;

class Range
{
public:
	int l,r;
};

int n,Seq[maxN],rcnt;
Range Re[maxN];
int Ans,Cnt[maxCnt],Tot[maxN],S[maxN],lst[maxN];

bool cmp(Range A,Range B);
void dfs(int now,int s,int cnt);

int main(){
	for (int i=0;i<maxCnt;i++) Cnt[i]=Cnt[i>>1]+(i&1);
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d",&n);rcnt=0;mem(lst,0);mem(Tot,0);mem(S,0);
		for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
		if (n<=6){
			printf("0\n");continue;
		}
		for (int i=1;i<=n;i++)
			if (lst[Seq[i]]==0) lst[Seq[i]]=i;
			else Re[rcnt++]=((Range){lst[Seq[i]],i});
		sort(&Re[0],&Re[rcnt],cmp);

		if (rcnt==0){
			printf("0\n");continue;
		}

		//cout<<rcnt<<endl;

		for (int i=0;i<rcnt;i++)
			for (int j=0;j<i;j++)
				if (Re[j].r>Re[i].l){
					Tot[i]++;
					if (Re[j].r<Re[i].r) S[i]|=(1<<j);
				}
		Ans=inf;
		dfs(0,0,0);

		printf("%d\n",Ans);
	}

	return 0;
}

bool cmp(Range A,Range B){
	return A.l<B.l;
}

void dfs(int now,int s,int cnt){
	if (cnt>=Ans) return;
	if (now==rcnt){
		Ans=cnt;return;
	}
	int d=Cnt[s&S[now]];
	dfs(now+1,s|(1<<now),cnt+min(d,Tot[now]-d));
	d=Cnt[S[now]]-d;
	dfs(now+1,s,cnt+min(d,Tot[now]-d));
	return;
}

