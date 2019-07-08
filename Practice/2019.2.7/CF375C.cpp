#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=25;
const int maxM=8;
const int Fx[]= {0,1,0,-1};
const int Fy[]= {1,0,-1,0};
const int inf=1000000;

class QData
{
public:
	int x,y,S;
};

int n,m,stx,sty;
int Mp[maxN][maxN],tcnt=0,X[maxM],Y[maxM],Key[maxM],Tid[maxN];
char Input[maxN];
int Dp[maxN][maxN][1<<maxM];
bool inq[maxN][maxN][1<<maxM];
queue<QData> Q;

int main()
{
	//freopen("in","r",stdin);
	mem(Tid,-1);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) {
		scanf("%s",Input+1);
		for (int j=1; j<=m; j++)
			if (Input[j]=='B') X[tcnt]=i,Y[tcnt]=j,Key[tcnt]=-inf,++tcnt,Mp[i][j]=1;
			else if (Input[j]=='S') stx=i,sty=j;
			else if (Input[j]=='#') Mp[i][j]=1;
			else if (Input[j]!='.') Tid[Input[j]-'0']=tcnt,X[tcnt]=i,Y[tcnt]=j,++tcnt,Mp[i][j]=1;
	}
	//for (int i=1;i<=10;i++) cout<<Tid[i]<<" ";cout<<endl;
	for (int i=1; Tid[i]!=-1; i++) scanf("%d",&Key[Tid[i]]);
	//for (int i=0;i<tcnt;i++) cout<<X[i]<<" "<<Y[i]<<" "<<Key[i]<<endl;
	mem(Dp,63);
	Dp[stx][sty][0]=0;
	Q.push((QData) {
		stx,sty,0
	});
	inq[stx][sty][0]=1;
	while (!Q.empty()) {
		int x=Q.front().x,y=Q.front().y,S=Q.front().S;
		Q.pop();
		for (int f=0; f<4; f++) {
			int xx=x+Fx[f],yy=y+Fy[f],SS=S;
			if (xx<=0||yy<=0||xx>n||yy>m||Mp[xx][yy]) continue;
			if (f==1) for (int i=0; i<tcnt; i++) if (X[i]==xx&&Y[i]<yy) SS^=(1<<i);
			if (f==3) for (int i=0; i<tcnt; i++) if (X[i]==x&&Y[i]<y) SS^=(1<<i);
			//cout<<"("<<x<<" "<<y<<" "<<S<<") -> ("<<xx<<" "<<yy<<" "<<SS<<")"<<endl;
			if (Dp[xx][yy][SS]>Dp[x][y][S]+1) {
				Dp[xx][yy][SS]=Dp[x][y][S]+1;
				if (inq[xx][yy][SS]==0) {
					Q.push((QData) {
						xx,yy,SS
					});
					inq[xx][yy][SS]=1;
				}
			}
		}
		inq[x][y][S]=0;
	}
	int Ans=0;
	for (int i=0; i<(1<<tcnt); i++) {
		int sum=0;
		for (int j=0; j<tcnt; j++) if (i&(1<<j)) sum+=Key[j];
		Ans=max(Ans,sum-Dp[stx][sty][i]);
	}
	printf("%d\n",Ans);
	return 0;
}