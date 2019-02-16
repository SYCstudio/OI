#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=115;
const int maxN=maxMap*maxMap;
const int maxK=15;
const int maxQueue=maxMap*maxMap*maxK;
const int F1[5]={0,-1,0,1,0};
const int F2[5]={0,0,-1,0,1};
const int inf=147483647;

class Queue_Data
{
public:
    int k,x,y;
};

int n,K,A,B,C;
int Dist[maxK][maxMap][maxMap];
bool inqueue[maxK][maxMap][maxMap];
int Gas[maxMap][maxMap];
Queue_Data Q[maxQueue];

int main()
{
    //freopen("trav.in","r",stdin);
    //freopen("trav.out","w",stdout);
    scanf("%d%d%d%d%d",&n,&K,&A,&B,&C);
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) scanf("%d",&Gas[i][j]);
    mem(Dist,-1);
    Dist[K][1][1]=0;
    int h=1,t=0;Q[1]=((Queue_Data){K,1,1});inqueue[K][1][1]=1;
    do
    {
	++t;if (t>=maxQueue) t=0;
	Queue_Data u=Q[t];
	if (u.k!=0)
	    for (int i=1;i<=4;i++)
	    {
		int x=u.x+F1[i],y=u.y+F2[i];
		if ((x<=0)||(x>n)||(y<=0)||(y>n)) continue;
		int d=0,k=u.k-1;//if (k==0) continue;
		if (Gas[x][y]) d=d+A,k=K;
		//else if (u.k==1) d=d+C+A,k=K;
		if (i<=2) d=d+B;
		//cout<<"("<<u.x<<","<<u.y<<")->("<<x<<","<<y<<"):"<<d<<endl;
		if ((Dist[k][x][y]==-1)||(Dist[k][x][y]>Dist[u.k][u.x][u.y]+d))
		{
		    Dist[k][x][y]=Dist[u.k][u.x][u.y]+d;
		    if (inqueue[k][x][y]==0)
		    {
			inqueue[k][x][y]=1;
			++h;if (h>=maxQueue) h=0;
			Q[h]=((Queue_Data){k,x,y});
		    }
		}
	    }
	int d=A+C,k=K;
	if ((Dist[k][u.x][u.y]==-1)||(Dist[k][u.x][u.y]>Dist[u.k][u.x][u.y]+d))
	{
	    Dist[k][u.x][u.y]=Dist[u.k][u.x][u.y]+d;
	    if (inqueue[k][u.x][u.y]==0)
	    {
		inqueue[k][u.x][u.y]=1;
		++h;if (h>=maxQueue) h=0;
		Q[h]=((Queue_Data){k,u.x,u.y});
	    }
	}
	inqueue[u.k][u.x][u.y]=0;
    }
    while (t!=h);
    int Ans=inf;
    for (int i=0;i<=K;i++)
    {
	//cout<<Dist[i][n][n]<<" ";
	if (Dist[i][n][n]!=-1) Ans=min(Ans,Dist[i][n][n]);
    }
    printf("%d\n",Ans);
    return 0;
}
