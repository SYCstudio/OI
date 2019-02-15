#include<bits/stdc++.h>
using namespace std;

const int maxN=2010;
const int F1[]={-1,0,1,0};
const int F2[]={0,1,0,-1};
const int inf=2147483647;

int n,m,sx,sy,x,y;
char Map[maxN][maxN];
pair<int,int> Max[maxN][maxN];
bool vis[maxN][maxN];
queue<pair<int,int> > Q;

int main(){
	scanf("%d%d",&n,&m);scanf("%d%d",&sx,&sy);scanf("%d%d",&x,&y);
	for (int i=1;i<=n;i++) scanf("%s",Map[i]+1);
	Max[sx][sy]=make_pair(x,y);vis[sx][sy]=1;Q.push(make_pair(sx,sy));
	do{
		int nx=Q.front().first,ny=Q.front().second;Q.pop();
		for (int f=0;f<4;f++){
			int px=nx+F1[f],py=ny+F2[f];
			if ((vis[px][py])||(px<=0)||(py<=0)||(px>n)||(py>m)) continue;
			if (Map[px][py]=='*') continue;
			if ((f==3)&&(Max[nx][ny].first==0)) continue;
			if ((f==1)&&(Max[nx][ny].second==0)) continue;

			Max[px][py]=Max[nx][ny];vis[px][py]=1;Q.push(make_pair(px,py));
			if (f==3) Max[px][py].first--;
			if (f==1) Max[px][py].second--;
		}
	}
	while (!Q.empty());
	int Ans=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Ans+=vis[i][j];
	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			cout<<vis[i][j]<<" ";
		cout<<endl;
	}
	//*/
	printf("%d\n",Ans);
	return 0;
}
