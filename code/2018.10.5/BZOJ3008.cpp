#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxK=510;
const int inf=10000000;

int n,m,K,a,b;
int F1[8],F2[8];
char Map[maxN][maxN];
int W[maxK][maxK];
int SX[maxK],SY[maxK],TX[maxK],TY[maxK];
int Dist[maxN][maxN];
bool inq[maxN][maxN];
queue<pair<int,int> > Q;
int Match[maxK],Lkey[maxK],Rkey[maxK],Slack[maxK];
int tim,timx[maxK],timy[maxK];

void Bfs(int sx,int sy);
bool Hungary(int u);

int main(){
	scanf("%d%d%d%d%d",&n,&m,&K,&a,&b);
	F1[0]=a;F1[1]=a;F1[2]=-a;F1[3]=-a;F1[4]=b;F1[5]=b;F1[6]=-b;F1[7]=-b;
	F2[0]=b;F2[1]=-b;F2[2]=b;F2[3]=-b;F2[4]=a;F2[5]=-a;F2[6]=a;F2[7]=-a;
	for (int i=1;i<=n;i++) scanf("%s",Map[i]+1);
	for (int i=1;i<=K;i++) scanf("%d%d",&SX[i],&SY[i]);
	for (int i=1;i<=K;i++) scanf("%d%d",&TX[i],&TY[i]);

	for (int i=1;i<=K;i++){
		Bfs(SX[i],SY[i]);
		/*
		for (int x=1;x<=n;x++){
			for (int y=1;y<=m;y++)
				cout<<Dist[x][y]<<" ";
			cout<<endl;
		}cout<<endl;
		//*/
		for (int j=1;j<=K;j++) W[i][j]=Dist[TX[j]][TY[j]];
	}

	/*
	for (int i=1;i<=K;i++){
		for (int j=1;j<=K;j++)
			cout<<W[i][j]<<" ";
		cout<<endl;
	}
	//*/
	
	for (int i=1;i<=K;i++) for (int j=1;j<=K;j++) W[i][j]=-W[i][j];

	for (int i=1;i<=K;i++){
		Lkey[i]=-inf;
		for (int j=1;j<=K;j++) Lkey[i]=max(Lkey[i],W[i][j]);
	}

	mem(Match,-1);
	for (int i=1;i<=K;i++){
		for (int j=1;j<=K;j++) Slack[j]=inf;
		do{
			tim++;
			if (Hungary(i)) break;
			int mnd=inf;
			for (int j=1;j<=K;j++) if (timy[j]!=tim) mnd=min(mnd,Slack[j]);
			for (int j=1;j<=K;j++){
				if (timx[j]==tim) Lkey[j]-=mnd;
				if (timy[j]==tim) Rkey[j]+=mnd;
				else Slack[j]-=mnd;
			}
		}
		while (1);
	}

	int Ans=0;
	for (int i=1;i<=K;i++) Ans+=Lkey[i]+Rkey[i];
	printf("%d\n",-Ans);return 0;
}

void Bfs(int sx,int sy){
	//cout<<"Bfs:"<<sx<<" "<<sy<<endl;
	mem(Dist,127);mem(inq,0);while (!Q.empty()) Q.pop();
	Dist[sx][sy]=0;Q.push(make_pair(sx,sy));inq[sx][sy]=1;
	do{
		int x=Q.front().first,y=Q.front().second;Q.pop();
		for (int f=0;f<8;f++){
			int nx=x+F1[f],ny=y+F2[f];
			if ((nx<=0)||(ny<=0)||(nx>n)||(ny>m)) continue;
			if (inq[nx][ny]) continue;
			if (Map[nx][ny]=='*') continue;
			Dist[nx][ny]=Dist[x][y]+1;inq[nx][ny]=1;
			Q.push(make_pair(nx,ny));
		}
	}
	while (!Q.empty());
}

bool Hungary(int u){
	timx[u]=tim;
	for (int i=1;i<=K;i++)
		if (timy[i]!=tim){
			if (Lkey[u]+Rkey[i]==W[u][i]){
				timy[i]=tim;
				if ((Match[i]==-1)||(Hungary(Match[i]))){
					Match[i]=u;return 1;
				}
			}
			Slack[i]=min(Slack[i],Lkey[u]+Rkey[i]-W[u][i]);
		}
	return 0;
}

