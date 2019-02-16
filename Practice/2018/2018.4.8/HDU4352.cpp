#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=21;
const int inf=2147483647;

ll K;
int Arr[maxN];
ll F[maxN][1<<10][11];
int histcnt=0,Hist[maxN][1<<10][2];

ll Calc(ll Limit);
ll dfs(int now,int S,bool up,bool zero);
int GetS(int S,int pos);

int main()
{
	//freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	mem(F,-1);
	int T;scanf("%d",&T);
	int cas=0;
	while (T--)
	{
		ll L,R;;scanf("%lld%lld%lld",&L,&R,&K);
		printf("Case #%d: %lld\n",++cas,Calc(R)-Calc(L-1));
	}
	return 0;
}

ll Calc(ll Limit)
{
	histcnt++;
	int len=0;
	while (Limit){
		Arr[++len]=Limit%10;Limit/=10;
	}
	return dfs(len,0,1,1);
}

ll dfs(int now,int S,bool up,bool zero)
{
	if (now==0)
	{
		int cnt=0;
		for (int i=0;i<=9;i++) cnt+=((S&(1<<i))!=0);
		return cnt==K;
	}
	if ((up==0)&&(F[now][S][K]!=-1)) return F[now][S][K];
	//Hist[now][S][up]=histcnt;
	ll Ret=0;//F[now][S][up]=0;
	int mx=(up)?(Arr[now]):(9);
	for (int i=0;i<=mx;i++)
		Ret+=dfs(now-1,((zero)&&(i==0))?(0):(GetS(S,i)),(up)&&(i==Arr[now]),(zero)&&(i==0));
	if (up==0) F[now][S][K]=Ret;
	return Ret;
}

int GetS(int S,int pos)
{
	for (int i=pos;i<=9;i++)
		if ((S&(1<<i))!=0) return S^(1<<i)^(1<<pos);
	return S^(1<<pos);
}
