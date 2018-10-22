#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=11;
const int Mod=1e9+7;
const int inf=2147483647;

int n;
map<ull,int> M;

class Data
{
public:
	int sz;
	int A[maxN];
	ull hash(){
		ull ret=sz;
		for (int i=1;i<=n;i++) ret=ret*28+(ull)A[i];
		return ret;
	}
	void srt(){
		sort(&A[1],&A[sz+1]);reverse(&A[1],&A[sz+1]);return;
	}
	Data operator = (Data D){
		sz=D.sz;
		for (int i=1;i<=n;i++) A[i]=D.A[i];
		return *this;
	}
};

int dfs(int now,Data stt);

int main(){
	scanf("%d",&n);Data Start;
	mem(Start.A,0);Start.sz=1;M[Start.hash()]=1;
	for (int i=1;i<=n;i++) scanf("%d",&Start.A[i]);
	Start.sz=n;Start.srt();
	printf("%d\n",dfs(1,Start));return 0;
}

int dfs(int now,Data stt){
	//cout<<now<<":"<<stt.sz<<" ";for (int i=1;i<=n;i++) cout<<stt.A[i]<<" ";cout<<endl;
	if (3*(stt.sz-now+1)<stt.A[stt.sz]) return 0;
	if (now==stt.sz){
		if (stt.A[stt.sz]!=0) return 0;
		stt.sz--;stt.srt();
		if (M.count(stt.hash())) return M[stt.hash()];
		return M[stt.hash()]=dfs(1,stt);
	}
	int ret=0;
	if (stt.A[now]>=3){
		stt.A[now]-=3;
		ret=(ret+dfs(now+1,stt))%Mod;
		stt.A[now]+=3;
	}
	if ((stt.A[now]>=1)&&(stt.A[stt.sz]>=1)){
		stt.A[now]--;stt.A[stt.sz]--;
		ret=(ret+dfs(now+1,stt))%Mod;
		stt.A[now]++;stt.A[stt.sz]++;
	}
	if (stt.A[stt.sz]>=3){
		stt.A[stt.sz]-=3;
		ret=(ret+dfs(now+1,stt))%Mod;
		stt.A[stt.sz]+=3;
	}
	return ret;
}
