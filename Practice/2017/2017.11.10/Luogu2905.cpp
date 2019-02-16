#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001;
const int maxK=31;
const int maxMap=(maxK+10)*2;
const int inf=2147483647;
const int F1[5]={0,1,0,0,-1};
const int F2[5]={0,0,1,-1,0};
const char Dir[7]={" ENSW"};

class Pos
{
public:
    int x,y;
};

int n,m,K;
Pos Cow[maxN];
Pos Haystack[maxN];
int Skip[maxMap][maxMap];//Skip[i][j]:向N跳i步,向E跳j步能拯救的牛的数量
int F[maxK][maxMap][maxMap];

int main()
{
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=n;i++) scanf("%d%d",&Cow[i].x,&Cow[i].y);
    for (int i=1;i<=m;i++) scanf("%d%d",&Haystack[i].x,&Haystack[i].y);
    for (int i=1;i<=n;i++)//枚举每一只牛和每一个草垛
		for (int j=1;j<=m;j++)
		{
			int d1=Haystack[j].x-Cow[i].x,d2=Haystack[j].y-Cow[i].y;
			if (abs(d1)+abs(d2)>K) continue;
			Skip[d1+maxK][d2+maxK]++;
		}
    /*
	  for (int i=0;i<maxMap;i++)
	  for (int j=0;j<maxMap;j++)
	  if (Skip[i][j]!=0) cout<<"["<<i-maxN<<","<<j-maxN<<"] "<<Skip[i][j]<<endl;
    //*/
    for (int i=K;i>=0;i--)//为了方便后面求出路径，这里倒序存放在F数组中，因为最后知道F[0][(0,0)]是起始的状态，所以倒过来就是终态，这也能方便输出字典序最小的方案
		for (int x=maxK-i;x<=maxK+i;x++)
			for (int y=maxK-i;y<=maxK+i;y++)
			{
				for (int f=1;f<=4;f++)
				{
					int x2=x+F1[f],y2=y+F2[f];
					F[i][x][y]=max(F[i][x][y],F[i+1][x2][y2]);
				}
				F[i][x][y]+=Skip[x][y];
			}
    printf("%d\n",F[0][maxK][maxK]);
    int x=maxK,y=maxK;
    for (int i=0;i<K;i++)
    {
		for (int f=1;f<=4;f++)
		{
			int x2=x+F1[f],y2=y+F2[f];
			if (F[i][x][y]==F[i+1][x2][y2]+Skip[x][y])
			{
				x=x2;y=y2;
				printf("%c",Dir[f]);
				break;
			}
		}
    }
    printf("\n");
    return 0;
}
