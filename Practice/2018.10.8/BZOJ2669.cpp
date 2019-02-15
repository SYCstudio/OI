#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=5;
const int maxM=8;
const int Mod=12345678;
const int maxT=11;
const int F1[]={-1,-1,-1,0,0,1,1,1};
const int F2[]={-1,0,1,-1,1,-1,0,1};
const int inf=2147483647;

int n,m;
char Mp[maxN][maxM];
int Ans,F[maxN*maxM][1<<maxT],X[maxT],Y[maxT],num[1<<maxT];
bool vis[maxN][maxM];

void dfs(int x,int y,int opt);
int Calc();

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",Mp[i]+1);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (Mp[i][j]=='X'){
				for (int f=0;f<8;f++){
					int xx=i+F1[f],yy=j+F2[f];
					if ((xx<=0)||(yy<=0)||(xx>n)||(yy>m)) continue;
					if (Mp[xx][yy]=='X'){
						printf("0\n");return 0;
					}
				}
			}
	dfs(1,1,1);
	printf("%d\n",Ans);return 0;
}

void dfs(int x,int y,int opt){
	if (y==m+1) y=1,x++;
	if (x==n+1){
		Ans=(Ans+opt*Calc()%Mod+Mod)%Mod;
		return;
	}
	dfs(x,y+1,opt);
	bool flag=(Mp[x][y]=='.');
	for (int f=0;f<8;f++){
		int xx=x+F1[f],yy=y+F2[f];
		if ((xx<=0)||(yy<=0)||(xx>n)||(yy>m)) continue;
		if (Mp[xx][yy]=='X') flag=0;
	}
	if (flag){
		Mp[x][y]='X';
		dfs(x,y+1,-opt);
		Mp[x][y]='.';
	}
	return;
}

int Calc(){
	int tcnt=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) if (Mp[i][j]=='X') X[tcnt]=i,Y[tcnt]=j,tcnt++;
	for (int S=0;S<(1<<tcnt);S++){
		mem(vis,0);
		for (int i=0;i<tcnt;i++)
			if ((S&(1<<i))==0){
				vis[X[i]][Y[i]]=1;
				for (int f=0;f<8;f++){
					int xx=X[i]+F1[f],yy=Y[i]+F2[f];
					if ((xx<=0)||(yy<=0)||(xx>n)||(yy>m)) continue;
					vis[xx][yy]=1;
				}
			}
		num[S]=n*m;
		for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) num[S]=num[S]-vis[i][j];
	}
	//for (int i=1;i<=n;i++) cout<<(Mp[i]+1)<<endl;
	//for (int S=0;S<(1<<tcnt);S++) cout<<S<<" "<<num[S]<<endl;
	mem(F,0);
	F[0][0]=1;
	for (int i=1;i<=n*m;i++)
		for (int j=0;j<(1<<tcnt);j++){
			F[i][j]=(1ll*F[i-1][j]*max(0,num[j]-i+1))%Mod;
			for (int k=0;k<tcnt;k++)
				if (j&(1<<k))
					F[i][j]=(F[i][j]+F[i-1][j^(1<<k)])%Mod;
		}
	return F[n*m][(1<<tcnt)-1];
}
