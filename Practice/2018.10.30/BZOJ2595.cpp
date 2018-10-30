#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=11;
const int F1[4]={-1,0,1,0};
const int F2[4]={0,-1,0,1};
const int inf=2147483647;

int n,m,empty;
int Val[maxN][maxN];
int F[maxN][maxN][1<<maxN];
pair<int,int> From[maxN][maxN][1<<maxN];
int viscnt,vis[maxN][maxN];
priority_queue<pair<int,pair<int,int> > > H;

void mark(int x,int y,int S);

int main(){
	int ex,ey;
	mem(F,63);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			scanf("%d",&Val[i][j]);
			if (Val[i][j]==0) F[i][j][1<<(empty++)]=0,ex=i,ey=j;
		}

	for (int S=0;S<(1<<empty);++S){
		for (int x=1;x<=n;x++)
			for (int y=1;y<=m;y++){
				for (int s=S;s;s=(s-1)&S)
					if (F[x][y][S]>F[x][y][s]+F[x][y][S^s]-Val[x][y]){
						F[x][y][S]=F[x][y][s]+F[x][y][S^s]-Val[x][y];
						From[x][y][S]=make_pair(4,s);
					}
				if (F[x][y][S]!=F[0][0][0]) H.push(make_pair(-F[x][y][S],make_pair(x,y)));
			}
		++viscnt;
		while (!H.empty()){
			int x=H.top().second.first,y=H.top().second.second;H.pop();
			if (vis[x][y]==viscnt) continue;vis[x][y]=viscnt;
			for (int f=0;f<4;f++){
				int xx=x+F1[f],yy=y+F2[f];
				if ((xx<=0)||(yy<=0)||(x>n)||(y>m)) continue;
				if (F[xx][yy][S]>F[x][y][S]+Val[xx][yy]){
					F[xx][yy][S]=F[x][y][S]+Val[xx][yy];From[xx][yy][S]=make_pair(f,S);
					H.push(make_pair(-F[xx][yy][S],make_pair(xx,yy)));
				}
			}
		}
	}
	++viscnt;
	mark(ex,ey,(1<<empty)-1);
	printf("%d\n",F[ex][ey][(1<<empty)-1]);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			if (Val[i][j]==0) printf("x");
			else if (vis[i][j]==viscnt) printf("o");
			else printf("_");
		printf("\n");
	}
	return 0;
}

void mark(int x,int y,int S){
	vis[x][y]=viscnt;
	if (From[x][y][S].second==0) return;
	int f=From[x][y][S].first;
	if (f<=3) mark(x-F1[f],y-F2[f],S);
	else{
		mark(x,y,From[x][y][S].second);
		mark(x,y,From[x][y][S].second^S);
	}
	return;
}
