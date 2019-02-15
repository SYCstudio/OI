#include<bits/stdc++.h>
using namespace std;

const int maxN=1010;
const int maxM=61000;
const int Mod=998244353;
const int inf=2147483647;

int n,H[maxN],F[maxN];
int tim,Tim[maxM],Cnt[maxM];

void Add(int pos,int key);
int Query(int pos);

int main(){
	scanf("%d",&n);int mx=0;
	for (int i=1;i<=n;i++) scanf("%d",&H[i]),mx=max(mx,H[i]);
	int Ans=n;
	for (int d=0;d<=mx;d++){
		tim++;
		for (int i=n;i>=1;i--){
			F[i]=(Query(H[i]+d))%Mod;
			//cout<<"Q:"<<Query(H[i]+d)<<" ";
			Add(H[i],F[i]+1);Ans=(Ans+F[i])%Mod;
			//cout<<F[i]<<" ";
		}
		//cout<<endl;
	}
	//cout<<Ans<<endl;
	reverse(&H[1],&H[n+1]);
	for (int d=1;d<=mx;d++){
		tim++;
		for (int i=n;i>=1;i--){
			F[i]=(Query(H[i]+d))%Mod;
			Add(H[i],F[i]+1);Ans=(Ans+F[i])%Mod;
		}
	}
	printf("%d\n",Ans);return 0;
}

void Add(int pos,int key){
	if (Tim[pos]!=tim) Tim[pos]=tim,Cnt[pos]=key;
	else Cnt[pos]=(Cnt[pos]+key)%Mod;
}

int Query(int pos){
	if (Tim[pos]==tim) return Cnt[pos];
	return 0;
}
