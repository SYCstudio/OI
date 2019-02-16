#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=7;
const int inf=2147483647;

int n,Ans;
bool Cover[maxN][maxN];
char Map[maxN][maxN];

void dfs(int x,int y,int cnt);

int main()
{
    while (scanf("%d",&n)!=EOF)
    {
	if (n==0) break;
	for (int i=1;i<=n;i++)
	    scanf("%s",Map[i]+1);
	Ans=0;
	dfs(1,1,0);
	printf("%d\n",Ans);
    }
    return 0;
}

void dfs(int x,int y,int cnt)
{
    if (y==n+1) x++,y=1;
    if (x==n+1)
    {
	Ans=max(Ans,cnt);return;
    }
    if (Map[x][y]=='X') dfs(x,y+1,cnt);
    else
    {
	bool ok=1;
	for (int i=x;(i>=1)&&(Map[i][y]!='X');i--)
	    if (Cover[i][y]) ok=0;
	for (int i=x;(i<=n)&&(Map[i][y]!='X');i++)
	    if (Cover[i][y]) ok=0;
	for (int i=y;(i>=1)&&(Map[x][i]!='X');i--)
	    if (Cover[x][i]) ok=0;
	for (int i=y;(i<=n)&&(Map[x][i]!='X');i++)
	    if (Cover[x][i]) ok=0;
	if (ok)
	{
	    Cover[x][y]=1;
	    dfs(x,y+1,cnt+1);
	    Cover[x][y]=0;
	}
	dfs(x,y+1,cnt);
    }
    return;
}
