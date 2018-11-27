#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=52;
const int maxM=101000;
const int inf=2147483647;

int n;
int C[maxN],F[maxM],Low[maxM];
bool notp[maxM];
int pcnt,P[maxM];

int main(){
	notp[1]=1;
	for (int i=2;i<maxM;i++){
		if (notp[i]==0) P[++pcnt]=i,Low[i]=i;
		for (int j=1;(j<=pcnt)&&(1ll*P[j]*i<maxM);j++){
			notp[i*P[j]]=1;Low[i*P[j]]=P[j];
			if (i%P[j]==0) break;
		}
	}
	//for (int i=1;i<=20;i++) cout<<Low[i]<<" ";cout<<endl;
	scanf("%d",&n);int mx=0;
	for (int i=1;i<=n;i++) scanf("%d",&C[i]),mx=max(mx,C[i]);

	mem(F,63);
	for (int i=mx;i>=1;i--){
		int sum=0,x=i;for (int j=1;j<=n;j++) sum=sum+C[j]/i;
		F[i]=min(F[i],sum);
		while (x>1){
			sum=0;//if (i==100) cout<<i<<"->"<<x<<endl;
			for (int j=1;j<=n;j++) sum=sum+(C[j]%i)/(i/Low[x]);
			F[i/Low[x]]=min(F[i/Low[x]],F[i]+sum);
			int p=Low[x];while (x%p==0) x/=p;
		}
	}
	//for (int i=1;i<=mx;i++) cout<<i<<" "<<F[i]<<endl;
	printf("%d\n",F[1]);
	return 0;
}
