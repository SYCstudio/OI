#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int Mod=19940417;
const int inf=2147483647;

int n,K;
pair<int,int> P[maxN];
int F[maxN][2];

int QPow(int x,int cnt);

int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=K;i++) scanf("%d%d",&P[i].first,&P[i].second);
	P[++K]=make_pair(0,0);P[++K]=make_pair(n,0);
	sort(&P[1],&P[K+1]);K=unique(&P[1],&P[K+1])-P-1;

	//for (int i=1;i<=K;i++) cout<<"("<<P[i].first<<","<<P[i].second<<")"<<endl;

	int mx=0;
	F[1][0]=0;F[1][1]=1;
	for (int i=2;i<=K;i++){
		int x1=P[i-1].first,y1=P[i-1].second,x2=P[i].first,y2=P[i].second;

		int dx=x2-x1,dy=dx-y1-y2,zero=dy/2;
		mx=max(mx,(x2-x1+y2+y1)/2);

		if (zero<=0){
			if (x2-x1==y2-y1){
				F[i][0]=(F[i][0]+F[i-1][0])%Mod;
				if (y1==0) F[i][0]=(F[i][0]+F[i-1][1])%Mod;
			}
			else if (x2-x1==y1-y2){
				F[i][1]=(F[i][1]+F[i-1][1]+F[i-1][0])%Mod;
			}
			else{
				F[i][1]=F[i-1][0];
				if (y1==0) F[i][1]=(F[i][1]+F[i-1][1])%Mod;
				if (zero==0) F[i][0]=(F[i-1][1]+F[i-1][0])%Mod;
			}
		}
		else{
			int two=QPow(2,zero-1);
			if (y2){
				F[i][0]=1ll*F[i-1][1]*two%Mod;
				if (y1) F[i][0]=(F[i][0]+1ll*F[i-1][0]*two*2ll%Mod)%Mod;
			}
			F[i][1]=1ll*F[i-1][1]*two%Mod;
			if (y1) F[i][1]=(F[i][1]+1ll*F[i-1][0]*two*2ll%Mod)%Mod;
		}
	}
	//for (int i=1;i<=K;i++) cout<<F[i][0]<<" "<<F[i][1]<<endl;
	printf("%d %d\n",(F[K][0]+F[K][1])%Mod,mx);
	return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}
