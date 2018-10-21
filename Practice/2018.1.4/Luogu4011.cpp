#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=16;
const int maxSta=1<<12;
const int maxQueue=maxMap*maxMap*maxSta;
const int F1[5]={0,-1,0,1,0};
const int F2[5]={0,0,-1,0,1};
const int inf=2147483647;

class Queue_Data
{
public:
    int s,x,y;
};

int n,m,P,K,S;
int Map[maxMap][maxMap][5];
int Key[maxMap][maxMap];
int Dist[maxSta][maxMap][maxMap];
bool inqueue[maxSta][maxMap][maxMap];
Queue_Data Queue[maxQueue];

int main()
{
    mem(Map,-1);
    scanf("%d%d%d",&n,&m,&P);
    scanf("%d",&K);
    for (int i=1;i<=K;i++)
    {
	int x1,y1,x2,y2,gi;scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&gi);
	for (int j=1;j<=4;j++)
	    if ((x1+F1[j]==x2)&&(y1+F2[j]==y2))
	    {
		Map[x1][y1][j]=gi;
		break;
	    }
	for (int j=1;j<=4;j++)
	    if ((x2+F1[j]==x1)&&(y2+F2[j]==y1))
	    {
		Map[x2][y2][j]=gi;
		break;
	    }
    }
    //for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=4;k++) if (Map[i][j][k]!=-1) cout<<i<<" "<<j<<" "<<k<<endl;
    //cout<<endl;
    scanf("%d",&S);
    for (int i=1;i<=S;i++)
    {
	int x,y,key;scanf("%d%d%d",&x,&y,&key);
	Key[x][y]=Key[x][y]|(1<<key);
    }
    mem(Dist,-1);
    int h=1,t=0;
    Dist[0][1][1]=0;
    Queue[1]=((Queue_Data){0,1,1});inqueue[0][1][1]=1;
    do
    {
	++t;if (t>=maxQueue) t=0;
	Queue_Data u=Queue[t];inqueue[u.s][u.x][u.y]=0;
	//cout<<u.x<<","<<u.y<<" "<<u.s<<endl;
	int su=u.s|Key[u.x][u.y];
	for (int i=1;i<=4;i++)
	    if (Map[u.x][u.y][i]!=0)
		if ((Map[u.x][u.y][i]==-1)||(((1<<Map[u.x][u.y][i])&su)!=0))
		{
		    int x2=u.x+F1[i];int y2=u.y+F2[i];
		    if ((x2<=0)||(y2<=0)||(x2>n)||(y2>m)) continue;
		    if ((Dist[su][x2][y2]==-1)||(Dist[su][x2][y2]>Dist[u.s][u.x][u.y]+1))
		    {
			Dist[su][x2][y2]=Dist[u.s][u.x][u.y]+1;
			if (inqueue[su][x2][y2]==0)
			{
			    inqueue[su][x2][y2]=1;++h;if (h>=maxQueue) h=0;
			    Queue[h]=((Queue_Data){su,x2,y2});
			}
		    }
		}
    }
    while (t!=h);
    int Ans=inf;
    for (int i=0;i<(1<<(P+1));i++) if (Dist[i][n][m]!=-1) Ans=min(Ans,Dist[i][n][m]);
    if (Ans==inf) Ans=-1;
    printf("%d\n",Ans);
    return 0;
}
