#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=72;
const int inf=2147483647;
const ll INF=1e18;

class Data{
public:
	int key,num,w;
};

int n,K;
Data D[maxN];
ll F[maxN][maxN][maxN];
int numcnt,Num[maxN];

bool cmp(Data A,Data B);

int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&D[i].key);
	for (int i=1;i<=n;i++) scanf("%d",&D[i].num),Num[i]=D[i].num;
	for (int i=1;i<=n;i++) scanf("%d",&D[i].w);

	sort(&Num[1],&Num[n+1]);numcnt=unique(&Num[1],&Num[n+1])-Num-1;
	for (int i=1;i<=n;i++) D[i].num=lower_bound(&Num[1],&Num[numcnt+1],D[i].num)-Num;
	sort(&D[1],&D[n+1],cmp);

	for (int i=2;i<=n;i++) D[i].w+=D[i-1].w;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=D[i].num;j++) F[i][i][j]=D[i].w-D[i-1].w;
		for (int j=D[i].num+1;j<=numcnt;j++) F[i][i][j]=K+D[i].w-D[i-1].w;
	}

	for (int len=2;len<=n;len++)
		for (int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			for (int k=numcnt;k>=1;k--){
				if (k!=numcnt) F[l][r][k]=F[l][r][k+1];
				else F[l][r][k]=INF;
				for (int p=l;p<=r;p++){
					F[l][r][k]=min(F[l][r][k],F[l][p-1][k]+F[p+1][r][k]+D[r].w-D[l-1].w+K);
					if (D[p].num>=k) F[l][r][k]=min(F[l][r][k],F[l][p-1][D[p].num]+F[p+1][r][D[p].num]+D[r].w-D[l-1].w);
				}
			}
		}

	/*
	for (int l=1;l<=n;l++)
		for (int r=l;r<=n;r++)
			for (int k=1;k<=numcnt;k++)
				cout<<"("<<l<<','<<r<<','<<k<<") "<<F[l][r][k]<<endl;
	//*/

	printf("%lld\n",F[1][n][1]);

	return 0;
}

bool cmp(Data A,Data B){
	return A.key<B.key;
}
