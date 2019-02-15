#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-x))

const int maxN=100010;
const int R=100000;
const int P[60]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281};
const int Mod=19961993;
const int inf=2147483647;

class BIT
{
public:
	int B[maxN],Seq[maxN];

	void Add(int pos,int key){
		while (pos<=R){
			B[pos]+=key;pos+=lowbit(pos);
		}
		return;
	}

	int Sum(int pos){
		int ret=0;
		while (pos){
			ret+=B[pos];pos-=lowbit(pos);
		}
		return ret;
	}

	int Query(int l,int r){
		return Sum(r)-Sum(l-1);
	}
	
	void Modify(int pos,int key){
		Add(pos,key-Seq[pos]);Seq[pos]=key;
		return;
	}
};

BIT B[60];
int Cnt[60];

int GetPhi();
int QPow(int x,int cnt);

int main(){
	for (int i=1;i<=R;i++) B[1].Modify(i,1);
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int opt,a,b;scanf("%d%d%d",&opt,&a,&b);
		if (opt==0){
			for (int i=0;i<60;i++) Cnt[i]=B[i].Query(a,b);
			printf("%d\n",GetPhi());
		}
		if (opt==1)
			for (int i=0;i<60;i++){
				int cnt=0;
				while (b%P[i]==0) cnt++,b/=P[i];
				B[i].Modify(a,cnt);
			}
	}

	return 0;
}

int GetPhi(){
	//for (int i=0;i<60;i++) cout<<Cnt[i]<<" ";cout<<endl;
	int ret=1;
	for (int i=0;i<60;i++)
		if (Cnt[i]) ret=1ll*ret*QPow(P[i],Cnt[i]-1)%Mod*(P[i]-1)%Mod;
	return ret;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}
