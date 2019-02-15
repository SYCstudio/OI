#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeofArr)

const int maxN=101000;
const int Mod=1e9+7;
const int inf=2147483647;

int n;
int Up[maxN],Down[maxN],P[maxN],Q[maxN],Left[maxN],Sum[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int x,y;scanf("%d%d",&x,&y);x++;y++;
		P[x]=y;Q[y]=x;
	}

	Up[1]=Q[1];
	for (int i=2;i<n;i++) Up[i]=min(Q[i],Up[i-1]);
	Down[n-1]=Q[n];
	for (int i=n-2;i>=1;i--) Down[i]=max(Down[i+1],Q[i+1]);
	for (int i=1;i<n;i++) Down[i]--;

	P[1];
	for (int i=2;i<n;i++) P[i]=min(P[i],P[i-1]);
	for (int i=1;i<n;i++) Sum[i]=(Sum[i-1]+P[i]-1)%Mod,Left[i]=(Left[i-1]+Sum[i])%Mod;

	//for (int i=1;i<n;i++) cout<<Up[i]<<" ";cout<<endl;
	//for (int i=1;i<n;i++) cout<<Down[i]<<" ";cout<<endl;
	//for (int i=1;i<n;i++) cout<<P[i]<<" ";cout<<endl;
	//for (int i=1;i<n;i++) cout<<Sum[i]<<" ";cout<<endl;
	//for (int i=1;i<n;i++) cout<<Left[i]<<" ";cout<<endl;

	ll Ans=0;
	for (int i=1;i<n;i++)
		if (Down[i]>=Up[i]){
			ll key1=1ll*(Down[i]-Up[i]+1)*(Down[i]-Up[i]+2)/2%Mod*i%Mod;
			ll key2=(Left[Down[i]]-1ll*Sum[Up[i]-1]*(Down[i]-Up[i]+1)%Mod-Left[Up[i]-1]+Mod)%Mod;
			//cout<<i<<" "<<key1<<" "<<key2<<" s1:"<<Sum[Up[i]-1]<<" "<<Down[i]-Up[i]+1<<" s2:"<<Left[Up[i]]<<endl;
			Ans=((Ans+key1-key2)%Mod+Mod)%Mod;
		}
	printf("%lld\n",Ans);return 0;
}
