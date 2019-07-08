#include<bits/stdc++.h>
using namespace std;

#define pw(x) (1<<(x))

const int maxN=20;
const int maxM=pw(maxN)+10;
const int Mod=998244353;

int n,N,A[maxN];
int Sm[maxM],F[maxM],G[maxM],C[maxM];

void Plus(int &x,int y);
int main()
{
	scanf("%d",&n);
	N=pw(n);
	for (int i=0; i<n; i++) scanf("%d",&A[i]),Sm[pw(i)]=A[i];
	for (int S=1; S<N; S++) Sm[S]=Sm[S-((S)&(-S))]+Sm[(S)&(-S)];

	for (int i=0; i<n; i++) F[pw(i)]=1;
	for (int S=1; S<N; S++)
		if (Sm[S]>0)
			for (int i=0; i<n; i++)
				if ((S&pw(i))==0)
					Plus(F[S|pw(i)],F[S]);
	G[0]=1;
	for (int S=1; S<N; S++)
		if (Sm[S]<=0)
			for (int i=0; i<n; i++)
				if (S&pw(i))
					Plus(G[S],G[S^pw(i)]);
	//for (int S=0;S<N;S++) cout<<F[S]<<" ";cout<<endl;
	//for (int S=0;S<N;S++) cout<<G[S]<<" ";cout<<endl;
	//for (int S=0;S<N;S++) cout<<Sm[S]<<" ";cout<<endl;
	int Ans=0;
	for (int S=0; S<N; S++) {
		//cout<<1ll*Sm[S]*F[S]%Mod*G[(N-1)^S]%Mod<<" ";
		Ans=(Ans+1ll*Sm[S]*F[S]%Mod*G[(N-1)^S]%Mod)%Mod;
		Ans=(Ans+Mod)%Mod;
	}//cout<<endl;
	printf("%d\n",Ans);
	return 0;
}
void Plus(int &x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return;
}
