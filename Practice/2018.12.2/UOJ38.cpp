#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int P[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281};
const int Mod=19961993;
const int inf=2147483647;

class Data
{
public:
	int D[60];
};

int n=100000;
Data BIT[maxN];

Data operator + (Data A,Data B);
Data operator - (Data A,Data B);
int QPow(int x,int cnt);
void Modify(int pos,int key);
Data Sum(int pos);
Data Query(int l,int r);

int main(){
	for (int i=1;i<=n;i++) BIT[i].D[1]=(i)&(-i);
	int m;scanf("%d",&m);
	while (m--){
		int opt,a,b;scanf("%d%d%d",&opt,&a,&b);
		if (opt==0){
			Data R=Query(a,b);
			//for (int i=0;i<4;i++) cout<<R.D[i]<<" ";cout<<endl;
			int Ans=1;
			for (int i=0;i<60;i++)
				if (R.D[i]) Ans=1ll*Ans*QPow(P[i],R.D[i]-1)%Mod*(P[i]-1)%Mod;
			printf("%d\n",Ans);
		}
		if (opt==1) Modify(a,b);
	}
	return 0;
}

Data operator + (Data A,Data B){
	for (int i=0;i<60;i++) A.D[i]+=B.D[i];
	return A;
}

Data operator - (Data A,Data B){
	for (int i=0;i<60;i++) A.D[i]-=B.D[i];
	return A;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void Modify(int pos,int key){
	Data D;mem(D.D,0);
	for (int i=0;i<60;i++)
		while (key%P[i]==0) key/=P[i],++D.D[i];
	D=D-Query(pos,pos);
	while(pos<=n){
		BIT[pos]=BIT[pos]+D;
		pos+=(pos)&(-pos);
	}
	return;
}

Data Sum(int pos){
	Data Ret;mem(Ret.D,0);
	while (pos){
		Ret=Ret+BIT[pos];
		pos-=(pos)&(-pos);
	}
	return Ret;
}

Data Query(int l,int r){
	return Sum(r)-Sum(l-1);
}
