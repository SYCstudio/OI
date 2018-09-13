#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=120;
const int inf=2147483647;
const int F1[5]={0,-1,1,0,0};
const int F2[5]={0,0,0,-1,1};

int n,m;
int sx,sy,ex,ey;
int Map[maxN][maxN];
char Input[maxN];
char Follow[maxN];
int Id[4];

int main()
{
	mem(Map,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",Input+1);
		for (int j=1;j<=m;j++)
			if (Input[j]=='.') Map[i][j]=0;
			else if (Input[j]=='S') sx=i,sy=j,Map[i][j]=0;
			else if (Input[j]=='E') ex=i,ey=j,Map[i][j]=0;
	}
	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			cout<<Map[i][j]<<" ";
		cout<<endl;
	}
	//*/
	scanf("%s",Follow);
	int flen=strlen(Follow);
	for (int i=0;i<flen;i++) Follow[i]-='0';
	Id[0]=1;Id[1]=2;Id[2]=3;Id[3]=4;
	int Ans=0;
	do
	{
		/*
		for (int i=0;i<=3;i++) cout<<Id[i]<<" ";
		cout<<endl;
		//*/
		int x=sx,y=sy;
		bool flag=1;
		//if ((Id[0]==2)&&(Id[1]==3)&&(Id[2]==1)&&(Id[3]==4)) cout<<"("<<x<<","<<y<<")"<<endl;
		for (int i=0;i<flen;i++)
		{
			int nx=x+F1[Id[Follow[i]]];
			int ny=y+F2[Id[Follow[i]]];
			//if ((Id[0]==2)&&(Id[1]==3)&&(Id[2]==1)&&(Id[3]==4)) cout<<"-->("<<nx<<","<<ny<<")"<<endl;
			if (Map[nx][ny]==-1)
			{
				flag=0;
				break;
			}
			x=nx;y=ny;
			if ((x==ex)&&(y==ey)) break;
		}
		if ((x==ex)&&(y==ey)&&(flag)) Ans++;
	}
	while(next_permutation(&Id[0],&Id[4]));
	printf("%d\n",Ans);
	return 0;
}
