#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMat=40;
const int maxF=5;
//const int inf=2147483647;
const int meminf=2139062143;
const int ff[5]={0,2,1,4,3};

class Pos
{
public:
	int x,y;
	Pos()
		{
			return;
		}
	Pos(int a,int b)
		{
			x=a;
			y=b;
		}
};

class Queue_Data
{
public:
	int x,y,f;
};

int n,m;
int Mat[maxMat][maxMat];
Pos F[maxF];
int Skip[maxMat][maxMat][maxF][maxF];
int Dist[maxMat][maxMat][maxF];
bool vis[maxMat][maxMat][maxF];
queue<Queue_Data> Q;

Pos operator + (Pos A,Pos B);
Queue_Data operator + (Queue_Data A,Pos B);
void init();
int Bfs(Pos st,Pos ed);

int main()
{
	int qus;
	scanf("%d%d%d",&n,&m,&qus);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&Mat[i][j]);
	init();
	while (qus--)
	{
		int Epx,Epy,Stx,Sty,Glx,Gly;
		scanf("%d%d%d%d%d%d",&Epx,&Epy,&Stx,&Sty,&Glx,&Gly);
		if ((Mat[Stx][Sty]==0)||(Mat[Glx][Gly]==0))
		{
			printf("-1\n");
			continue;
		}
		if ((Stx==Glx)&&(Sty==Gly))
		{
			printf("0\n");
			continue;
		}
		
		Mat[Stx][Sty]=0;
		while (!Q.empty())
			Q.pop();
		mem(Dist,127);
		mem(vis,0);
		
		Pos init=(Pos){Stx,Sty};
		for (int i=1;i<=4;i++)
		{
			Pos v=init+F[i];
			Dist[Stx][Sty][i]=Bfs((Pos){Epx,Epy},v);
			if (Dist[Stx][Sty][i]!=meminf)
				Q.push((Queue_Data){Stx,Sty,i});
		}
		Mat[Stx][Sty]=1;

		while (!Q.empty())
		{
			Queue_Data u=Q.front();
			Q.pop();
			vis[u.x][u.y][u.f]=0;
			for (int i=1;i<=4;i++)
			{
				Queue_Data v=u+F[i];
				v.f=ff[i];
				if (Dist[v.x][v.y][v.f]>Dist[u.x][u.y][u.f]+Skip[u.x][u.y][u.f][i])
				{
					Dist[v.x][v.y][v.f]=Dist[u.x][u.y][u.f]+Skip[u.x][u.y][u.f][i];
					if (vis[v.x][v.y][v.f]==0)
					{
						Q.push(v);
						vis[v.x][v.y][v.f]=1;
					}
				}
			}
		}

		int Ans=meminf;
		for (int i=1;i<=4;i++)
			Ans=min(Ans,Dist[Glx][Gly][i]);
		if (Ans==meminf)
			Ans=-1;
		printf("%d\n",Ans);
	}
	return 0;
}

Pos operator + (Pos A,Pos B)
{
	return (Pos){A.x+B.x,A.y+B.y};
}

Queue_Data operator + (Queue_Data A,Pos B)
{
	return (Queue_Data){A.x+B.x,A.y+B.y,A.f};
}

void init()
{
	F[1]=(Pos){-1,0};
	F[2]=(Pos){1,0};
	F[3]=(Pos){0,-1};
	F[4]=(Pos){0,1};
	mem(Skip,127);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (Mat[i][j]==0)
				continue;
			Mat[i][j]=0;
			Pos now(i,j);
			for (int f1=1;f1<=4;f1++)
				for (int f2=1;f2<=4;f2++)
				{
					if (f1>f2)
					{
						Skip[i][j][f1][f2]=Skip[i][j][f2][f1];
						continue;
					}
					Skip[i][j][f1][f2]=Bfs(now+F[f1],now+F[f2])+1;
				}
			Mat[i][j]=1;
		}
	return;
}

int Bfs(Pos st,Pos ed)
{
	if ((Mat[st.x][st.y]==0)||(Mat[ed.x][ed.y]==0))
		return meminf;
	
	queue<Pos> Q;
	while (!Q.empty())
		Q.pop();
	bool vis[maxMat][maxMat];
	int Dist[maxMat][maxMat];
	mem(vis,0);
	mem(Dist,127);
	
	Q.push(st);
	vis[st.x][st.y]=1;
	Dist[st.x][st.y]=0;
	
	do
	{
		Pos u=Q.front();
		Q.pop();
		for (int i=1;i<=4;i++)
		{
			Pos v=u+F[i];
			if ((Mat[v.x][v.y]==0)||(vis[v.x][v.y]==1))
				continue;
			vis[v.x][v.y]=1;
			Dist[v.x][v.y]=Dist[u.x][u.y]+1;
			Q.push(v);
		}
	}
	while (!Q.empty());
	return Dist[ed.x][ed.y];
}
