#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxN=51;
const int inf=2147483647;

int n;
int Mat[maxN][maxN];

int main()
{
	scanf("%d",&n);
	int posx,posy;
	posx=1;
	posy=n/2+1;
	Mat[posx][posy]=1;
	for (int i=2;i<=n*n;i++)
	{
		if ((posx!=1)||(posy!=n))
		{
			if (posx==1)
			{
				posx=n;
				posy++;
				Mat[posx][posy]=i;
			}
			else
				if (posy==n)
				{
					posx--;
					posy=1;
					Mat[posx][posy]=i;
				}
				else
				{
					if (Mat[posx-1][posy+1]==0)
					{
						posx--;
						posy++;
						Mat[posx][posy]=i;
					}
					else
					{
						posx++;
						Mat[posx][posy]=i;
					}
				}
		}
		else
		{
			posx++;
			Mat[posx][posy]=i;
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
			printf("%d ",Mat[i][j]);
		printf("\n");
	}
	return 0;
}
