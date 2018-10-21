#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=20;
const int maxM=20;
const int End=(1<<18)-1;
const int inf=2147483647;

int Id[maxN][maxN];
int Tri[maxN];
int F[1<<maxM];

int dfs(RG int status);
int Place(int status,RG int edge);

int main()
{
	Id[1][2]=1<<0;Id[1][3]=1<<1;Id[2][3]=1<<2;Id[2][4]=1<<3;Id[2][5]=1<<4;Id[3][5]=1<<5;Id[3][6]=1<<6;Id[4][5]=1<<7;Id[5][6]=1<<8;Id[4][7]=1<<9;Id[4][8]=1<<10;Id[5][8]=1<<11;Id[5][9]=1<<12;Id[6][9]=1<<13;Id[6][10]=1<<14;Id[7][8]=1<<15;Id[8][9]=1<<16;Id[9][10]=1<<17;
	Tri[1]=Id[1][2]|Id[1][3]|Id[2][3];
	Tri[2]=Id[2][4]|Id[2][5]|Id[4][5];
	Tri[3]=Id[2][3]|Id[2][5]|Id[3][5];
	Tri[4]=Id[3][5]|Id[3][6]|Id[5][6];
	Tri[5]=Id[4][7]|Id[4][8]|Id[7][8];
	Tri[6]=Id[4][5]|Id[4][8]|Id[5][8];
	Tri[7]=Id[5][8]|Id[5][9]|Id[8][9];
	Tri[8]=Id[5][6]|Id[5][9]|Id[6][9];
	Tri[9]=Id[6][9]|Id[6][10]|Id[9][10];
	//for (int i=1;i<=9;i++) cout<<Tri[i]<<" ";cout<<endl;

	int TTTT;scanf("%d",&TTTT);
	while (TTTT--)
	{
		RG int TTT;scanf("%d",&TTT);
		mem(F,0);
		for (RG int ti=1;ti<=TTT;ti++)
		{
			RG int n;
			RG int opt=0,status=0,score=0;
			scanf("%d",&n);
			for (RG int i=1;i<=n;i++)
			{
				RG int e1,e2;scanf("%d%d",&e1,&e2);
				if (e1>e2) swap(e1,e2);
				int c=Place(status,Id[e1][e2]);
				status|=Id[e1][e2];
				if (c) score+=c*((opt==0)?(1):(-1));
				else opt^=1;
			}
			int ret=dfs(status);
			if (opt==0) score+=ret;
			else score-=ret;
			printf("Game %d: %c wins.\n",ti,((score>0)?('A'):('B')));
		}
		if (TTTT) printf("\n");
	}
	return 0;
}

int dfs(int status)
{
	if (F[status]) return F[status];
	if (status==End) return F[status]=0;
	int now=(~status)&End;
	int Ret=-inf;
	while (now)
	{
		int e=(now)&(-now);
		int c=Place(status,e);
		if (c) Ret=max(Ret,c+dfs(status|e));
		else Ret=max(Ret,-dfs(status|e));
		now-=e;
	}
	return F[status]=Ret;
}

int Place(int status,RG int edge)
{
	int ret=0;
	int nstatus=status|edge;
	for (RG int i=1;i<=9;i++)
		if ( ((status&Tri[i])!=Tri[i]) && ((nstatus&Tri[i])==Tri[i])) ret++;
	return ret;
}
