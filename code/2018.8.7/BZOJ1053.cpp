#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int pricnt=12;
const int Prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41};

int n;
int mx=0,ans=0;
int Cnt[pricnt+1];

void dfs(int depth,int sum,int key);

int main(){
	scanf("%d",&n);
	dfs(0,1,1);
	printf("%d\n",ans);
	return 0;
}

void dfs(int depth,int sum,int key){
	if (depth>pricnt) return;
	if ((sum>mx)||((sum==mx)&&(key<ans))){
		ans=key;mx=sum;
	}
	int ret=1;
	while ((1ll*key*Prime[depth]<=n)&&((depth==0)||(Cnt[depth]<Cnt[depth-1]))){
		key=key*Prime[depth];Cnt[depth]++;
		dfs(depth+1,sum*(Cnt[depth]+1),key);
	}
	Cnt[depth]=0;
	return;
}
