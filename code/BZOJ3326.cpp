#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int Mod=20130427;
const int inf=2147483647;

int B;
int L[maxN],R[maxN];
int F[2][maxN],G[2][maxN];

int Calc(int len,int *M);
int GetOne(int key);

int main(){
	int n,m;
	scanf("%d",&B);
	scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&L[i]);
	scanf("%d",&m);for (int i=1;i<=m;i++) scanf("%d",&R[i]);

	int Ans=0,sum=0;
	for (int i=1;i<=n;i++){
		sum=(1ll*sum*B%Mod+1ll*L[i]*i%Mod)%Mod;
		Ans=(Ans+sum)%Mod;
	}

	sum=0;
	for (int i=1;i<=13;i++) sum+=GetOne(i);
	cout<<sum<<endl;

	printf("%d\n",((Ans+Calc(m,R)-Calc(n,L))%Mod+Mod)%Mod);
}

int Calc(int len,int *M){
	int Ans=0;mem(F,0);mem(G,0);
	F[0][1]=M[1];F[1][1]=M[1]*(M[1]-1)/2;
	G[0][1]=1;G[1][1]=(M[1]-1);
	Ans=F[0][1]+F[1][1];
	for (int i=2;i<=len;i++){
		F[0][i]=F[0][i-1]*B+G[0][i-1]*M[i]+M[i];
		G[0][i]=G[0][i-1]+1;

		F[1][i]=F[0][i-1]+F[0][i-1]*B*M[i]+M[i]*(M[i]-1)/2*G[0][i-1]+M[i]*(M[i]-1)/2*G[0][i-1]+M[i]*(M[i]-1)/2;
		G[1][i]=G[0][i-1]*M[i]+M[i];

		F[1][i]=F[1][i]+F[1][i-1]*B*B+B*(B-1)/2*G[1][i-1]+B*(B-1)/2*G[1][i-1];
		G[1][i]=G[1][i]+G[1][i-1]*B;

		Ans=(Ans+F[0][i]+F[1][i])%Mod;
	}
	for (int i=1,sum=0,cnt=0;i<len;i++){
		sum=sum*B+B*(B-1)/2*cnt+B*(B-1)/2*cnt+B*(B-1)/2;
		cnt=cnt*B+B;
		cout<<i<<" "<<sum<<" "<<cnt<<endl;
		Ans=Ans+sum;
	}
	cout<<"Calc:";for (int i=1;i<=len;i++) cout<<M[i];cout<<" "<<Ans<<endl;
	for (int i=1;i<=len;i++) cout<<"("<<F[0][i]<<","<<F[1][i]<<") ";cout<<endl;
	for (int i=1;i<=len;i++) cout<<"("<<G[0][i]<<","<<G[1][i]<<") ";cout<<endl;
	return Ans;
}

int GetOne(int key){
	int ans=0;
	int up=0,x=key,P[100];
	while (x){
		up++;P[up]=x%10;
		x/=10;
	}

	reverse(&P[1],&P[up+1]);
	int sum=0;
	for (int i=1;i<=up;i++){
		sum=sum*B+P[i]*i;
		ans+=sum;
	}
	return ans;
}
