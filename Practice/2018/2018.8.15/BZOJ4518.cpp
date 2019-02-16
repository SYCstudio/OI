#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=3010;
const int inf=2147483647;

int n,m;
int Val[maxN];
int F[maxN],G[maxN],Q[maxN];

int Calc(int C);
ll GetX(int i,int j);
ll GetY(int i,int j);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]),Val[i]+=Val[i-1];

	int L=0,R=Val[n]*Val[n],pos;
	do{
		int mid=(L+R)>>1;
		//cout<<"("<<L<<","<<R<<")"<<endl;
		if (Calc(mid)>=m) pos=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);
	Calc(pos);
	//cout<<"pos:"<<pos<<" "<<F[n]-pos*m<<" "<<Val[n]<<endl;
	printf("%lld\n",1ll*m*(F[n]-1ll*pos*m)-1ll*Val[n]*Val[n]);

	return 0;
}

int Calc(int C){
	F[0]=0;G[0]=0;
	int h=1,t=1;Q[1]=0;
	for (int i=1;i<=n;i++){
		while ((h<t)&&(GetY(Q[h],Q[h+1])<=1ll*Val[i]*GetX(Q[h],Q[h+1]))) h++;
		F[i]=F[Q[h]]+(Val[i]-Val[Q[h]])*(Val[i]-Val[Q[h]])+C;
		G[i]=G[Q[h]]+1;
		//cout<<Q[h]<<"->"<<i<<endl;
		while ((h<t)&&(1ll*GetY(Q[t-1],Q[t])*GetX(Q[t],i)>=1ll*GetY(Q[t],i)*GetX(Q[t-1],Q[t]))) t--;
		Q[++t]=i;
	}
	//cout<<"C:"<<C<<endl;
	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<G[i]<<" ";cout<<endl;
	return G[n];
}

ll GetY(int i,int j){
	return F[j]-F[i]+1ll*Val[j]*Val[j]-1ll*Val[i]*Val[i];
}

ll GetX(int i,int j){
	return 2ll*(Val[j]-Val[i]);
}
