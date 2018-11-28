#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int Mod=10007;
const int inf=2147483647;

int n;
char Mp[maxN][maxN];
int Up[maxN][maxN],Down[maxN][maxN];
int F1[maxN][maxN],F2[maxN][maxN];
pair<int,int> Q[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%s",Mp[i]+1);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (Mp[i][j]=='B') Up[i][j]=Up[i-1][j]+1;
	for (int i=n;i>=1;i--) for (int j=1;j<=n;j++) if (Mp[i][j]=='B') Down[i][j]=Down[i+1][j]+1;

	for (int i=1;i<=n;i++){
		int top=1,sum=Mod-1;Q[1]=make_pair(0,0);
		for (int j=1;j<=n;j++){
			while ((top)&&(Q[top].second>=Up[i][j])){
				sum=(sum-1ll*Q[top].second*(Q[top].first-Q[top-1].first)%Mod+Mod)%Mod;
				--top;
			}
			Q[++top]=make_pair(j,Up[i][j]);
			sum=(sum+1ll*Q[top].second*(Q[top].first-Q[top-1].first)%Mod)%Mod;
			if (Mp[i][j]=='B') F1[i][j]=sum;
		}
		top=1;sum=Mod-1;Q[1]=make_pair(n+1,0);
		for (int j=n;j>=1;j--){
			while ((top)&&(Q[top].second>=Down[i][j])){
				sum=(sum-1ll*Q[top].second*(Q[top-1].first-Q[top].first)%Mod+Mod)%Mod;
				--top;
			}
			Q[++top]=make_pair(j,Down[i][j]);
			sum=(sum+1ll*Q[top].second*(Q[top-1].first-Q[top].first)%Mod)%Mod;
			if (Mp[i][j]=='B') F2[i][j]=sum;
		}
	}

	
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			cout<<F1[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			cout<<F2[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	//*/

	for (int i=n;i>=1;i--) for (int j=n;j>=1;j--) F2[i][j]=((F2[i][j]+F2[i+1][j]+F2[i][j+1]-F2[i+1][j+1])%Mod+Mod)%Mod;

	int Ans=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			Ans=(Ans+1ll*F1[i][j]*(F2[i+1][1]+F2[1][j+1]-F2[i+1][j+1]+Mod)%Mod)%Mod;
			//cout<<"("<<i<<","<<j<<")"<<F1[i][j]<<" "<<F2[i+1][1]+F2[1][j+1]-F2[i+1][j+1]<<endl;
		}
	//int cnt=0;
	//for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) cnt+=(Mp[i][j]=='B');
	//Ans=(Ans-1ll*cnt*(cnt-1)/2%Mod+Mod)%Mod;
	printf("%d\n",Ans);return 0;
}
