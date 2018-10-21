#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=80;
const int inf=2147483647;

ll n,m,KK,P;
int F[2][2][2][maxN],G[2][2][2][maxN],N[maxN],M[maxN],K[maxN];
int Bin[maxN];

void Plus(int &x,int y);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%lld%lld%lld%lld",&n,&m,&KK,&P);
		Bin[0]=1;for (int i=1;i<maxN;i++) Bin[i]=(Bin[i-1]<<1)%P;
		int lenn=0,lenm=0,lenk=0,L;
		mem(N,0);mem(M,0);mem(K,0);
		while (n) N[++lenn]=n&1,n>>=1;
		while (m) M[++lenm]=m&1,m>>=1;
		while (KK) K[++lenk]=KK&1,KK>>=1;
		L=max(lenn,max(lenm,lenk));

		//for (int i=1;i<=L;i++) cout<<N[i];cout<<endl;
		//for (int i=1;i<=L;i++) cout<<M[i];cout<<endl;
		//for (int i=1;i<=L;i++) cout<<K[i];cout<<endl;
		
		mem(F,0);mem(G,0);
		for (int x=0;x<2;x++)
			for (int y=0;y<2;y++)
				for (int z=0;z<2;z++)
					for (int u=0;u<((x)?(2):(N[1]));u++)
						for (int v=0;v<((y)?(2):(M[1]));v++)
							if ((z)||((u^v)>=K[1])){
								Plus(F[x][y][z][1],((u^v)-K[1]+P)%P);
								Plus(G[x][y][z][1],1);
							}
		for (int len=2;len<=L;len++)
			for (int x=0;x<2;x++)
				for (int y=0;y<2;y++)
					for (int z=0;z<2;z++)
						for (int u=0;u<=max(x,N[len]);u++)
							for (int v=0;v<=max(y,M[len]);v++)
								if ((z)||((u^v)>=K[len])){
								int i=x|(u<N[len]),j=y|(v<M[len]),k=z|((u^v)>K[len]);
								//cout<<"("<<len-1<<","<<i<<","<<j<<","<<k<<") -> ("<<len<<","<<x<<","<<y<<","<<z<<") "<<u<<" "<<v<<endl;
								Plus(F[x][y][z][len],((1ll*G[i][j][k][len-1]*((u^v)-K[len])%P*Bin[len-1]%P+P)%P+F[i][j][k][len-1])%P);
								Plus(G[x][y][z][len],G[i][j][k][len-1]);
							}
		/*
		for (int i=1;i<=L;i++)
			for (int x=0;x<2;x++)
				for (int y=0;y<2;y++)
					for (int z=0;z<2;z++)
						cout<<"("<<i<<" "<<x<<" "<<y<<" "<<z<<") : "<<F[x][y][z][i]<<" "<<G[x][y][z][i]<<endl;
		//*/
		
		printf("%d\n",F[0][0][0][L]);
	}
	return 0;
}

void Plus(int &x,int y){
	x=((x+y)%P+P)%P;return;
}
