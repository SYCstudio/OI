#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=3510;
const int N=3500;
const int Key[10]={119,36,93,109,46,107,123,37,127,111};
const int inf=2147483647;

int n,m;
char Input[maxN];
short F[3505/2][7010][2];

IL void GetMin(RG short &x,RG int y);

int main(){
	RG int i,j,k,x,usesum,movecnt,sum=0,len;
	int move[11][10],delta[11][10];mem(move,0);mem(delta,0);
	for (i=0;i<=9;++i)
		for (j=0;j<=9;++j)
			for (k=0;k<=6;++k){
				if ( !(Key[i]&(1<<k)) && (Key[j]&(1<<k)) ) ++move[i][j],++delta[i][j];
				if ( (Key[i]&(1<<k)) && !(Key[j]&(1<<k)) ) --delta[i][j];
			}
	for (i=0;i<=9;++i) for (j=0;j<=6;++j) if (Key[i]&(1<<j)) ++move[10][i],++delta[10][i];
	scanf("%s",Input+1);scanf("%d",&m);n=strlen(Input+1);
	reverse(&Input[1],&Input[n+1]);for (i=1;i<=n;++i) Input[i]-='0',sum+=move[10][Input[i]];
	len=sum/2;
	for (i=n+1;i<=len;++i) Input[i]=10;
	for (i=0;i<=len;++i) for (j=-m;j<=m;++j) for (k=0;k<=1;++k) F[i][j+N][k]=m+1;
	F[0][N][0]=0;
	for (i=0;i<len;++i)
		for (j=-m;j<=m;++j)
			for (k=0;k<=1;++k)
				if (F[i][j+N][k]<=m)
					for (x=0;x<=9;++x)
						GetMin(F[i+1][j+delta[Input[i+1]][x]+N][x==0],F[i][j+N][k]+move[Input[i+1]][x]);
	while (F[len][N][0]>m) --len;
	for (i=0;i<=len;++i) for (j=-m;j<=m;++j) GetMin(F[i][N+j][0],F[i][N+j][1]);
	for (i=len,usesum=0,movecnt=0;i>=1;--i)
		for (j=9;j>=0;--j){
			usesum+=delta[Input[i]][j];movecnt+=move[Input[i]][j];
			if (F[i-1][N-usesum][0]<=m-movecnt){
				printf("%d",j);
				break;
			}
			usesum-=delta[Input[i]][j];movecnt-=move[Input[i]][j];
		}
	return 0;
}

IL void GetMin(short &x,int y){
	if (x>y) x=y;return;
}
