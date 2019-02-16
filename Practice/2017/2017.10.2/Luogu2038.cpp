#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=200;
const int maxPos=129;
const int inf=2147483647;

int D,n;
int Sum[maxN][maxN];

int main()
{
	scanf("%d",&D);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int x,y,k;
		scanf("%d%d%d",&x,&y,&k);
		Sum[x+1][y+1]+=k;
	}
	for (int i=1;i<=maxPos;i++)
	{
		Sum[0][i]=Sum[0][i]+Sum[0][i-1];
		Sum[i][0]=Sum[i][0]+Sum[i-1][0];
	}
	for (int i=1;i<=maxPos;i++)
		for (int j=1;j<=maxPos;j++)
			Sum[i][j]+=Sum[i-1][j]+Sum[i][j-1]-Sum[i-1][j-1];
	int method=0,maxNum=0;
	for (int i=1;i<=maxPos;i++)
		for (int j=1;j<=maxPos;j++)
		{
			int l1,l2,r1,r2;
			l1=max(0,i-D-1);
			r1=max(0,j-D-1);
			l2=min(maxPos,i+D);
			r2=min(maxPos,j+D);
			int now=Sum[l2][r2]-Sum[l1][r2]-Sum[l2][r1]+Sum[l1][r1];
			if (now>maxNum)
			{
				maxNum=now;
				method=1;
			}
			else
				if (now==maxNum)
					method++;
		}
	printf("%d %d\n",method,maxNum);
	return 0;
}
