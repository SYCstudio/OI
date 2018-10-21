#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=12;
const int maxMap=110;
const int Mod=20110520;
const int inf=2147483647;

int R,C;
char Input[maxMap],M[maxMap][maxMap];
int F[2][250000];
int Tre[maxN];

void Plus(int &x,int y);

int main(){
	Tre[0]=1;for (int i=1;i<maxN;i++) Tre[i]=Tre[i-1]*3;
	scanf("%d%d",&R,&C);
	for (int i=1;i<=R;i++){
		scanf("%s",Input+1);
		if (R>=C) for (int j=1;j<=C;j++) M[i][j]=(Input[j]=='_');
		if (R<C) for (int j=1;j<=C;j++) M[j][i]=(Input[j]=='_');
	}
	if (R<C) swap(R,C);

	F[0][0]=1;
	int now=0;
	for (int x=1;x<=R;x++)
		for (int y=1;y<=C;y++){
			now^=1;mem(F[now],0);
			for (int k=0;k<Tre[C+1];k++)
				if (F[now^1][k]) {
					int p=k%3,q=k/Tre[y]%3,val=F[now^1][k],kk=k-p-q*Tre[y];
					if (M[x][y]==0){
						if ((p==0)&&(q==0)) Plus(F[now][k],val);
						continue;
					}
					if ((y==1)&&(p)) continue;
					if ((p==0)&&(q==0)){
						Plus(F[now][kk+2+2*Tre[y]],val);
						Plus(F[now][kk+1],val);
						Plus(F[now][kk+Tre[y]],val);
					}
					if ((p==0)&&(q==1)){
						Plus(F[now][kk+Tre[y]],val);
						Plus(F[now][kk+2],val);
					}
					if ((p==1)&&(q==0)){
						Plus(F[now][kk+2*Tre[y]],val);
						Plus(F[now][kk+1],val);
					}
					if ((p==1)&&(q==1)) Plus(F[now][kk],val);
					if ((p==0)&&(q==2)){
						Plus(F[now][kk],val);
						Plus(F[now][kk+2*Tre[y]],val);
					}
					if ((p==2)&&(q==0)){
						Plus(F[now][kk],val);
						Plus(F[now][kk+2],val);
					}
					//*/
				}
		}
	printf("%d\n",F[now][0]);return 0;
}

void Plus(int &x,int y){
	x=(x+y)%Mod;return;
}

