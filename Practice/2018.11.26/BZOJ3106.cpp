#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=21;
const int F1[]={-1,0,1,0};
const int F2[]={0,-1,0,1};
const int inf=2000000000;

int n;
int F[maxN*4][maxN][maxN][maxN][maxN];

int dfs(int xw,int yw,int xb,int yb,int dep);

int main(){
	int xw,yw,xb,yb;scanf("%d%d%d%d%d",&n,&xw,&yw,&xb,&yb);
	if (abs(xw-xb)+abs(yw-yb)<=1){
		printf("WHITE 1\n");return 0;
	}
	mem(F,-1);
	printf("BLACK %d\n",dfs(xw,yw,xb,yb,1));
	return 0;
}

int dfs(int xw,int yw,int xb,int yb,int dep){
	if ((xw==xb)&&(yw==yb)) return (dep&1)?(dep-1):inf;
	if (dep>4*n) return inf;
	if (F[dep][xw][yw][xb][yb]!=-1) return F[dep][xw][yw][xb][yb];
	if (dep&1){
		F[dep][xw][yw][xb][yb]=0;
		for (int f=0;f<4;f++){
			int xx=xw+F1[f],yy=yw+F2[f];
			if ((xx<=0)||(yy<=0)||(xx>n)||(yy>n)) continue;
			//if (dfs(xx,yy,xb,yb,dep+1)<inf) F[dep][xw][yw][xb][yb]=max(F[dep][xw][yw][xb][yb],F[dep+1][xx][yy][xb][yb]);
			F[dep][xw][yw][xb][yb]=max(F[dep][xw][yw][xb][yb],dfs(xx,yy,xb,yb,dep+1));
		}
	}
	else{
		F[dep][xw][yw][xb][yb]=inf;
		for (int f=0;f<4;f++){
			int xx=xb+F1[f],yy=yb+F2[f];
			if ((xx<=0)||(yy<=0)||(xx>n)||(yy>n)) continue;
			F[dep][xw][yw][xb][yb]=min(F[dep][xw][yw][xb][yb],dfs(xw,yw,xx,yy,dep+1));
			xx+=F1[f];yy+=F2[f];
			if ((xx<=0)||(yy<=0)||(xx>n)||(yy>n)) continue;
			F[dep][xw][yw][xb][yb]=min(F[dep][xw][yw][xb][yb],dfs(xw,yw,xx,yy,dep+1));
		}
	}
	//cout<<xw<<" "<<yw<<" "<<xb<<" "<<yb<<" "<<dep<<" ["<<F[dep][xw][yw][xb][yb]<<"]"<<endl;
	return F[dep][xw][yw][xb][yb];
}
