#include<bits/stdc++.h>
using namespace std;

const int maxN=2010;
const int inf=2147483647;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

int n,K;
char Input[maxN][maxN];
int F[maxN][maxN];
pair<int,int> P[2][maxN];

int main(){
	cin>>n>>K;
	for (int i=1;i<=n;i++) cin>>(Input[i]+1);
	F[1][1]=Input[1][1]!='a';
	for (int i=1;i<=n;i++)
		for (int j=(i==1)?2:1;j<=n;j++){
			F[i][j]=inf;
			if (i!=1) F[i][j]=min(F[i][j],F[i-1][j]);
			if (j!=1) F[i][j]=min(F[i][j],F[i][j-1]);
			F[i][j]=F[i][j]+(Input[i][j]!='a');
		}
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (F[i][j]<=K) Input[i][j]='a';

	int top[2]={0,1};P[1][1]=make_pair(1,1);
	int now=1;
	printf("%c",Input[1][1]);
	for (int ccc=1;ccc<=2*n-2;ccc++){
		now^=1;mem(P[now],0);top[now]=0;
		char minchar='z';
		for (int i=1;i<=top[now^1];i++){
			int x=P[now^1][i].first,y=P[now^1][i].second;
			if (x+1<=n) minchar=min(minchar,Input[x+1][y]);
			if (y+1<=n) minchar=min(minchar,Input[x][y+1]);
		}
		printf("%c",minchar);
		for (int i=1;i<=top[now^1];i++){
			int x=P[now^1][i].first,y=P[now^1][i].second;
			if ((x+1<=n)&&(Input[x+1][y]==minchar)) P[now][++top[now]]=make_pair(x+1,y);
			if ((y+1<=n)&&(Input[x][y+1]==minchar)) P[now][++top[now]]=make_pair(x,y+1);
		}
		sort(&P[now][1],&P[now][top[now]+1]);
		top[now]=unique(&P[now][1],&P[now][top[now]+1])-P[now]-1;
	}
	printf("\n");
	return 0;
}
