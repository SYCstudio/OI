#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const ull base=19260817;
const int inf=2147483647;

int n,K;
ll Cnt[7],C[10][10];
multiset<ull> St[7],now;

int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++){
		int Spr[7],Seq[7];scanf("%d%d%d%d%d%d",&Spr[0],&Spr[1],&Spr[2],&Spr[3],&Spr[4],&Spr[5]);
		now.clear();
		for (int S=1;S<(1<<6);S++){
			int cnt=0;ull hash=0;
			for (int j=0;j<6;j++)
				if (S&(1<<j)) hash=hash*base+1ull*Spr[j]+1,cnt++;
				else hash=hash*base;
			if (now.count(hash)) continue;now.insert(hash);
			//if (St[cnt].count(hash)) cout<<i<<" "<<cnt<<" "<<S<<" "<<hash<<" "<<St[cnt].count(hash)<<endl;
			Cnt[cnt]+=St[cnt].count(hash);St[cnt].insert(hash);
		}
		//cout<<i<<":";
		//for (int j=1;j<=6;j++) cout<<Cnt[j]<<" ";cout<<endl;
		//for (int j=0;j<6;j++) cout<<Spr[j]<<" ";cout<<endl;
	}

	//for (int i=1;i<=6;i++) cout<<Cnt[i]<<" ";cout<<endl;

	for (int i=0;i<10;i++)
		for (int j=C[i][0]=1;j<=i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];

	for (int i=5;i>=1;i--)
		for (int j=i+1;j<=6;j++) Cnt[i]=Cnt[i]-Cnt[j]*C[j][i];

	Cnt[0]=1ll*n*(n-1)/2-Cnt[1]-Cnt[2]-Cnt[3]-Cnt[4]-Cnt[5]-Cnt[6];

	//for (int i=0;i<=6;i++) cout<<Cnt[i]<<" ";cout<<endl;

	printf("%lld\n",Cnt[K]);return 0;
}
