#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxM=13;
const int maxAlpha=3;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m,C,Q,U;
char S1[maxM],S2[maxM];
int M[100];
int Next[maxN],ta[maxAlpha][maxN],tb[maxAlpha][maxN];
int F[1<<maxM][maxM][maxM],G[1<<maxM][maxM][maxM];

void Add(int &x,int y);
void clear();
void copy();

int main(){
	M['W']=0;M['B']=1;M['X']=2;
	scanf("%d%d%d%d",&n,&m,&C,&Q);
	U=1<<(m-C+1);
	while (Q--){
		mem(F,0);mem(G,0);mem(ta,0);mem(tb,0);mem(S1,-1);mem(S2,-1);
		scanf(" %s",S1+1);scanf(" %s",S2+1);
		for (int i=1;i<=C;i++) S1[i]=M[S1[i]],S2[i]=M[S2[i]];
		int na,nb;

		Next[0]=Next[1]=0;
		for (int i=2;i<=C;i++){
			int j=Next[i-1];
			while ((j!=0)&&(S1[j+1]!=S1[i])) j=Next[j];
			if (S1[j+1]==S1[i]) j++;Next[i]=j;
		}
		na=Next[C];
		for (int i=0;i<C;i++)
			for (int k=0;k<maxAlpha;k++){
				int now=i;
				while ((now!=0)&&(S1[now+1]!=k)) now=Next[now];
				if (S1[now+1]==k) now++;
				ta[k][i]=now;
			}

		Next[0]=Next[1]=0;
		for (int i=2;i<=C;i++){
			int j=Next[i-1];
			while ((j!=0)&&(S2[j+1]!=S2[i])) j=Next[j];
			if (S2[j+1]==S2[i]) j++;Next[i]=j;
		}
		nb=Next[C];
		for (int i=0;i<=C;i++)
			for (int k=0;k<maxAlpha;k++){
				int now=i;
				while ((now!=0)&&(S2[now+1]!=k)) now=Next[now];
				if (S2[now+1]==k) now++;
				tb[k][i]=now;
			}
		mem(F,0);mem(G,0);

		F[0][0][0]=1;
		for (int i=1;i<=n;i++){
			clear();
			for (int S=0;S<U;S++)
				for (int x=0;x<C;x++)
					for (int y=0;y<C;y++)
						Add(G[S][0][0],F[S][x][y]);
			copy();
			for (int j=1;j<=m;j++){
				clear();
				for (int S=0;S<U;S++)
					for (int x=0;x<C;x++)
						for (int y=0;y<C;y++)
							if (F[S][x][y])
								for (int k=0;k<maxAlpha;k++){
									int ns=S,nx=ta[k][x],ny=ta[k][y];
									if ((j>=C)&&(ns&(1<<(j-C)))) ns^=(1<<(j-C));
									if (nx==C) ns^=(1<<(j-C)),nx=na;
									if (ny==C){
										if (S&(1<<(j-C))) continue;
										ny=nb;
									}
									Add(G[ns][nx][ny],F[S][x][y]);
								}
				copy();
			}
		}
		int ans=1;for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) ans=1ll*ans*3ll%Mod;
		for (int S=0;S<U;S++) for (int x=0;x<C;x++) for (int y=0;y<C;y++) ans=(ans-F[S][x][y]+Mod)%Mod;

		printf("%d\n",ans);
	}
	return 0;
}

void Add(int &x,int y){
	x=(x+y)%Mod;return;
}

void clear(){
	for (int S=0;S<U;S++) for (int i=0;i<C;i++) for (int j=0;j<C;j++) G[S][i][j]=0;
	return;
}

void copy(){
	for (int S=0;S<U;S++) for (int i=0;i<C;i++) for (int j=0;j<C;j++) F[S][i][j]=G[S][i][j];
	return;
}
