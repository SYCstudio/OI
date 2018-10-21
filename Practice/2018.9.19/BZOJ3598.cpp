#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=60;
const int maxSum=2510;
const int Mid=1000;
const int inf=2147483647;

int B;
ll F[2][maxN][maxSum];
int len,Num[maxN];

ll Calc(ll Up);
ll dfs1(int u,int sum,int limit);
ll dfs2(int u,int sum,int mid,int limit);

int main(){
	ll L,R;
	scanf("%lld%lld%d",&L,&R,&B);
	printf("%lld\n",Calc(R)-Calc(L-1));

	return 0;
}

ll Calc(ll Up){
	len=0;
	while (Up) Num[++len]=Up%B,Up/=B;
	reverse(&Num[1],&Num[len+1]);
	mem(F,-1);
	ll ret=dfs1(1,0,0);
	for (int i=1;i<len;i++){
		mem(F,-1);
		ret-=dfs2(1,0,i,0);
	}
	return ret;
}

ll dfs1(int u,int sum,int limit){
	if (u==len+1) return sum;
	if (F[limit][u][sum]!=-1) return F[limit][u][sum];
	ll ret=0;
	for (int i=0;i<=((limit)?(B-1):(Num[u]));i++)
		ret+=dfs1(u+1,sum+(u-1)*i,(limit)|(i<Num[u]));
	return F[limit][u][sum]=ret;
}

ll dfs2(int u,int sum,int mid,int limit){
	if (u==len+1) return max(sum,0);
	if (F[limit][u][sum+Mid]!=-1) return F[limit][u][sum+Mid];
	ll ret=0;
	for (int i=0;i<=((limit)?(B-1):(Num[u]));i++)
		ret+=dfs2(u+1,sum+((u<=mid)?(-i):(i)),mid,(limit)|(i<Num[u]));
	return F[limit][u][sum+Mid]=ret;
}
